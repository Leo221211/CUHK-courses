import numpy as np
from tqdm import tqdm
import matplotlib.pyplot as plt

def plot_prediction(w, step):
    def logistic_func(s):
        return np.exp(s) / (1 + np.exp(s))

    X = [25, 35, 45, 55, 65, 775, 85]
    Y = [0, 0.17, 0.29, 0.57, 0.80, 1., 1]
    plt.xlabel('x')
    plt.ylabel('y')
    plt.xlim(0, 100)
    plt.scatter(X, Y, color='blue')

    x_pred, y_pred = [], []
    for x in range(1, 101):
        x_pred.append(x)
        y_pred.append(logistic_func(np.dot(np.array([1, x]), w)))
    plt.plot(x_pred, y_pred, color='red')
    plt.savefig('{}.jpg'.format(step))
    plt.clf


def main():
    X = [22, 23, 24, 27, 28, 30, 30, 32, 33, 35, 38, \
        40, 41, 46, 47, 48, 49, 49, 50, 51, 51, 51, \
        54, 55, 58, 60, 60, 62, 65, 67, 71, 77, 81]
    
    Y = [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, \
        0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, \
        0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1]

    X = np.array([[1, x] for x in X]).reshape(len(X), 2)            # add bias term
    Y = np.array(Y)

    # define model weights, total_steps, lr
    w = np.zeros(2)
    total_steps = 100000
    lr = 0.002

    for step in tqdm(range(total_steps)):
        total_error = 0
        total_grad = 0
        for x, y in zip(X, Y):
            # calculate the output of logistic reg
            def logistic_func(s):
                return np.exp(s) / (1 + np.exp(s))
            
            z = np.dot(x, w)
            h = logistic_func(z)
            # print(h)

            # calculate gradients
            grad = np.dot(x.T, (h-y))
            # grad = - (y * x) / (1 + np.exp(y * np.dot(x, w)))
            error = - np.sum(y * np.log(h) + (1 - y) * np.log(1 - h))
            total_grad += grad
            total_error += error

        # print(total_grad)

        total_error /= X.shape[0]
        total_grad /= X.shape[0]
        w = w - lr * total_grad     # backward propagation

        if (step+1) % 10000 == 0:
            print("[step: {}] [error: {}]".format(step, total_error))
            plot_prediction(w, step+1)


if __name__=='__main__':
    main()