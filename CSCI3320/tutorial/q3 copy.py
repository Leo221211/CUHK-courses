import numpy as np
import matplotlib.pyplot as plt
import random


def svm_smo(X, y, num_iter = 100000):
    """_summary_

    Args:
        X: data (_type_): N x dim
        y: labels (_type_): (N,)
    """

    def meet_kkt(w, b, x_i, y_i, alpha_i):
        if alpha_i < 1e-7:
            return y_i * (np.dot(w, x_i) + b) >= 1
        else:
            return abs(y_i * (np.dot(w, x_i) + b) - 1) < 1e-7
        
    def select_j(best_i):
        valid_j_list = [i for i in range(0, len(alphas)) if alphas[i] > 0 and i != best_i]
        best_j = -1
        if len(valid_j_list) > 0:
            max_e = 0
            for j in valid_j_list:
                current_e = np.abs(errors[best_i] - errors[j])
                if current_e > max_e:
                    best_j = j
                    max_e = current_e
        else:
            l = list(range(len(alphas)))
            seq = l[: best_i] + l[best_i + 1:]
            best_j = random.choice(seq)
        return best_j

    # init
    N, dim = X.shape
    w = np.zeros(dim)
    b = 0
    alphas = np.zeros(N)
    errors = np.zeros(N)
    
    for i in range(N):
        errors[i] = np.dot(w, X[i, :]) + b - y[i]


    # fit
    for _ in range(num_iter):
        # for each loop, test all alphas, and update the illegal ones
        if_all_match_kkt = True
        for i in range(len(alphas)):
            x_i = X[i, :]
            y_i = y[i]
            alpha_i_prev = alphas[i]
            error_i_prev = errors[i]

            # if can find best i
            if not meet_kkt(w, b, x_i, y_i, alpha_i_prev):
                # find best j
                if_all_match_kkt = False

                best_j = select_j(i)

                alpha_j_prev = alphas[best_j]
                x_j = X[best_j, :]
                y_j = y[best_j]
                error_j_prev = errors[best_j]

                # update
                eta = np.dot(x_i - x_j, x_i - x_j)

                if eta < 1e-3:
                    continue
                alpha_j_unc = alpha_j_prev + y_j * (error_i_prev - error_j_prev) / eta

                if y_i == y_j:
                    if alpha_j_unc < 0:
                        alpha_j_new = 0
                    elif 0 <= alpha_j_unc <= alpha_i_prev + alpha_j_prev:
                        alpha_j_new = alpha_j_unc
                    else:
                        alpha_j_new = alpha_i_prev + alpha_j_prev
                else:
                    if alpha_j_unc < max(0, alpha_j_prev - alpha_i_prev):
                        alpha_j_new = max(0, alpha_j_prev - alpha_i_prev)
                    else:
                        alpha_j_new = alpha_j_unc

                if np.abs(alpha_j_new - alpha_j_prev) < 1e-5:
                    continue
                
                alpha_i_new = alpha_i_prev + y_i * y_j * (alpha_j_prev - alpha_j_new)

                w = w + (alpha_i_new - alpha_i_prev) * y_i * x_i + (alpha_j_new - alpha_j_prev) * y_j * x_j

                alphas[i] = alpha_i_new
                alphas[best_j] = alpha_j_new

                b_i_new = y_i - np.dot(w, x_i)
                b_j_new = y_j - np.dot(w, x_j)
                if alpha_i_new > 0:
                    b = b_i_new
                elif alpha_j_new > 0:
                    b = b_j_new
                else:
                    b = (b_i_new + b_j_new) / 2.0

                for k in range(len(errors)):
                    errors[k] = np.dot(w, X[k, :]) + b - y[k]

        if if_all_match_kkt is True:
            print("early break")
            break

    sv = np.where(alphas > 1e-2)[0]

    b = np.mean([ y[s] - np.dot(w, X[s, :]) for s in sv.tolist()])

    return w, b, sv, alphas






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

    w, b, sv, alphas = svm_smo(X, y)

    # Plotting the data points
    plt.scatter(class_0[:, 0], class_0[:, 1], c='red', label='Class 0')
    plt.scatter(class_1[:, 0], class_1[:, 1], c='blue', label='Class 1')

    # Plotting the support vectors
    plt.scatter(X[sv, 0], X[sv, 1], c='black', marker='x', label='Support Vectors')

    # Generate x-values for the line
    x_min, x_max = X[:, 0].min() - 0.1, X[:, 0].max() + 0.1
    x = np.linspace(x_min, x_max, 100)

    # Calculate the corresponding y-values using wx + b = 0
    y = -(w[0] * x + b) / w[1]

    # Plot the line
    plt.plot(x, y, 'r-', label='wx + b = 0')

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('SVM Decision Boundary')
    plt.legend()
    plt.show()
    # Plotting the data points
    # plt.scatter(class_0[:, 0], class_0[:, 1], c='red', label='Class 0')
    # plt.scatter(class_1[:, 0], class_1[:, 1], c='blue', label='Class 1')

    # # Plotting the support vectors
    # plt.scatter(X[sv, 0], X[sv, 1], c='black', marker='x', label='Support Vectors')

    # # Generate x-values for the line
    # x_min, x_max = X[:, 0].min() - 0.1, X[:, 0].max() + 0.1
    # x = np.linspace(x_min, x_max, 100)

    # # Calculate the corresponding y-values using wx + b = 0
    # y = -(w[0] * x + b) / w[1]

    # # Plot the line
    # plt.plot(x, y, 'r-', label='wx + b = 0')

    # plt.xlabel('X')
    # plt.ylabel('Y')
    # plt.title('SVM Decision Boundary')
    # plt.legend()
    # plt.show()


    # # Train the SVM model
    # alpha, b = svm_smo(X, y)

    # # Get support vectors
    # support_vector_indices = np.where(alpha > 0)[0]
    # support_vectors = X[support_vector_indices]

    # # Plot the data points
    # plt.scatter(class_0[:, 0], class_0[:, 1], color='red', marker='o', label='Class 0')
    # plt.scatter(class_1[:, 0], class_1[:, 1], color='blue', marker='x', label='Class 1')
    # plt.scatter(support_vectors[:, 0], support_vectors[:, 1], color='green', marker='s', label='Support Vectors')

    # # Plot the decision boundary
    # x_min, x_max = X[:, 0].min() - 0.1, X[:, 0].max() + 0.1
    # y_min, y_max = X[:, 1].min() - 0.1, X[:, 1].max() + 0.1
    # xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.01), np.arange(y_min, y_max, 0.01))
    # Z = np.sign(np.dot(np.hstack((xx.ravel().reshape(-1, 1), yy.ravel().reshape(-1, 1))), alpha * y) + b)
    # Z = Z.reshape(xx.shape)
    # plt.contour(xx, yy, Z, colors='k', levels=[-1, 0, 1], alpha=0.5, linestyles=['--', '-', '--'])

    # # Set plot labels and legend
    # plt.xlabel('X')
    # plt.ylabel('Y')
    # plt.legend()

    # # Show the plot
    # plt.show()

if __name__ == '__main__':
    main()