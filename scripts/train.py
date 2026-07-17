import pandas as pd
import joblib
import torch
import torch.nn as nn
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import train_test_split

df = pd.read_csv("data/spam.csv")
X = df["text"]
y = df["label"].map({"ham": 0, "spam": 1})

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

vec = TfidfVectorizer(max_features=3000)
X_train_vec = vec.fit_transform(X_train).toarray()
X_test_vec = vec.transform(X_test).toarray()

X_train_t = torch.tensor(X_train_vec, dtype=torch.float32)
y_train_t = torch.tensor(y_train.values, dtype=torch.float32).unsqueeze(1)
X_test_t = torch.tensor(X_test_vec, dtype=torch.float32)
y_test_t = torch.tensor(y_test.values, dtype=torch.float32).unsqueeze(1)

class SpamNet(nn.Module):
    def __init__(self, input_dim):
        super().__init__()
        self.fc1 = nn.Linear(input_dim, 64)
        self.fc2 = nn.Linear(64, 1)

    def forward(self, x):
        x = torch.relu(self.fc1(x))
        return self.fc2(x)

model = SpamNet(X_train_t.shape[1])
opt = torch.optim.Adam(model.parameters(), lr=0.001)

spam_weight = (y_train == 0).sum() / (y_train == 1).sum()
loss_fn = nn.BCEWithLogitsLoss(pos_weight=torch.tensor([spam_weight]))

for epoch in range(20):
    model.train()
    opt.zero_grad()
    out = model(X_train_t)
    loss = loss_fn(out, y_train_t)
    loss.backward()
    opt.step()
    print(f"epoch {epoch+1} loss {loss.item():.4f}")

model.eval()
with torch.no_grad():
    preds = (torch.sigmoid(model(X_test_t)) > 0.5).float()
    acc = (preds == y_test_t).float().mean()
    print("test acc:", acc.item())

torch.save(model.state_dict(), "models/spam_model.pt")
joblib.dump(vec, "models/vectorizer.joblib")
print("done training")

