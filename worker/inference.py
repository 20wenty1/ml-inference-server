from worker.loader import model


def predict(text: str):
    prediction = model.predict([text])

    return prediction[0]