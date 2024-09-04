import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib.lines as mlines
from matplotlib.colors import ListedColormap


class Perceptron(object):
    def __init__(self, eta=0.5):
        self.eta = eta
    
    def fit(self, X, y):
        '''
        self.errors_: a list, where ith element: number of errors in ith iteration
        errors: each iteration's recorder. errors[i]: indicator of: in this iteration, is the ith point an error point?
        '''
        # initialize weights as zeros of size 1 + number of features, errors as empty list
        self.w_ = np.zeros(1 + X.shape[1])
        self.errors_ = []
        
        while(True):
            errors = []

            for xi, target in zip(X, y):
                update = self.eta * (target - self.predict(xi))     
                self.w_[0] += update                                # since xi doesn't include bias term, (if included, is 1)
                self.w_[1:] += update * xi

                errors.append(int(update != 0.0))                   # for this point, if is updated: 1, else 0
            
            num_errors_for_one_iter = sum(errors) if len(errors) > 0 else 0
            if num_errors_for_one_iter == 0:                        # converge
                break
            else:
                self.errors_.append(num_errors_for_one_iter) # each iteration, how many points are updated

        return self
    
    def net_input(self, X):
        return np.dot(X, self.w_[1:]) + self.w_[0]
    
    def predict(self, X):
        return np.where(self.net_input(X) >= 0.0, 1, -1)
    
    
def plot(X, y, f, title, subplot_idx, result=None, value_max=150 ):

    # init
    # plt.figure(figsize=(12, 8))
    resolution = 0.02
    markers = ['o', 'x', 's', '^', 'v']
    colors = ['r', 'b', 'k', 'g', 'grey']
    cmap = ListedColormap(colors[:10])
    labels = ["-ve","+ve"]
    def predict(W,x):
        return np.where(np.dot(x, W[1:])+W[0] >= 0.0,1,-1)


    # plot
    plt.subplot(2, 2, subplot_idx)
    plt.title(f'question ({title})')
    plt.xlim(-0.5, value_max+0.5)
    plt.ylim(-0.5, value_max+0.5)
    plt.xlabel('x1 value')
    plt.ylabel('x2 value')
    
    for i, cl in enumerate(np.unique(y)):   # plot samples
        plt.scatter(x=X[y==cl, 0], y=X[y==cl, 1], alpha=0.8, color=colors[i], marker=markers[i], label=labels[i])


    xs = np.arange(-0.5, value_max+0.5, resolution)          # plot target function
    plt.plot(xs, (-f[0] - f[1] * xs) / f[2], label='f')      

    if result is not None:
        W = result.w_                                   # plot g

        xx1, xx2 = np.meshgrid(np.arange(-0.5, value_max+0.5, resolution), np.arange(-0.5, value_max+0.5, resolution))    # contour
        if (W != np.zeros(1 + X.shape[1])).sum()==0:        
            Z = np.ones(xx1.shape,dtype=np.int32)           
            Z[0][0] = -1 
        else:
            Z = predict(W, np.array([xx1.ravel(),xx2.ravel()]).T)
            Z = Z.reshape(xx1.shape)
        plt.contourf(xx1, xx2, Z, alpha=0.4, cmap=cmap)

        plt.plot(xs, (-W[0] - W[1] * xs) / W[2], label='g')     # g


    plt.legend(loc='upper left', fontsize='small')          # show


if __name__ == "__main__":
    value_max = 150

    '''
    (a) generate data set of size 20
    '''
    size_X = 20
    # set X
    # X: shape(n_samples, n_features)
    X = np.random.randint(0, value_max, size=(size_X, 2))

    # set target function f
    # f: shape (n_features + 1), f[0] is the bias term
    f = np.array([0.5, -1, 1])      # 0.5 - x1 + x2

    # set y
    # y: shape(n_samples)
    y = np.ones((20))
    y = np.where(np.dot(X, f[1:])+f[0] >= 0.0,1,-1)

    # plot
    plot(X, y, f, 'a', 1)


    '''
    (b) run the perceptron
    '''
    ppn = Perceptron(eta=0.5)
    result = ppn.fit(X, y)

    # number of updates
    print(f"for datasize=20, number of updates is {np.sum(result.errors_)}")

    # plot
    plot(X, y, f, 'b', 2, result)


    '''
    (c) run the perceptron with size=100
    '''
    size_X = 100
    # set X
    # X: shape(n_samples, n_features)
    X = np.random.randint(0, value_max, size=(size_X, 2))

    # set target function f
    # f: shape (n_features + 1), f[0] is the bias term
    f = np.array([0.5, -1, 1])      # 0.5 - x1 + x2

    # set y
    # y: shape(n_samples)
    y = np.ones((20))
    y = np.where(np.dot(X, f[1:])+f[0] >= 0.0,1,-1)

    ppn = Perceptron(eta=0.5)
    result = ppn.fit(X, y)

    # number of updates
    print(f"for datasize=100, number of updates is {np.sum(result.errors_)}")

    # plot
    plot(X, y, f, 'c', 3, result)

    '''
    (d) run the perceptron with size=1000
    '''
    size_X = 1000
    # set X
    # X: shape(n_samples, n_features)
    X = np.random.randint(0, value_max, size=(size_X, 2))

    # set target function f
    # f: shape (n_features + 1), f[0] is the bias term
    f = np.array([0.5, -1, 1])      # 0.5 - x1 + x2
    # set y
    # y: shape(n_samples)
    y = np.ones((20))
    y = np.where(np.dot(X, f[1:])+f[0] >= 0.0,1,-1)

    ppn = Perceptron(eta=0.5)
    result = ppn.fit(X, y)

    # number of updates
    print(f"for datasize=1000, number of updates is {np.sum(result.errors_)}")

    # plot
    plot(X, y, f, 'd', 4, result)


    '''
    (e) run the perceptron with size=1000 in 10D space
    '''
    size_X = 1000
    # set X
    # X: shape(n_samples, n_features)
    X = np.random.randint(0, value_max, size=(size_X, 10))

    # set target function f
    # f: shape (n_features + 1), f[0] is the bias term
    f = np.array([0.5, -1, 1, 2,-2, 3, -3, 4, -4, 5, -5])      

    # set y
    # y: shape(n_samples)
    y = np.ones((20))
    y = np.where(np.dot(X, f[1:])+f[0] >= 0.0,1,-1)

    ppn = Perceptron(eta=0.5)
    result = ppn.fit(X, y)

    # number of updates
    print(f"for datasize=1000, dimension=10, number of updates is {np.sum(result.errors_)}")


    plt.show()



