import numpy as np
import matplotlib.pyplot as plt
import random
import time
from tqdm import tqdm

def svm_smo(X, y, loss_precision, num_iter = 5000):
    """_summary_

    Args:
        X (_type_): N x dim
        y (_type_): (N,)
        num_iter (int, optional): _description_. Defaults to 100000.
    """

    # init
    N, dim = X.shape

    # decision line
    w = np.zeros(dim)
    w0 = 0

    alphas = np.zeros(N)

    errors = np.zeros(N)
    for i in range(N):
        errors[i] = np.dot(w, X[i, :]) + w0 - y[i]

    # tol
    alpha_i_tol = 1e-2
    updata_i_tol = 1e-3
    update_j_tol = 1e-5
    
    # # alpha_i_tol = 1
    # updata_i_tol = 1
    # update_j_tol = 1
    

    # loss
    loss_list = []


    # fit
    for it in (range(num_iter)):
        # check wether all alpha correct
        all_alpha_correct = True

        # for all alpha
        for i in range(len(alphas)):
            # get var
            xi = X[i, :]
            yi = y[i]
            alpha_i_prev = alphas[i]
            error_i_prev = errors[i]

            # check if satisfy boundary
            if ((alpha_i_prev < alpha_i_tol) and yi * (np.dot(w, xi) + w0) >= 1) or \
               ((alpha_i_prev >= alpha_i_tol) and abs(yi * (np.dot(w, xi) + w0) - 1) < alpha_i_tol):
                # print("here", it)
                continue            # satisfy condition, not suitable for alpha

            all_alpha_correct = False

            # select best alpha_j
            candidate_j = [can_j for can_j in range(len(alphas)) if alphas[can_j] > 0 and can_j != i]
            j = -1
            
            if len(candidate_j) > 0:
                best_diff = 0
                for test_j in candidate_j:
                    test_diff = np.abs(errors[i] - errors[test_j])
                    if test_diff > best_diff:
                        j = test_j
                        best_diff = test_diff
            else:       # randomly choose one
                candidate_j = [can_j for can_j in range(len(alphas)) if can_j != i]
                j = random.choice(candidate_j)

            # get new alpha_i, alpha_j
            alpha_j_prev = alphas[j]
            xj = X[j, :]
            yj = y[j]
            error_j_prev = errors[j]

            # if it < 1000:
            # if np.dot(xi - xj, xi - xj) < updata_i_tol:     # xi xj too close
            #     # print("here", it)
            #     continue

            alpha_j_unconstrained =  alpha_j_prev + yj * (error_i_prev - error_j_prev) / np.dot(xi - xj, xi - xj)

            # get alpha_j new
            if yi == yj:
                if alpha_j_unconstrained < 0:
                    alpha_j_new = 0
                elif 0 <= alpha_j_unconstrained <= alpha_i_prev + alpha_j_prev:
                    alpha_j_new = alpha_j_unconstrained
                else:
                    alpha_j_new = alpha_i_prev + alpha_j_prev
            else:
                if alpha_j_unconstrained < max(0, alpha_j_prev - alpha_i_prev):
                    alpha_j_new = max(0, alpha_j_prev - alpha_i_prev)
                else:
                    alpha_j_new = alpha_j_unconstrained

            # if didn't update too much, then skip
            # if np.abs(alpha_j_new - alpha_j_prev) < update_j_tol:
            #     print("here", it)
            #     continue

            alpha_i_new = alpha_i_prev + yi * yj * (alpha_j_prev - alpha_j_new)

            # update
            # w
            w = w + (alpha_i_new - alpha_i_prev) * yi * xi + (alpha_j_new - alpha_j_prev) * yj * xj

            # alpha
            alphas[i] = alpha_i_new
            alphas[j] = alpha_j_new

            # w0
            w0_i = yi - np.dot(w, xi)
            w0_j = yj - np.dot(w, xj)
            if alpha_i_new > 0:
                w0 = w0_i
            elif alpha_j_new > 0:
                w0 = w0_j
            else:
                w0 = (w0_i + w0_j) / 2

            # errors
            for e in range(len(errors)):
                errors[e] = np.dot(w, X[e, :]) + w0 - y[e]

        # Calculate loss every 10 iterations and store in loss_list
        if it % loss_precision == 0:
            loss = 0
            for i in range(N):
                for j in range(N):
                    loss += alphas[i] * alphas[j] * y[i] * y[j] * np.dot(X[i, :], X[j, :].T)
            
            loss = loss / 2 - np.sum(alphas)
            loss_list.append(loss)
        
        # if haven't updated any alpha_i
        if all_alpha_correct:
            print(f"\nearly break at it {it}")
            break

    # return
    sv_list = np.where(alphas > 1e-2)[0].tolist()

    w0 = np.mean([y[sv] - np.dot(w, X[sv, :]) for sv in sv_list])

    return w, w0, sv_list, alphas, loss_list






def main():
    '''
    (a)
    '''
    # init points
    # gen class 0 (ABC)
    class_0 = []
    while len(class_0) < 20:
        x = np.random.uniform(0, 1)
        y = np.random.uniform(0, 1)

        if x + y < 1:
            class_0.append([x, y])

    # gen class 1 (ABC)
    class_1 = []
    while len(class_1) < 20:
        x = np.random.uniform(0, 1)
        y = np.random.uniform(0, 1)

        if x + y > 1:
            class_1.append([x, y])
    
    '''
    (b)
    '''
    # Convert data to numpy arrays
    class_0 = np.array(class_0)
    class_1 = np.array(class_1)

    # Combine the two classes
    X = np.vstack((class_0, class_1))
    y = np.hstack((np.ones(len(class_0)), -np.ones(len(class_1))))

    # fit
    # print(X[0, :],  X[1, :].T, np.dot(X[0, :], X[1, :].T), X[0, 0]* X[1, 0] + X[0, 1]*X[1, 1])
    iter_num = 2000000
    loss_precision = 5
    start_time = time.time()
    w, w0, sv, alphas, loss_list = svm_smo(X, y, loss_precision, iter_num)
    # print(len(loss_list))
    end_time = time.time()

    # find time
    training_time = end_time - start_time
    print(f"when size == 20, training time is {training_time}s")

    # find accuracy
    # Compute training accuracy
    predictions = np.sign(np.dot(X, w) + w0)
    accuracy = np.mean(predictions == y)
    print(f"when size == 20, final accuracy is {accuracy}")

    # plot loss curve
    plt.subplot(1, 2, 1)
    plt.plot(list(range(0, len(loss_list)*loss_precision, loss_precision)), loss_list)
    plt.xlabel('Iteration')
    plt.ylabel('Loss')
    plt.title('Loss Curve - size 20')

    # plot prediction
    # Plotting the data points
    plt.subplot(1, 2, 2)
    plt.scatter(class_0[:, 0], class_0[:, 1], c='red', label='Class 0')
    plt.scatter(class_1[:, 0], class_1[:, 1], c='blue', label='Class 1')

    # Plotting the support vectors
    plt.scatter(X[sv, 0], X[sv, 1], c='black', marker='x', label='Support Vectors', linewidth=1, s=100)

    # Generate x-values for the line
    x_min, x_max = X[:, 0].min() - 0.1, X[:, 0].max() + 0.1
    x = np.linspace(x_min, x_max, 100)

    # Calculate the corresponding y-values using wx + w0 = 0
    y = -(w[0] * x + w0) / w[1]

    # Plot the line
    plt.plot(x, y, 'r-', label='wx + w0 = 0')

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('SVM Decision Boundary - size 20')
    plt.legend()
    plt.show()

    '''
    (c)
    '''
    # 50 data each class

    # init points
    # gen class 0 (ABC)
    class_0 = []
    while len(class_0) < 50:
        x = np.random.uniform(0, 1)
        y = np.random.uniform(0, 1)

        if x + y < 1:
            class_0.append([x, y])

    # gen class 1 (ABC)
    class_1 = []
    while len(class_1) < 50:
        x = np.random.uniform(0, 1)
        y = np.random.uniform(0, 1)

        if x + y > 1:
            class_1.append([x, y])

    # Convert data to numpy arrays
    class_0 = np.array(class_0)
    class_1 = np.array(class_1)

    # Combine the two classes
    X = np.vstack((class_0, class_1))
    y = np.hstack((np.ones(len(class_0)), -np.ones(len(class_1))))

    # fit
    # print(X[0, :],  X[1, :].T, np.dot(X[0, :], X[1, :].T), X[0, 0]* X[1, 0] + X[0, 1]*X[1, 1])
    start_time = time.time()
    w, w0, sv, alphas, loss_list = svm_smo(X, y, loss_precision, iter_num)
    # print(len(loss_list))
    end_time = time.time()

    # find time
    training_time = end_time - start_time
    print(f"when size == 50, training time is {training_time}s")

    # find accuracy
    # Compute training accuracy
    predictions = np.sign(np.dot(X, w) + w0)
    accuracy = np.mean(predictions == y)
    print(f"when size == 50, final accuracy is {accuracy}")

    # plot loss curve
    plt.subplot(1, 2, 1)
    plt.plot(list(range(0, len(loss_list)*loss_precision, loss_precision)), loss_list)
    plt.xlabel('Iteration')
    plt.ylabel('Loss')
    plt.title('Loss Curve - size 50')

    # plot prediction
    # Plotting the data points
    plt.subplot(1, 2, 2)
    plt.scatter(class_0[:, 0], class_0[:, 1], c='red', label='Class 0')
    plt.scatter(class_1[:, 0], class_1[:, 1], c='blue', label='Class 1')

    # Plotting the support vectors
    plt.scatter(X[sv, 0], X[sv, 1], c='black', marker='x', label='Support Vectors', linewidth=1, s=100)

    # Generate x-values for the line
    x_min, x_max = X[:, 0].min() - 0.1, X[:, 0].max() + 0.1
    x = np.linspace(x_min, x_max, 100)

    # Calculate the corresponding y-values using wx + w0 = 0
    y = -(w[0] * x + w0) / w[1]

    # Plot the line
    plt.plot(x, y, 'r-', label='wx + w0 = 0')

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('SVM Decision Boundary - size 50')
    plt.legend()
    plt.show()



    # 100 data each class

    # init points
    # gen class 0 (ABC)
    class_0 = []
    while len(class_0) < 100:
        x = np.random.uniform(0, 1)
        y = np.random.uniform(0, 1)

        if x + y < 1:
            class_0.append([x, y])

    # gen class 1 (ABC)
    class_1 = []
    while len(class_1) < 100:
        x = np.random.uniform(0, 1)
        y = np.random.uniform(0, 1)

        if x + y > 1:
            class_1.append([x, y])

    # Convert data to numpy arrays
    class_0 = np.array(class_0)
    class_1 = np.array(class_1)

    # Combine the two classes
    X = np.vstack((class_0, class_1))
    y = np.hstack((np.ones(len(class_0)), -np.ones(len(class_1))))

    # fit
    # print(X[0, :],  X[1, :].T, np.dot(X[0, :], X[1, :].T), X[0, 0]* X[1, 0] + X[0, 1]*X[1, 1])
    start_time = time.time()
    w, w0, sv, alphas, loss_list = svm_smo(X, y, loss_precision, iter_num)
    # print(len(loss_list))
    end_time = time.time()

    # find time
    training_time = end_time - start_time
    print(f"when size == 100, training time is {training_time}s")

    # find accuracy
    # Compute training accuracy
    predictions = np.sign(np.dot(X, w) + w0)
    accuracy = np.mean(predictions == y)
    print(f"when size == 100, final accuracy is {accuracy}")

    # plot loss curve
    plt.subplot(1, 2, 1)
    plt.plot(list(range(0, len(loss_list)*loss_precision, loss_precision)), loss_list)
    plt.xlabel('Iteration')
    plt.ylabel('Loss')
    plt.title('Loss Curve - size 100')

    # plot prediction
    # Plotting the data points
    plt.subplot(1, 2, 2)
    plt.scatter(class_0[:, 0], class_0[:, 1], c='red', label='Class 0')
    plt.scatter(class_1[:, 0], class_1[:, 1], c='blue', label='Class 1')

    # Plotting the support vectors
    plt.scatter(X[sv, 0], X[sv, 1], c='black', marker='x', label='Support Vectors', linewidth=1, s=100)

    # Generate x-values for the line
    x_min, x_max = X[:, 0].min() - 0.1, X[:, 0].max() + 0.1
    x = np.linspace(x_min, x_max, 100)

    # Calculate the corresponding y-values using wx + w0 = 0
    y = -(w[0] * x + w0) / w[1]

    # Plot the line
    plt.plot(x, y, 'r-', label='wx + w0 = 0')

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('SVM Decision Boundary - size 100')
    plt.legend()
    plt.show()
    


if __name__ == '__main__':
    main()