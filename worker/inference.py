import torch
from worker.loader import model, vectorizer

def predict(text: str):
    vec = vectorizer.transform([text]).toarray()
    x = torch.tensor(vec, dtype=torch.float32)
    with torch.no_grad():
        out = torch.sigmoid(model(x))
    return "spam" if out.item() > 0.5 else "ham"

