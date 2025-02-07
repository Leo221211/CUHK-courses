import torch
from torch import nn
from torch.utils.data import DataLoader
import numpy as np
from torch.utils.data import Dataset
import pandas as pd
from tqdm import tqdm
import matplotlib.pyplot as plt

# Set the seed for reproducibility
seed = 1443
torch.manual_seed(seed)
np.random.seed(seed)


# Define the custom dataset
class Data(Dataset):
    def __init__(self, csv_file, transform=None):
        super(Data, self).__init__()
        file = pd.read_csv(csv_file)
        self.input_data = file[['x1', 'x2']].values
        self.labels = file['y'].values.astype(int)

    def __getitem__(self, index):
        data_item = self.input_data[index]
        data_item = torch.tensor(data_item).float()

        label = self.labels[index]
        return data_item, label

    def __len__(self):
        return len(self.input_data)


# Create train and test datasets
train_data = Data('train_q4.csv')
test_data = Data('test_q4.csv')

# Set batch size
batch_size = 256


# Define the neural network model
class NeuralNetwork(nn.Module):
    def __init__(self):
        super(NeuralNetwork, self).__init__()
        self.linear_relu_stack = nn.Sequential(
            nn.Linear(2, 4),
            nn.ReLU(),
            nn.Linear(4, 4),
            nn.ReLU(),
            nn.Linear(4, 3),
            nn.Softmax(dim=1)
        )
        self.initialize_weights()

    def forward(self, x):
        logits = self.linear_relu_stack(x)
        return logits

    def initialize_weights(self):
        for m in self.modules():
            if isinstance(m, nn.Linear):
                # Initialize weights using He initialization
                nn.init.kaiming_uniform_(m.weight)

                if m.bias is not None:
                    nn.init.zeros_(m.bias)


# Create data loaders
train_dataloader = DataLoader(train_data, batch_size=batch_size)
test_dataloader = DataLoader(test_data, batch_size=batch_size)

# Set device (CPU or GPU)
device = "cuda" if torch.cuda.is_available() else "cpu"

# Initialize the model
model = NeuralNetwork().to(device)

# Set the learning rate and loss function
learning_rate = 0.1
loss_fn = nn.CrossEntropyLoss()

# Set the optimizer
optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)

# Training loop
epochs = 100
train_loss_data = []
for epoch in tqdm(range(epochs)):
    train_loss, correct = 0, 0
    for X, y in train_dataloader:
        X, y = X.to(device), y.to(device)

        pred = model(X)

        loss = loss_fn(pred, y.long())

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        train_loss += loss.item()
        correct += (pred.argmax(1) == y).type(torch.float).sum().item()

    size = len(train_dataloader.dataset)
    train_loss /= len(train_dataloader)
    train_loss_data.append(train_loss)
    correct /= size

    if epoch % 20 == 0:
        print(f"Train accuracy: {(100 * correct):>0.1f}%, Avg loss: {train_loss:>8f}")

# Evaluate the model on the test set
model.eval()
test_correct = 0
with torch.no_grad():
    for X, y in test_dataloader:
        X, y = X.to(device), y.to(device)
        pred = model(X)
        test_correct += (pred.argmax(1) == y).type(torch.float).sum().item()

test_accuracy = (test_correct / len(test_dataloader.dataset)) * 100
print(f"Test accuracy: {test_accuracy:.1f}%")

# Plot the training loss
# Plot the training loss
plt.plot(range(1, epochs + 1), train_loss_data, label="Training loss")
plt.title("Training Loss Over Epochs")  # Add the title here
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.grid(True)
plt.legend()
plt.show()