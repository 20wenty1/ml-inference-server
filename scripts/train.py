import pandas as pd
import joblib

from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline

df = pd.read_csv("data/spam.csv")

print(df.head())

X = df["text"]
y = df["label"]

model = Pipeline(
    [
        ("tfidf", TfidfVectorizer()),
        ("classifier", MultinomialNB())
    ]
)

model.fit(X, y)

joblib.dump(model, "models/spam_model.joblib")

print("Training complete!")
print("Model saved successfully!")

