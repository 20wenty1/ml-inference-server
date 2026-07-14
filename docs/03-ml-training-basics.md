# Day 4 - ML Training Basics

## Objective

Started building the machine learning component of my inference server. Learned how a model is trained, how training differs from inference, and how the training script fits into the overall project architecture.

## Information Gathered

Machine Learning Model - A trained program that learns patterns from data and can make predictions on unseen inputs.

Training - The process of teaching a model using a labeled dataset. Training only happens during development and produces a trained model.

Inference - The process of using an already trained model to make predictions. This is what happens every time a client sends a request to the server.

Features (X) - The input data provided to the model. For this project, X represents the email or SMS text.

Labels (y) - The correct answers associated with each input.

Pandas - A Python library used for reading and working with structured datasets. It loads CSV files into DataFrames.

DataFrame - A tabular data structure provided by pandas that stores rows and columns of data.

Joblib - A library used to serialize (save) trained Python objects so they can be loaded later without retraining.

Serialization - The process of converting an object in memory into a file that can be stored on disk.

Project Structure - Separated the project into dedicated folders for datasets, models, scripts, the inference worker, and the server to keep responsibilities organized.

Training Script (train.py) - A standalone script responsible for loading data, training the model, and saving the trained pipeline. It is never executed during normal API requests.

## Key Terms

- Machine Learning
- Training
- Inference
- Features (X)
- Labels (y)
- Pandas
- DataFrame
- Joblib
- Serialization
- train.py

## Important Questions (for me personally)

- Why do machine learning models require numerical input instead of raw text?
- What exactly does TF-IDF do?
- Why is Multinomial Naive Bayes commonly used for spam detection?
- What does scikit-learn's Pipeline class actually do internally?
- What is stored inside spam_pipeline.pkl?
- How does the Python worker load the trained model and make predictions?