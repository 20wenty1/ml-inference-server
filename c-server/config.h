#ifndef CONFIG_H
#define CONFIG_H

#define SERVER_PORT 8080
#define WORKER_TIMEOUT_SECONDS 3
#define REQUEST_BUFFER_SIZE 4096
#define RESPONSE_BUFFER_SIZE 512
#define NUM_WORKERS 3
#define CLIENT_TIMEOUT_SECONDS 5
#define RATE_LIMIT_WINDOW_SECONDS 10
#define RATE_LIMIT_MAX_REQUESTS 20
#define MAX_TRACKED_IPS 64

static const char *WORKER_SOCKET_PATHS[NUM_WORKERS] = {
    "/sockets/spam_worker_1.sock",
    "/sockets/spam_worker_2.sock",
    "/sockets/spam_worker_3.sock"
};

#endif



