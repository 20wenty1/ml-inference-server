# Day 2 - FastAPI Basics

## Objective

Built the foundation of my ML Inference Server using FastAPI and understood how an HTTP request reaches my Python code.

## Information Gathered

FastAPI - FastAPI is the framework I'm using to build my inference server. It lets me create API endpoints that other programs can send requests to. It also automatically creates API documentation and converts my Python responses into JSON.

API - An API is simply a way for two programs to communicate. Instead of another application accessing my code directly, it sends a request to one of the endpoints I expose and receives a response.

Uvicorn - Uvicorn is what actually runs my FastAPI application. It waits for incoming requests, passes them to FastAPI, and sends the response back to whoever made the request.

Routes - A route connects a URL (like `/`) to a Python function. When someone visits that URL or sends a request to it, FastAPI runs the corresponding function.

JSON - JSON is the format used to exchange data between applications. When my function returns a Python dictionary, FastAPI automatically converts it into JSON before sending it back.

Localhost (127.0.0.1) - Localhost always refers to my own computer. Any request sent to `127.0.0.1` stays on my machine, which is why it's used while developing and testing applications.

## Key Terms

- FastAPI
- API
- Uvicorn
- Route
- Endpoint
- JSON
- Localhost
- Loopback Address
- ASGI

## Imp Questions ( for me personally )

- How does @app.get() register a route?
- Why do we use async instead of a normal function?
- How does FastAPI automatically convert dictionaries into JSON?
- How does Uvicorn find the app object?
- What happens internally when multiple clients access the server at the same time?