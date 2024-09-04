import numpy as np
from tqdm import tqdm
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

def logistic_func(s):
    return np.exp(s) / (1 + np.exp(s))

def plot_data(x, y, label, title):
    # init
    colors = ['blue', 'red']
    cmap = ListedColormap(colors)

    x_max = np.max(x)
    y_max = np.max(y)

    # plot structure
    plt.title(f'question ({title})')
    plt.xlim(-5, x_max+5)
    plt.ylim(-5, y_max+5)
    plt.xlabel('a value')
    plt.ylabel('b value')

    # plot data
    plt.scatter(x, y, c=label, cmap=cmap)

    # save
    plt.savefig(f'question ({title}).jpg')
    plt.clf

def grad_descent(X, Y, lr = 0.001, total_steps = 100000, prsc_report=False, precise=100):
    w = np.zeros(3)
    error_list = []

    for step in tqdm(range(total_steps)):
        total_error = 0
        total_grad = 0

        # forward
        for x, y in zip(X, Y):
            # cal error
            h = logistic_func(np.dot(x, w))
            total_error += - np.sum(y * np.log(h) + (1 - y) * np.log(1 - h))

            # cal grad
            grad = np.dot(x.T, (h-y))
            total_grad += grad

        total_error /= X.shape[0]
        total_grad /= X.shape[0]

        # backward propagation
        w = w - lr * total_grad

        if prsc_report and (step+1) % precise == 0:
            error_list.append([step, total_error])
        

    if prsc_report:
        steps = [points[0] for points in error_list]
        errors = [points[1] for points in error_list]
        plt.figure()
        plt.xlabel('step')
        plt.ylabel('loss')
        plt.title('question (4)')
        plt.plot(steps, errors, color ='blue')
        plt.savefig(f'question (4).jpg')
        print("The plot is stored in file question (4).jpg")
        
    
    return w, total_error


def main():
    a = [4, 5, 12, 29, 30, 36, 36, 54, 58, 70, 72, 76, 78, 82, 87, 90, 90, 92, 95, 98]
    b = [49, 4, 28, 18, 65, 32, 1, 29, 76, 12, 26, 55, 4, 15, 95, 70, 55, 84, 14, 21]
    label = [0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0]

    '''
    question (1)
    '''
    plot_data(a, b, label, "1")

    print("Question(1) \nFinished. The plot is stored in file question (1).jpg")

    '''
    question (2)
    '''
    print("\n\nQuestion(2)")

    X = np.array([[1, a_itm, b_itm] for a_itm, b_itm in zip(a, b)]).reshape((len(a), 3))     # add bias term  

    Y = np.array(label)

    
    # report
    w, total_error = grad_descent(X, Y)

    print(f"\nTraining finished.\n Final w = {w}\n Final error {total_error}")

    # calculate accuracy
    correct_cnt = 0
    for x, y in zip(X, Y):
        predicted = logistic_func(np.dot(x, w))
        if np.round(predicted).astype(int) == y:
            correct_cnt += 1
    print(f"Accuracy is {correct_cnt / X.shape[0]}")

    '''
    question (3)
    '''
    print("\n\nQuestion(3)")

    lr_list = [0.0005, 0.001, 0.0025, 0.005, 0.0075]
    error_list = []
    for lr in lr_list:
        w, total_error = grad_descent(X, Y, lr=lr)
        print(f"\nFor learning rate = {lr}:\n Final w = {w}\n Final error {total_error}")
        error_list.append(total_error)

    '''
    question (4)
    '''
    print("\n\nQuestion(4)")
    best_lr = lr_list[error_list.index(min(error_list))]
    print(f"best learning rate picked is {best_lr}")

    grad_descent(X, Y, lr=best_lr, prsc_report=True)


if __name__=='__main__':
    main()