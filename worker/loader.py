import joblib
import torch
import torch.nn as nn

vectorizer = joblib.load("models/vectorizer.joblib")

class SpamNet(nn.Module):
    def __init__(self, input_dim):
        super().__init__()
        self.fc1 = nn.Linear(input_dim, 128)
        self.drop = nn.Dropout(0.2)
        self.fc2 = nn.Linear(128, 32)
        self.fc3 = nn.Linear(32, 1)

    def forward(self, x):
        x = torch.relu(self.fc1(x))
        x = self.drop(x)
        x = torch.relu(self.fc2(x))
        return self.fc3(x)

input_dim = len(vectorizer.get_feature_names_out())
model = SpamNet(input_dim)
model.load_state_dict(torch.load("models/spam_model.pt"))
model.eval()

