from fastapi import FastAPI

app = FastAPI(
    title="ML Inference Server",
    description="A production-style ML inference server built with FastAPI",
    version="0.1.0"
)


@app.get("/")
async def root():
    return {
        "status": "running",
        "message": "ML Inference Server is online"
    }