# ML Inference Server

A spam-detection inference server built from scratch in C, connected to a persistent PyTorch worker over a Unix domain socket. Built as a personal learning project to go past frameworks and understand what's actually happening at the socket/HTTP level, with AI assistance used throughout as a tutor and pair-programmer.

## Goal

Build an HTTP server from scratch that:
- Accepts concurrent requests
- Communicates with a persistent Python worker
- Runs PyTorch inference
- Returns JSON responses
- Follows the architecture of a production ML inference server

## What's Working

- Raw TCP server in C (sockets, bind/listen/accept) with its own minimal HTTP parser
- Multithreaded request handling — each connection is handled on its own thread, so multiple clients can be served concurrently
- A persistent Python worker (loads the PyTorch model once, stays running) connected to the C server over a Unix domain socket
- Timeout and error handling on the C↔worker connection (malformed requests, empty bodies, worker unavailable/timeout all return proper HTTP status codes)
- Centralized config (`c-server/config.h`) instead of hardcoded values
- Unit tests for the inference layer (pytest) and integration tests for the HTTP endpoints (shell script against a running server)
- An earlier FastAPI/Python-only prototype (`server/`) still in the repo as a baseline for future benchmarking

## Not Yet Built

- A worker pool (currently one Python worker process, so predictions themselves are not yet parallel — see `docs/roadmap.md`)
- Benchmarking against the FastAPI baseline
- Docker packaging
- CI/CD
- Health check endpoint for monitoring server/worker status 

## Tech Stack

- C
- Python
- PyTorch
- Linux (Ubuntu 24.04)
- GCC
- Git

## How to Run

Requires three terminals, in this order:

**1. Start the Python worker**
```bash
python -m worker.server
```

**2. Compile and start the C server**
```bash
gcc c-server/main.c -o c-server/server -lpthread
./c-server/server
```

**3. Test it**
```bash
curl http://localhost:8080/
curl -X POST http://localhost:8080/predict -d "WINNER! Free prize, call now to claim!"
```

## Running Tests

```bash
python -m pytest tests/ -v
./tests/test_server.sh
```
(requires the worker and C server both running for the second one)

## Status

🚧 Actively in progress — see `docs/roadmap.md` for what's done and what's next.