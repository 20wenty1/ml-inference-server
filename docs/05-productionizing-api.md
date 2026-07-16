# Day 6 - Productionizing the API

## Objective
Made the inference server feel less like a script and more like something you'd actually run in production. Added structured logging, centralized error handling, and cleaned up how the project is organized. Started understanding how real APIs monitor what's happening and deal with things going wrong.

## Information Gathered

Production API - An API that's built to actually be reliable in the real world, not just work on your machine. That means logging, proper error handling, and code that's organized enough for someone else to understand.

Logging - Recording what your application is doing while it runs. Without this you're blind when something breaks in production.

Logger - An object that handles writing log messages at different severity levels. Cleaner than print statements and actually configurable.

Log Levels - How you classify how serious a log message is.

INFO - Normal stuff. Server started, request came in, prediction returned successfully.

ERROR - Something broke and needs attention.

Exception Handling - Wrapping risky code in try-except so the app recovers gracefully instead of just dying.

HTTPException - FastAPI's way of sending a clean structured error back to the client instead of leaking internal details.

Application Flow - Request comes in → validated → logged → hits inference layer → model runs → logged again → response returned. Each step is distinct.

Separation of Concerns - Each part of the codebase does one job. API handles HTTP, inference layer runs predictions, loader manages the model, logger handles recording. When something breaks you know where to look.

Centralized Logging - One dedicated logging module that everything imports. Consistent format everywhere instead of everyone doing their own thing.

Error Response - Structured JSON the client gets back when something fails. No stack traces exposed.

Production Readiness - Going beyond "it works" to "it works reliably, you can monitor it, and you can debug it when it doesn't."

## Key Terms
- Production API
- Logging
- Logger
- Log Levels
- INFO
- ERROR
- Exception Handling
- HTTPException
- Application Flow
- Separation of Concerns
- Centralized Logging
- Error Response
- Production Readiness

## Important Questions (for me personally)
- How do logging frameworks write to files instead of just the terminal?
- What's the practical difference between WARNING, ERROR, and CRITICAL — when do you actually use each?
- How do tools like ELK or Grafana collect and visualize logs from a running server?
- What happens to exceptions that slip past your try-except blocks in FastAPI?
- Can middleware automatically log every request and response without adding logger calls everywhere?
- How does log rotation work when files get too large?
- What should I add next — authentication, Docker, tests, rate limiting?