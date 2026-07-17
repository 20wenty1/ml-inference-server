import time
from fastapi import APIRouter, HTTPException
from pydantic import BaseModel
from worker.inference import predict
from server.core.logger import logger


router = APIRouter()


class PredictionRequest(BaseModel):
    text: str


@router.get("/")
def root():
    logger.info("Root endpoint accessed")
    return {"message": "Spam detection API is running"}


@router.post("/predict")
def predict_text(request: PredictionRequest):
    try:
        logger.info(f"Prediction request received: {request.text}")
        start = time.perf_counter()
        prediction = predict(request.text)
        elapsed = (time.perf_counter() - start) * 1000

        logger.info(f"Prediction: {prediction} | Inference Time: {elapsed:.2f} ms")

        return {
            "success": True,
            "prediction": prediction
        }

    except Exception:
        logger.exception("Prediction failed")
        raise HTTPException(
            status_code=500,
            detail="Prediction failed"
        )
    

