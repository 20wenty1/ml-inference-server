# ML Inference Server

A spam-detection inference server built from scratch in C, with a pool of persistent PyTorch workers connected over Unix domain sockets. Built as a personal learning project to go past frameworks and understand what's actually happening at the socket/HTTP level, with AI assistance used throughout as a tutor and pair-programmer.

## Goal

Build an HTTP server from scratch that:
- Accepts concurrent requests
- Communicates with a pool of persistent Python workers
- Runs PyTorch inference
- Returns JSON responses
- Follows the architecture of a production ML inference server

## Live Demo

Deployed and running on a DigitalOcean droplet:

```bash
curl http://139.59.91.233:8080/
curl -X POST http://139.59.91.233:8080/predict -d "WINNER! Free prize, call now to claim!"
```

## What's Working

- Raw TCP server in C (sockets, bind/listen/accept) with its own minimal HTTP parser, including a proper read loop that handles partial/chunked TCP reads correctly under load
- Multithreaded request handling — each connection is handled on its own thread, so multiple clients can be served concurrently
- A pool of 3 persistent Python workers (each loads the PyTorch model once, stays running), connected to the C server over Unix domain sockets with mutex-protected round-robin load balancing
- Timeout and error handling on the C↔worker connection and on client connections (malformed requests, empty bodies, worker unavailable/timeout all return proper HTTP status codes)
- Centralized config (`c-server/config.h`) instead of hardcoded values
- Unit tests for the inference layer (pytest) and integration tests for the HTTP endpoints (shell script against a running server)
- A load testing script (`benchmark/load_test.py`) with real before/after numbers for the worker pool (see Benchmark Results below)
- Fully containerized with Docker Compose — all 3 workers and the C server run together, sharing a Docker volume for their Unix sockets, with a restart policy so the stack survives crashes or a server reboot
- Deployed on a public DigitalOcean droplet, reachable from anywhere, not just localhost
- An earlier FastAPI/Python-only prototype (`server/`) still in the repo as a reference for how the project started

## Security

- Client connection timeout (5s) — protects against Slowloris-style stalled connections tying up a thread indefinitely
- Oversized request rejection (413) — `Content-Length` is validated against buffer capacity before it's trusted, instead of silently truncating
- IP-based rate limiting (20 requests / 10s) — mutex-protected table tracks requests per IP in a rolling window
- Worker connection timeout (3s) — a hung PyTorch worker can't hang the C server along with it
- CORS enabled — allows browser-based clients (like the project's demo site) to call the API cross-origin

## Benchmark Results

Measured with `benchmark/load_test.py`, 60 requests at concurrency 10, against the real running server:

| | 1 worker | 3 workers |
|---|---|---|
| Success rate | 58/60 | 60/60 |
| Requests/sec | 320.71 | 410.85 |
| Avg latency | 25.94ms | 23.41ms |

Along the way, this also surfaced a real bug: the C server's original request parser assumed a single `read()` call would always return the complete HTTP request. Under real concurrent load, TCP can deliver a request in multiple chunks, so a single `read()` sometimes returned before the body had fully arrived — causing false "empty body" errors. Fixed with a proper read loop that keeps reading until `Content-Length` is satisfied.

## Not Yet Built

- Benchmarking against the original FastAPI baseline (currently only 1-worker vs 3-worker C server is compared)
- CI/CD
- Health check endpoint for monitoring server/worker status individually
- A domain name / HTTPS in front of the droplet (currently plain HTTP on a raw IP)

## Tech Stack

- C
- Python
- PyTorch
- Docker
- Linux (Ubuntu 24.04)
- GCC
- Git

## How to Run

### Option 1: Docker (recommended)

`docker compose up --build`

This builds and starts all 3 Python workers and the C server together, sharing a Docker volume for their Unix sockets. Once it's up, test it the same way as below.

### Option 2: Running natively

Requires four terminals, in this order:

**1-3. Start each Python worker**
```bash
python -m worker.server /tmp/spam_worker_1.sock
python -m worker.server /tmp/spam_worker_2.sock
python -m worker.server /tmp/spam_worker_3.sock
```

**4. Compile and start the C server**
```bash
gcc c-server/main.c -o c-server/server -lpthread
./c-server/server
```

**Test it**
```bash
curl http://localhost:8080/
curl -X POST http://localhost:8080/predict -d "WINNER! Free prize, call now to claim!"
```

## Running Tests

```bash
python -m pytest tests/ -v
./tests/test_server.sh
```
(requires the worker(s) and C server both running for the second one)

## Running the Benchmark

```bash
python benchmark/load_test.py
```
(requires the worker(s) and C server both running)

## Status

✅ Core project complete — all 18 planned days done, plus security hardening and a live public deployment. See `docs/roadmap.md` for what's left beyond the original scope (CI/CD, HTTPS/domain).