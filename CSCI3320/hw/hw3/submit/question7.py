from sklearn.mixture import GaussianMixture
import numpy as np
import matplotlib.pyplot as plt
from itertools import permutations

def main():
    # (1)
    ## param
    # Parameters for the Gaussian distributions
    print("question (1): \nthe original plot is in subplot 1\n")
    mean1 = np.array([0, 0])
    variance1 = np.diag([1, 2])

    mean2 = np.array([4, 0])
    variance2 = np.diag([2, 2])

    mean3 = np.array([2, 0])
    variance3 = np.diag([2, 1])

    intensity_ratios = [3, 2, 2]
    num_points = [int(6000 * ratio / sum(intensity_ratios)) for ratio in intensity_ratios]
    num_points[2] = 6000 - num_points[0] - num_points[1]

    # generate
    data1 = np.random.multivariate_normal(mean1, variance1, num_points[0])
    data2 = np.random.multivariate_normal(mean2, variance2, num_points[1])
    data3 = np.random.multivariate_normal(mean3, variance3, num_points[2])
    data = np.vstack((data1, data2, data3))

    # plot
    plt.subplot(4, 2, 1)
    labels = np.concatenate((np.zeros(num_points[0]), np.ones(num_points[1]), np.full((num_points[2]), 2))).astype(int)
    plt.scatter(data[:, 0], data[:, 1], c=labels, s=5)
    plt.xlabel('X1', fontsize='small')
    plt.ylabel('X2', fontsize='small')
    plt.title('question 1', fontsize='small')

    # (2)
    # fit
    print("question (2)")
    gm = GaussianMixture(n_components=3, covariance_type='diag', random_state=0).fit(data)
    predictions = gm.predict(data)
    
    # try all matches and keep the best overall preciseness
    # labels [0, 1, 2] -> predictions [i, j, k]
    best_correct_num = -1
    for i, j, k in permutations([0, 1, 2]):
        correct_num = np.sum((labels == 0) & (predictions == i)) | np.sum((labels == 1) & (predictions == j)) | np.sum((labels == 2) & (predictions == k))

        if correct_num > best_correct_num:
            match = (i, j, k)
            best_correct_num = correct_num
    # print(f"final match {match}")
    
    indices = []
    for n in range(3):
        indices.append(np.argwhere(predictions == match[n]).flatten())

    for n in range(3):
        predictions[indices[n]] = n

    # calculate prediction and recall for each class
    precision = []
    recall = []
    for i in range(3):
        precision.append(np.sum((labels == i) & (predictions == i) ) / np.sum(labels == i))
        

        tp = np.sum((labels == predictions) & (predictions == i))
        fp = np.sum((labels != predictions) & (predictions == i))
        recall.append(tp / (tp + fp))     # TP / (TP + FP)   
    
    print(f"precision for class 1, 2, 3 is {precision}")
    print(f"recall for class 1, 2, 3 is {recall}")

    # plot
    plt.subplot(4, 2, 3)
    plt.scatter(data[:, 0], data[:, 1], c=predictions, s=5)
    plt.xlabel('X1', fontsize='small')
    plt.ylabel('X2', fontsize='small')
    plt.title('question 2', fontsize='small')


    # (3)
    print("\nquestion (3):")
    gm = GaussianMixture(n_components=3, covariance_type='full', random_state=0).fit(data)
    predictions = gm.predict(data)
    
    # try all matches and keep the best overall preciseness
    # labels [0, 1, 2] -> predictions [i, j, k]
    best_correct_num = -1
    for i, j, k in permutations([0, 1, 2]):
        correct_num = np.sum((labels == 0) & (predictions == i)) | np.sum((labels == 1) & (predictions == j)) | np.sum((labels == 2) & (predictions == k))
        if correct_num > best_correct_num:
            match = (i, j, k)
            best_correct_num = correct_num

    
    indices = []
    for n in range(3):
        indices.append(np.argwhere(predictions == match[n]).flatten())
    for n in range(3):
        predictions[indices[n]] = n

    # calculate prediction and recall for each class
    precision = []
    recall = []
    for i in range(3):
        precision.append(np.sum((labels == i) & (predictions == i) ) / np.sum(labels == i))

        tp = np.sum((labels == predictions) & (predictions == i))
        fp = np.sum((labels != predictions) & (predictions == i))
        recall.append(tp / (tp + fp))     # TP / (TP + FP)   
    
    print(f"new precision for class 1, 2, 3 is {precision}")
    print(f"new recall for class 1, 2, 3 is {recall}")

    # plot
    plt.subplot(4, 2, 4)
    plt.scatter(data[:, 0], data[:, 1], c=predictions, s=5)
    plt.xlabel('X1', fontsize='small')
    plt.ylabel('X2', fontsize='small')
    plt.title('question 3', fontsize='small')
    

    # (4)
    print("\nquestion (4): \nthe resulted is plotted")
    component_num_list = [2, 3, 10, 100]
    for cnt, component_num in enumerate(component_num_list):
        gm = GaussianMixture(n_components=component_num, covariance_type='full', random_state=0).fit(data)
        predictions = gm.predict(data)
        
        # # try all matches and keep the best overall preciseness
        # # labels [0, 1, 2] -> predictions [i, j, k]
        if(component_num == 3):
            best_correct_num = -1
            for i, j, k in permutations([0, 1, 2]):
                correct_num = np.sum((labels == 0) & (predictions == i)) | np.sum((labels == 1) & (predictions == j)) | np.sum((labels == 2) & (predictions == k))
                if correct_num > best_correct_num:
                    match = (i, j, k)
                    best_correct_num = correct_num

            
            indices = []
            for n in range(3):
                indices.append(np.argwhere(predictions == match[n]).flatten())
            for n in range(3):
                predictions[indices[n]] = n

        # # calculate prediction and recall for each class
        # precision = []
        # recall = []
        # for i in range(3):
        #     precision.append(np.sum((labels == i) & (predictions == i) ) / np.sum(labels == i))

        #     tp = np.sum((labels == predictions) & (predictions == i))
        #     fp = np.sum((labels != predictions) & (predictions == i))
        #     recall.append(tp / (tp + fp))     # TP / (TP + FP)   
        
        # print(f"when component number is {component_num},\nprecision for class 1, 2, 3 is {precision}")
        # print(f"recall for class 1, 2, 3 is {recall}\n")

        # plot
        plt.subplot(4, 2, 5+cnt)
        plt.scatter(data[:, 0], data[:, 1], c=predictions, s=5)
        plt.xlabel('X1', fontsize='small')
        plt.ylabel('X2', fontsize='small')
        plt.title(f'question 4 - n_com={component_num}', fontsize='small')

    plt.show()





if __name__ == '__main__':
    main()