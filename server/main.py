from fastapi import FastAPI

app = FastAPI(
    title="ML Inference Server",
    description="A ML inference server built with FastAPI",
)


@app.get("/")
async def root():
    return {
        "status": "running",
        "message": "ML Inference Server is online"
    }
    