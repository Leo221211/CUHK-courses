import numpy as np

# Samples for class 1 and class 2
class1_samples = np.array([[1.4, 1.3, 0.8], [0.3, -0.4, -0.3], [0, -1.1, -2], [1.3, -0.5, -0.6]])
class2_samples = np.array([[-1, -0.5, -1], [-0.5, -0.9, -0.2], [-1.4, 0.5, -1.2], [-0.8, -0.9, -1.3], [0.4, -0.1, 0.9], [1.1, -0.4, -0.3]])


mean_vector_class1 = np.mean(class1_samples, axis=0)
mean_vector_class2 = np.mean(class2_samples, axis=0)


print("question a")
print("mu 1:", mean_vector_class1)
print("mu 2:", mean_vector_class2)

variance_class1 = np.zeros((3,3))
variance_class2 = np.zeros((3,3))


print("\n question b")
# print(mean_vector_class2- mean_vector_class1)
diff = np.array(mean_vector_class2- mean_vector_class1).reshape((3,1))
print(diff @ diff.T)



# print(f'class1_samples.shape[0]:{class1_samples.shape[0]}')
for i in range(class1_samples.shape[0]):
    variance_class1 += np.dot((mean_vector_class1 - class1_samples[i]).reshape(1,3).T,(mean_vector_class1 - class1_samples[i]).reshape(1,3))
    # print(f"here {(mean_vector_class1 - class1_samples[i])}")

for i in range(class2_samples.shape[0]):
    variance_class2 += np.dot((mean_vector_class2 - class2_samples[i]).reshape(1,3).T,(mean_vector_class2 - class2_samples[i]).reshape(1,3))


# Print the variances
print("Variance for class 1:", variance_class1)
print("Variance for class 2:", variance_class2)
print(f"S1+S2={variance_class1+variance_class2}")

print(np.linalg.inv(variance_class1+variance_class2))
print(np.dot(np.linalg.inv(variance_class1+variance_class2), mean_vector_class1 - mean_vector_class2))