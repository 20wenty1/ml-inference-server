# Day 7 - Logging and Monitoring

## Objective
Built on yesterday's logging foundation by making it actually useful — measuring how long inference takes, tracking when the server starts and shuts down, and understanding what observability really means in practice. Starting to see how production systems know what they're doing without someone constantly watching them.

## Information Gathered

Logging - Recording what your application is doing while it runs. Doesn't change how the app behaves, just gives you visibility into it.

Logger - Python's built-in logging module gives you a logger object that writes messages at different severity levels. More flexible than print, actually configurable.

Log Levels - How serious is this message?
- INFO - Normal stuff, everything is fine.
- WARNING - Something unexpected happened but the app kept going.
- ERROR - Something failed and an operation didn't complete.
- CRITICAL - Something is badly wrong, the app might not recover.

Request Logging - Logging incoming requests before you process them. Useful for monitoring traffic patterns and figuring out what was happening right before something broke.

Inference Latency - How long the model actually takes to return a prediction after getting input. This is the number you care about when optimizing.

time.perf_counter() - High resolution timer for measuring short durations accurately. Use this for benchmarking inference, not time.time().

Performance Monitoring - Tracking how efficiently your app is doing its job. Latency per request, throughput, that kind of thing.

Lifecycle Events - Code that runs when your FastAPI app starts up or shuts down. Useful for initializing resources or logging server status.

Lifespan - FastAPI's way of handling startup and shutdown logic using an async context manager. Cleaner than the old @app.on_event approach.

asynccontextmanager - Decorator from Python's contextlib that makes writing async setup and teardown code straightforward.

logger.info() - For logging normal behavior. Server started, request received, prediction returned.

logger.exception() - Logs an error plus the full stack trace automatically. Much more useful than just logging the error message when you're trying to debug.

Observability - Being able to understand what your application is actually doing by looking at logs, metrics, and runtime data. The goal of everything in this day.

## Key Terms
- Logging
- Logger
- Log Levels
- Request Logging
- Inference Latency
- time.perf_counter()
- Performance Monitoring
- Lifecycle Events
- Lifespan
- asynccontextmanager
- logger.info()
- logger.exception()
- Observability

## Important Questions (for me personally)
- How does Python's logging module actually work under the hood?
- What's the real difference between logging to console vs a file, and when do you switch?
- How do production systems handle massive volumes of logs without running out of storage?
- How does FastAPI's lifespan context manager work internally?
- Why is time.perf_counter() more accurate than time.time() for short duration benchmarking?
- How do large-scale ML services actually collect and monitor logs across multiple instances?