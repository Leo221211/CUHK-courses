import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def kmeans(features, k, num_iters=10000):
    N = features.shape[0]

    # init
    idxs = np.random.choice(N, size=k, replace=False)
    centers = features[idxs]
    assignments = np.zeros(N, dtype=np.uint32)

    # fit
    for it_cnt in range(num_iters):
        assignments_prev = assignments.copy()

        for i in range(N):      # all points
            # find square dist to each center
            square_dist = (features[i] - centers) ** 2
            square_dist = np.sum(square_dist, axis=-1)

            # assign to the closest center
            assignments[i] = np.argmin(square_dist)

        for c in range(k):
            centers[c] = np.mean(features[assignments == c], axis=0)

        # check assignment
        if np.array_equal(assignments_prev, assignments):
            break

    # find sum
    sum_squared_distances = 0
    for i in range(N):
        sum_squared_distances += np.sum((features[i] - centers[assignments[i]]) ** 2)
        
    return assignments, it_cnt+1, sum_squared_distances, centers

'''
question 1
'''
print("question 1: the data points are ploted")
data = pd.read_csv("random_generated_data.csv", header=None, names=['x', 'y'])

plt.subplot(3, 5, 1)
plt.scatter(data['x'], data['y'])
plt.xlabel('x')
plt.ylabel('y')
plt.title('Data Points')


'''
question 2
'''
print("\n question 2")
# convert to np array
data_array = data[['x', 'y']].values
# print(data_array)

# fit
asm, num_iter, sum_sq_dist_5, centers = kmeans(data_array, 5)

# plot and report
plt.subplot(3, 5, 2)
plt.scatter(data['x'], data['y'], c=asm)
plt.scatter(centers[:, 0], centers[:, 1], c='red', marker='X', label='Cluster Centers')
plt.xlabel('x')
plt.ylabel('y')
plt.title('k=5')
plt.legend()
print(f"for k = 5, number of iteration is {num_iter}, sum of squared distances is {sum_sq_dist_5}")


'''
question 3
'''
list_sum_sq_dist = []
print("\n question 3")
for i in range(1, 13):
    if i == 5:
        list_sum_sq_dist.append(sum_sq_dist_5)
        continue

    # fit
    asm, num_iter, sum_sq_dist, centers = kmeans(data_array, i)
    list_sum_sq_dist.append(sum_sq_dist)

    # plot and report
    plt.subplot(3, 5, 2+i)
    plt.scatter(data['x'], data['y'], c=asm)
    plt.scatter(centers[:, 0], centers[:, 1], c='red', marker='X', label='Cluster Centers')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title(f'k={i}')
    plt.legend()
    print(f"for k = {i}, number of iteration is {num_iter}, sum of squared distances is {sum_sq_dist}")

# plot sum sq dist
plt.subplot(3, 5, 15)
plt.plot(list(range(1, 13)), list_sum_sq_dist, marker='o')
plt.xlabel('k')
plt.ylabel('Sum of Squared Distances')
plt.title('Sum of Squared Distances vs. k')
plt.grid(True)

plt.show()