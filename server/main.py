from fastapi import FastAPI
from pydantic import BaseModel

from worker.inference import predict

app = FastAPI(
    title="ML Inference Server",
    description="A ML inference server built with FastAPI",
)


class PredictionRequest(BaseModel):
    text: str


@app.get("/")
async def root():
    return {
        "status": "Running",
        "message": "ML Inference Server is online",
    }


@app.post("/predict")
async def predict_endpoint(data: PredictionRequest):
    prediction = predict(data.text)

    return {
        "prediction": prediction
    }
    
    