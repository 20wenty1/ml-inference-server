#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#define WORKER_SOCK "/tmp/spam_worker.sock"
#define WORKER_TIMEOUT_SEC 3

int call_worker(char *text, char *out, int out_size) {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) return -1;

    struct timeval tv;
    tv.tv_sec = WORKER_TIMEOUT_SEC;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, WORKER_SOCK, sizeof(addr.sun_path) - 1);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        return -1;
    }

    if (write(sock, text, strlen(text)) < 0) {
        close(sock);
        return -1;
    }

    int n = read(sock, out, out_size - 1);
    if (n > 0) {
        out[n] = '\0';
    } else {
        close(sock);
        return -1;
    }

    close(sock);
    return 0;
}

void handle_client(int client_fd) {
    char buffer[4096];
    int n = read(client_fd, buffer, sizeof(buffer) - 1);
    if (n <= 0) {
        close(client_fd);
        return;
    }
    buffer[n] = '\0';

    char method[8];
    char path[256];
    sscanf(buffer, "%7s %255s", method, path);

    char *body = strstr(buffer, "\r\n\r\n");
    if (body != NULL) body += 4;

    printf("method: %s\n", method);
    printf("path: %s\n", path);

    char res[512];
    int len;

    if (strcmp(method, "GET") == 0 && strcmp(path, "/") == 0) {
        char *msg = "{\"message\": \"Spam detection API is running\"}";
        len = strlen(msg);
        snprintf(res, sizeof(res), "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", len, msg);
    }
    else if (strcmp(method, "POST") == 0 && strcmp(path, "/predict") == 0) {
        if (body == NULL || strlen(body) == 0) {
            char *msg = "{\"error\": \"empty request body\"}";
            len = strlen(msg);
            snprintf(res, sizeof(res), "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", len, msg);
        }
        else {
            char prediction[256];
            int ok = call_worker(body, prediction, sizeof(prediction)) == 0;

            if (ok) {
                char msg[300];
                snprintf(msg, sizeof(msg), "{\"prediction\": \"%s\"}", prediction);
                len = strlen(msg);
                snprintf(res, sizeof(res), "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", len, msg);
            } else {
                char *msg = "{\"error\": \"worker unavailable or timed out\"}";
                len = strlen(msg);
                snprintf(res, sizeof(res), "HTTP/1.1 502 Bad Gateway\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", len, msg);
            }
        }
    }
    else {
        char *msg = "{\"error\": \"not found\"}";
        len = strlen(msg);
        snprintf(res, sizeof(res), "HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", len, msg);
    }

    write(client_fd, res, strlen(res));
    close(client_fd);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        exit(1);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("listening on port 8080\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}