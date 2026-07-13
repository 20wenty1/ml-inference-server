# Day 3 - Request Validation & POST Endpoints

## Objective

Built my first POST endpoint and learned how FastAPI validates incoming JSON using Pydantic models before my code executes.

## Information Gathered

POST Request - Unlike GET requests, POST requests send data inside the request body. They are commonly used when a client wants to submit information to the server.

Request Body - The request body contains the JSON data sent by the client. FastAPI automatically reads and converts it into a Python object.

Pydantic - Pydantic is responsible for validating incoming data. If the data doesn't match the expected types, FastAPI automatically returns a validation error.

BaseModel - BaseModel is the class used to define the structure of incoming data. Each field has a type, allowing FastAPI to validate requests.

Request Validation - Before my endpoint function runs, FastAPI checks whether the request matches the BaseModel. Invalid requests never reach my function.

JSON Schema - FastAPI automatically generates documentation describing what JSON the endpoint expects.

Swagger UI - Swagger provides an interactive webpage where I can test my API without writing client code.

HTTP 422 - FastAPI returns HTTP 422 when the request body is missing required fields or contains invalid data.

## Key Terms

- POST
- Request Body
- JSON
- Pydantic
- BaseModel
- Request Validation
- Swagger UI
- HTTP 422
- API Documentation

## Important Questions (for me personally)

- Why does FastAPI automatically know to read JSON into a BaseModel?
- What happens internally before my function executes?
- Why does invalid data never reach my endpoint?
- How can I make some fields optional?
- What are nested Pydantic models?