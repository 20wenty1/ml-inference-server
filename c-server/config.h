#ifndef CONFIG_H
#define CONFIG_H

#define SERVER_PORT 8080
#define WORKER_TIMEOUT_SECONDS 3
#define REQUEST_BUFFER_SIZE 4096
#define RESPONSE_BUFFER_SIZE 512
#define NUM_WORKERS 3

static const char *WORKER_SOCKET_PATHS[NUM_WORKERS] = {
    "/tmp/spam_worker_1.sock",
    "/tmp/spam_worker_2.sock",
    "/tmp/spam_worker_3.sock"
};

#endif

