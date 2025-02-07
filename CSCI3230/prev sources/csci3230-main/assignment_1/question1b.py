import numpy as np

# Input data
data = np.array([
    [5.86, 0.74],
    [1.34, 1.18],
    [3.65, 0.51],
    [4.69, -0.48],
    [4.13, -0.07],
    [5.87, 0.37],
    [7.91, 1.35],
    [5.57, 0.30],
    [7.30, 1.64],
    [7.89, 1.75]
])

X = data[:, 0]  # Input variables (x)
Y = data[:, 1]  # Output variables (y)

print(X)
print(Y)
print("X*Y",X*Y)

# Calculate the parameters
X_mean = np.mean(X)
# print("X_mean", X_mean)
Y_mean = np.mean(Y)

print("(X - X_mean) * (Y - Y_mean)",(X - X_mean) * (Y - Y_mean))
# 
# theta_2 = np.sum((X - X_mean) * (Y - Y_mean)) / np.sum((X - X_mean) ** 2)
theta_1 = np.sum((X - X_mean) * (Y - Y_mean)) / np.sum((X - X_mean) ** 2)
theta_0 = Y_mean - theta_1 * X_mean

print("Theta 0:", theta_0)
print("Theta 1:", theta_1)

# import matplotlib.pyplot as plt
#
# # Plotting the data points
# plt.scatter(X, Y, color='blue', label='Data Points')
#
# # Calculate the predicted values using the linear model
# Y_pred = theta_0 + theta_1 * X
#
# # Plotting the linear model
# plt.plot(X, Y_pred, color='red', label='Linear Model')
#
# # Set labels and title
# plt.xlabel('X')
# plt.ylabel('Y')
# plt.title('Linear Model')
#
# # Add legend
# plt.legend()
#
# # Display the plot
# plt.show()
