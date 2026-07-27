#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <pthread.h>
#include "config.h"

int call_worker(const char *socket_path, char *text, char *out, int out_size) {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) return -1;

    struct timeval tv;
    tv.tv_sec = WORKER_TIMEOUT_SECONDS;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

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

pthread_mutex_t worker_index_lock = PTHREAD_MUTEX_INITIALIZER;
int next_worker_index = 0;

const char *pick_worker_socket() {
    pthread_mutex_lock(&worker_index_lock);
    int index = next_worker_index;
    next_worker_index = (next_worker_index + 1) % NUM_WORKERS;
    pthread_mutex_unlock(&worker_index_lock);
    return WORKER_SOCKET_PATHS[index];
}

void handle_client(int client_fd) {
    struct timeval client_tv;
    client_tv.tv_sec = CLIENT_TIMEOUT_SECONDS;
    client_tv.tv_usec = 0;
    setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, &client_tv, sizeof(client_tv));

    char buffer[REQUEST_BUFFER_SIZE];
    int total_read = 0;
    int header_end = -1;
    int content_length = 0;
    int body_too_large = 0;

    while (total_read < (int)sizeof(buffer) - 1) {
        int n = read(client_fd, buffer + total_read, sizeof(buffer) - 1 - total_read);
        if (n <= 0) break;
        total_read += n;
        buffer[total_read] = '\0';

        char *marker = strstr(buffer, "\r\n\r\n");
        if (marker != NULL) {
            header_end = (marker - buffer) + 4;

            char *cl = strstr(buffer, "Content-Length:");
            if (cl != NULL) {
                content_length = atoi(cl + 15);
            }

            int max_body = (int)sizeof(buffer) - 1 - header_end;
            if (content_length > max_body) {
                body_too_large = 1;
                break;
            }

            int body_received = total_read - header_end;
            if (body_received >= content_length) break;
        }
    }

    if (total_read <= 0) {
        close(client_fd);
        return;
    }

    char method[8];
    char path[256];
    sscanf(buffer, "%7s %255s", method, path);

    char *body = (header_end >= 0) ? buffer + header_end : NULL;

    printf("method: %s\n", method);
    printf("path: %s\n", path);

    char res[RESPONSE_BUFFER_SIZE];
    int len;

    if (body_too_large) {
        char *msg = "{\"error\": \"request body too large\"}";
        len = strlen(msg);
        snprintf(res, sizeof(res), "HTTP/1.1 413 Payload Too Large\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", len, msg);
    }
    else if (strcmp(method, "GET") == 0 && strcmp(path, "/") == 0) {
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
            const char *socket_path = pick_worker_socket();
            int ok = call_worker(socket_path, body, prediction, sizeof(prediction)) == 0;

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

void *handle_client_thread(void *arg) {
    int client_fd = *(int *)arg;
    free(arg);
    handle_client(client_fd);
    return NULL;
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
    addr.sin_port = htons(SERVER_PORT);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        exit(1);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("listening on port %d\n", SERVER_PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        int *fd_ptr = malloc(sizeof(int));
        *fd_ptr = client_fd;

        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client_thread, fd_ptr) != 0) {
            perror("thread create failed");
            free(fd_ptr);
            close(client_fd);
            continue;
        }
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
