import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import Dataset, DataLoader
import torchvision
import torchvision.transforms as transforms
from torchvision.datasets import ImageFolder
import timm

import matplotlib.pyplot as plt  # For data viz
import pandas as pd
import numpy as np
import sys
from tqdm import tqdm


print('System Version:', sys.version)
print('PyTorch version', torch.__version__)
print('Torchvision version', torchvision.__version__)
print('Numpy version', np.__version__)
print('Pandas version', pd.__version__)

#Step 1.Pytorch Dataset( and Dataloader)


class PlayingCardDataset(Dataset):
    def __init__(self, data_dir, transform=None):
        self.data = ImageFolder(data_dir, transform=transform)

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        return self.data[idx]

    @property
    def classes(self):
        return self.data.classes


#Create Test Dataset
dataset = PlayingCardDataset(
    data_dir=r'C:\Users\Pavel\Downloads\PlantsDataSet'
)
len(dataset)
image, label = dataset[6000]
print(label)


# Get a dictionary associating target values with folder names
data_dir = r'C:\Users\Pavel\Downloads\PlantsDataSet'
target_to_class = {v: k for k, v in ImageFolder(data_dir).class_to_idx.items()}
print(target_to_class)

transform = transforms.Compose([
    transforms.Resize((128, 128)),
    transforms.ToTensor(),
])

data_dir = r'C:\Users\Pavel\Downloads\PlantsDataSet'
dataset = PlayingCardDataset(data_dir, transform)

image, label = dataset[100]
image.shape

# iterate over dataset
for image, label in dataset:
    break

# Dataloaders

dataloader = DataLoader(dataset, batch_size=196, shuffle=True)
for images, labels in dataloader:
    break
images.shape, labels.shape

# labels

#Step 2. Pytorch Model


class SimpleCardClassifier(nn.Module):
    def __init__(self, num_classes=38):
        super(SimpleCardClassifier, self).__init__()
        # Where we define all the parts of the model
        self.base_model = timm.create_model('efficientnet_b0', pretrained=True)
        self.features = nn.Sequential(*list(self.base_model.children())[:-1])

        enet_out_size = 1280
        # Make a classifier
        self.classifier = nn.Sequential(
            nn.Flatten(),
            nn.Linear(enet_out_size, num_classes)
        )

    def forward(self, x):
        # Connect these parts and return the output
        x = self.features(x)
        output = self.classifier(x)
        return output

model = SimpleCardClassifier(num_classes=38)


print(str(model)[:500])
example_out = model(images)
example_out.shape  # [batch_size, num_classes]

#Step3.The training loop
# Loss function
criterion = nn.CrossEntropyLoss()
# Optimizer
optimizer = optim.Adam(model.parameters(), lr=0.001)
criterion(example_out, labels)
print("Example shape\n")
print(example_out.shape, labels.shape)

#Setup Datasets
transform = transforms.Compose([
    transforms.Resize((128, 128)),
    transforms.ToTensor(),
])

train_folder = r'C:\Users\Pavel\Downloads\PlantsDataSet\train'
valid_folder = r'C:\Users\Pavel\Downloads\PlantsDataSet\valid'
test_folder = r'C:\Users\Pavel\Downloads\PlantsDataSet\test'

train_dataset = PlayingCardDataset(train_folder, transform=transform)
val_dataset = PlayingCardDataset(valid_folder, transform=transform)
test_dataset = PlayingCardDataset(test_folder, transform=transform)

train_loader = DataLoader(train_dataset, batch_size=196, shuffle=True)
val_loader = DataLoader(val_dataset, batch_size=196, shuffle=False)
test_loader = DataLoader(val_dataset, batch_size=196, shuffle=False)

# Simple
# Training
# Loop

# Simple training loop
num_epochs = 5
train_losses, val_losses = [], []

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")


model = SimpleCardClassifier(num_classes=38)
model.to(device)

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

for epoch in range(num_epochs):
    # Training phase
    model.train()
    running_loss = 0.0
    for images, labels in tqdm(train_loader, desc='Training loop'):
        # Move inputs and labels to the device
        images, labels = images.to(device), labels.to(device)

        optimizer.zero_grad()
        outputs = model(images)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
        running_loss += loss.item() * labels.size(0)
    train_loss = running_loss / len(train_loader.dataset)
    train_losses.append(train_loss)

    # Validation phase
    model.eval()
    running_loss = 0.0
    with torch.no_grad():
        for images, labels in tqdm(val_loader, desc='Validation loop'):
            # Move inputs and labels to the device
            images, labels = images.to(device), labels.to(device)

            outputs = model(images)
            loss = criterion(outputs, labels)
            running_loss += loss.item() * labels.size(0)
    val_loss = running_loss / len(val_loader.dataset)
    val_losses.append(val_loss)
    print(f"Epoch {epoch + 1}/{num_epochs} - Train loss: {train_loss}, Validation loss: {val_loss}\n")