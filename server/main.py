from fastapi import FastAPI
from server.api.routes import router

app = FastAPI(
    title="ML Inference Server",
    description="A ML inference server built with FastAPI",
)

app.include_router(router)

