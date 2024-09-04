import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Step 1: Load the data points from "random_generated_data.csv"
data = pd.read_csv("random_generated_data.csv")

# Step 2: Plot the data points
plt.scatter(data['x'], data['y'])
plt.xlabel('x')
plt.ylabel('y')
plt.title('Data Points')
plt.show()

# Step 3: Implement the K-means algorithm
def kmeans(data, k, max_iterations=100):
    # Initialize cluster centers randomly
    np.random.seed(0)
    centers = np.random.randn(k, 2)

    # Iterate until convergence or max_iterations reached
    for _ in range(max_iterations):
        # Assign data points to the nearest cluster center
        distances = np.linalg.norm(data[:, np.newaxis] - centers, axis=2)
        assigned_clusters = np.argmin(distances, axis=1)

        # Update cluster centers
        for i in range(k):
            centers[i] = np.mean(data[assigned_clusters == i], axis=0)

    # Compute the sum of squared distances
    distances = np.linalg.norm(data[:, np.newaxis] - centers, axis=2)
    sum_squared_distances = np.sum(np.min(distances, axis=1))

    return assigned_clusters, centers, sum_squared_distances

# Convert data to numpy array
data_array = data[['x', 'y']].values

# Fit the data points with k-means algorithm
k = 5
assigned_clusters, centers, sum_squared_distances = kmeans(data_array, k)

# Plot the prediction results
colors = ['red', 'green', 'blue', 'orange', 'purple']
plt.scatter(data['x'], data['y'], c=assigned_clusters, cmap='rainbow')
plt.scatter(centers[:, 0], centers[:, 1], c='black', marker='x')
plt.xlabel('x')
plt.ylabel('y')
plt.title(f'K-means Clustering (k={k})')
plt.show()

# Report the number of iterations and sum of squared distances
num_iterations = 100
print(f"Number of iterations: {num_iterations}")
print(f"Sum of squared distances: {sum_squared_distances}")

# Step 4: Repeat the fitting with different cluster numbers
cluster_numbers = [1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12]

for k in cluster_numbers:
    assigned_clusters, centers, sum_squared_distances = kmeans(data_array, k)
    plt.scatter(data['x'], data['y'], c=assigned_clusters, cmap='rainbow')
    plt.scatter(centers[:, 0], centers[:, 1], c='black', marker='x')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title(f'K-means Clustering (k={k})')
    plt.show()