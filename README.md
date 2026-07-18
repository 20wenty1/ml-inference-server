# ML Inference Server

Python/FastAPI prototype complete. C HTTP server now connects to a persistent PyTorch worker over a Unix domain socket for live predictions.

## Goal

Build an HTTP server from scratch that:
- Accepts concurrent requests
- Communicates with a persistent Python worker
- Runs PyTorch inference
- Returns JSON responses
- Follows the architecture of a production ML inference server

## Tech Stack

- C
- Python
- PyTorch
- Linux (Ubuntu 24.04)
- GCC
- Git
- CMake

## Status

🚧 Learning Phase
