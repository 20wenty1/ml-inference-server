# ML Inference Server Roadmap

## Phase 1 - Networking Fundamentals

- [x] Day 1 - Project Setup & How the Internet Works
- [x] Day 2 - What Happens When You Type `google.com`
- [x] Day 3 - DNS, IP Addresses & Routing
- [x] Day 4 - TCP & The Three-Way Handshake
- [x] Day 5 - Sockets
- [x] Day 6 - Processes, Threads & Concurrency

## Phase 2 - Server Development

- [x] Day 7 - Create a TCP Server
- [x] Day 8 - Accept Connections & Handle Multiple Clients
- [x] Day 9 - Understanding HTTP
- [x] Day 10 - Parse HTTP Requests & Build Responses
- [x] Day 11 - Project Refactoring & Clean Architecture

## Phase 3 - ML Worker

- [x] Day 12 - Python Worker Architecture & IPC
- [x] Day 13 - Load the PyTorch Model & Run Inference
- [x] Day 14 - Connect the C Server to the Python Worker

## Phase 4 - Production Features

- [x] Day 15 - Worker Pool & Concurrent Request Handling (3 Python workers running concurrently; C server round-robins between them with a mutex-protected index)
- [x] Day 16 - Logging, Configuration & Error Handling
- [x] Day 17 - Testing, Benchmarking & Performance Optimization (unit + integration tests pass; benchmarked 1-worker vs 3-worker pool — found and fixed a partial-read bug under concurrent load along the way, see benchmark/load_test.py)
- [x] Day 18 - Docker, Documentation & Final Polish (Dockerfiles for the C server and worker, docker-compose to run the full stack with a shared volume for Unix sockets, README and roadmap brought up to date)