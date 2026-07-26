FROM gcc:13 AS builder

WORKDIR /app
COPY c-server/main.c c-server/config.h ./

RUN gcc main.c -o server -lpthread

FROM debian:bookworm-slim

WORKDIR /app
COPY --from=builder /app/server ./server

EXPOSE 8080

CMD ["./server"]

