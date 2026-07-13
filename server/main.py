from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI(
    title="ML Inference Server",
    description="A ML inference server built with FastAPI",
)


class PredictionRequest(BaseModel):
    age: int
    salary: float


@app.get("/")
async def root():
    return {
        "status": "running",
        "message": "ML Inference Server is online"
    }


@app.post("/predict")
async def predict(data: PredictionRequest):
    return {
        "received": data,
        "prediction": "test_prediction"
    }
    
    