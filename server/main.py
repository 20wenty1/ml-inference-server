from contextlib import asynccontextmanager
from fastapi import FastAPI
from server.api.routes import router
from server.core.logger import logger

@asynccontextmanager
async def lifespan(app: FastAPI):
    logger.info("ML Inference Server started")
    yield
    logger.info("ML Inference Server shutting down")

app = FastAPI(
    title="ML Inference Server (Original Prototype)",
    description="Early FastAPI/Python prototype. Superseded by a C server with a threaded PyTorch worker pool — see the project README.",
    lifespan=lifespan,
)

app.include_router(router)

