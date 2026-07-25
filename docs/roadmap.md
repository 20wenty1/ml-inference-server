# ML Inference Server Roadmap

## Phase 1 - Networking Fundamentals

- [x] Day 1 - Project Setup & How the Internet Works
- [x] Day 2 - What Happens When You Type `google.com`
- [ ] Day 3 - DNS, IP Addresses & Routing
- [ ] Day 4 - TCP & The Three-Way Handshake
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

- [ ] Day 15 - Worker Pool & Concurrent Request Handling (C server is multithreaded; Python worker is still a single process — next: run multiple worker processes and have the C server pick between them per request)
- [x] Day 16 - Logging, Configuration & Error Handling
- [ ] Day 17 - Testing, Benchmarking & Performance Optimization (unit + integration tests done; benchmarking not started)
- [ ] Day 18 - Docker, Documentation & Final Polish