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
        logger.info("Prediction request received")

        prediction = predict(request.text)

        logger.info(f"Prediction: {prediction}")

        return {
            "success": True,
            "prediction": prediction
        }

    except Exception as e:
        logger.error(f"Prediction failed: {e}")

        raise HTTPException(
            status_code=500,
            detail="Prediction failed"
        )
    

    
    
