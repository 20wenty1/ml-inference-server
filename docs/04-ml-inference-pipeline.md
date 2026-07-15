# Day 5 - Building the ML Inference Pipeline

## Objective

Connected the trained machine learning model to the FastAPI server. Learned how trained models are saved, loaded, and used to make real-time predictions while separating training, inference, and API responsibilities.

## Information Gathered

Training - The process of teaching a machine learning model using labeled data. It only happens when creating or updating a model.

Inference - The process of using a trained model to make predictions on new, unseen data. This is what happens whenever a client sends a prediction request.

Serialization - The process of converting a Python object into a file so it can be stored on disk and loaded later.

Joblib - A Python library commonly used to save and load trained scikit-learn models efficiently.

joblib.dump() - Saves a trained model or pipeline to a file so it can be reused without retraining.

joblib.load() - Loads a previously saved model back into memory.

Pipeline - A scikit-learn object that combines preprocessing steps (TF-IDF Vectorizer) and the machine learning model (Multinomial Naive Bayes) into a single object. Saving the entire pipeline preserves both preprocessing and prediction logic.

Model Loader (loader.py) - Responsible for loading the trained model into memory when the server starts.

Inference Function (inference.py) - Responsible for receiving input text, passing it to the loaded model, and returning the prediction.

FastAPI Endpoint - Receives HTTP requests, validates the incoming data using Pydantic, calls the inference function, and returns the prediction as JSON.

Single Responsibility Principle (SRP) - A software engineering principle stating that each module or file should have one clear responsibility. Training, model loading, inference, and the API are separated into different files.

Model Loading Strategy - The model is loaded once when the server starts instead of being loaded for every request. This improves performance because disk access is much slower than using an object already stored in memory.

Python Import Caching - Python imports each module only once during execution. After the first import, the loaded module is reused, allowing the model to stay in memory for all future prediction requests.

Inference Server - A server that exposes a trained machine learning model through an HTTP API, allowing clients to send data and receive predictions.

## Key Terms

- Training
- Inference
- Serialization
- Joblib
- joblib.dump()
- joblib.load()
- Pipeline
- Single Responsibility Principle (SRP)
- Model Loader
- Inference Function
- FastAPI Endpoint
- Inference Server

## Important Questions (for me personally)

- How does TF-IDF convert text into numerical vectors internally?
- How does Multinomial Naive Bayes calculate probabilities?
- How does Python cache imported modules?
- What exactly happens inside joblib.dump() and joblib.load()?
- How does scikit-learn's Pipeline execute each step during prediction?
- How can the inference server return prediction confidence using predict_proba()?
- How can this architecture be scaled to support multiple models?