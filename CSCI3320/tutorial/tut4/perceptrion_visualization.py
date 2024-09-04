import matplotlib.pyplot as plt
# %matplotlib inline
import numpy as np
import pandas as pd
import matplotlib.lines as mlines
from matplotlib.colors import ListedColormap
# Take an objected-oriented approach to define the perceptron interface as a Python Class
# It has a fit method a predict method
# Add an underscore to attributes that are not being created upon the initialization of the object but by calling the object's other methods
# In practice, samples need to be shuffled at each epoch, which will be implemented in the AdalineSGD
class Perceptron(object):
    """Perceptron classifier.

    Parameters
    ------------
    eta : float
        Learning rate (between 0.0 and 1.0)
    n_iter : int
        Passes over the training dataset.

    Attributes
    -----------
    w_ : 1d-array
        Weights after fitting.
    errors_ : list
        Number of misclassifications in every epoch.

    """
    def __init__(self, eta=0.5, n_iter=10):
        self.eta = eta
        self.n_iter = n_iter
    
    def fit(self, X, y):
        """Fit training data.

        Parameters
        ----------
        X : {array-like}, shape = [n_samples, n_features]
            Training vectors, where n_samples is the number of samples and
            n_features is the number of features.
            is the X that does not includes bias term
        y : array-like, shape = [n_samples]
            Target values.

        Returns
        -------
        self : object

        Other var
        ---------
        self.w_ is the weight vector, including bias term

        """
        # initialize weights as zeros of size 1 + number of features, errors as empty list
        self.w_ = np.zeros(1 + X.shape[1])
        self.errors_ = []
        
        for _ in range(self.n_iter):
            errors = []
            # iterate samples one by one and update the weights
            for xi, target in zip(X, y):
                update = self.eta * (target - self.predict(xi))     # either -2, 0, or 2
                self.w_[0] += update                                # since xi doesn't include bias term, (if included, is 1)
                self.w_[1:] += update * xi
                errors.append(int(update != 0.0))
            self.errors_.append(sum(errors) if len(errors) > 0 else 0.)
        return self
    
    def net_input(self, X):
        """
        Calculate net input before activation
        
        returns the vector y
        """
        return np.dot(X, self.w_[1:]) + self.w_[0]
    
    def predict(self, X):
        """Return class label after unit step"""
        # not np.sign, because it will output 0 if input is 0
        return np.where(self.net_input(X) >= 0.0, 1, -1)
            
    def fit_with_plot(self,X,y):
        plt.ion()
        
        self.w_ = np.zeros(1 + X.shape[1])
        self.errors_ = []
        
        for num_i in range(self.n_iter):
            print("\n[INFO] Iteration:", num_i+1)
            errors = []
            # iterate samples one by one and update the weights
            step = 0
            print(">> Weight",self.w_)
            for xi, target in zip(X, y):
                now_errors = sum(errors)
                step += 1
                plot_each(X=X,y=y,W=self.w_, xi=xi, iteration=num_i+1,step=step, append_str=f"(err:{now_errors})")
                print("[DEBUG]", xi, target, self.predict(xi))
                update = self.eta * (target - self.predict(xi))
                self.w_[0] += update
                self.w_[1:] += update * xi
                errors.append(int(update != 0.0))
                if errors[-1] == 1:
                    
                    proceed = input("Continue to evaluation? [Y/N] >> ")
                    if proceed.lower() != "y":
                        return
                    now_errors = sum(errors)
                    plot_each(X=X,y=y,W=self.w_, xi=xi, iteration=num_i+1,step=step, append_str=f"_updated(err:{now_errors})")
                    print("Update weight",self.w_)
                    print("[DEBUG]", xi, target, self.predict(xi))
                    
            print("errors:", sum(errors))
            self.errors_.append(sum(errors) if len(errors) > 0 else 0.)
        
        plt.ioff()
        plt.show()
        
        return self




def plot_each(X,y, W=None,xi=None, iteration: int= 1,step: int = 1, append_str: str="", resolution: int=0.02):
    markers = ['o', 'x', 's', '^', 'v']
    colors = ['r', 'b', 'g', 'k', 'grey']
    cmap = ListedColormap(colors[:len(np.unique(y))])
    labels = ["sentosa(-1)","versicolor(+1)"]
    
    # plot scatter plot
    plt.cla()

    #####################################
    # plot region
    #####################################
    xx1, xx2 = np.meshgrid(np.arange(-1, X[:, 0].max()+0.1, resolution), np.arange(-4, X[:, 1].max()+0.1, resolution))
    # use predict method to predict the class labels z of the grid points
    def predict(W,x):
        return np.where(np.dot(x, W[1:])+W[0] >= 0.0,1,-1)
    
    # Z is the predicted mesh
    if (W != np.zeros(1 + X.shape[1])).sum()==0:        # if all the elements in W is 0
        Z = np.ones(xx1.shape,dtype=np.int32)           
        Z[0][0] = -1 # if comment, the whole region becomes red (0), because they are in the same height 
    else:
        Z = predict(W, np.array([xx1.ravel(),xx2.ravel()]).T)
        Z = Z.reshape(xx1.shape)

    # draw the contour using matplotlib
    plt.contourf(xx1, xx2, Z, alpha=0.4, cmap=cmap)
    plt.xlim(xx1.min(), xx1.max())
    plt.ylim(xx2.min(), xx2.max())
    
    #####################################
    # plot samples
    #####################################
    for i, cl in enumerate(np.unique(y)):
        plt.scatter(x=X[y==cl, 0], y=X[y==cl, 1], alpha=0.8, color=colors[i], marker=markers[i], label=labels[i])
    
    #####################################
    # plot the select sample
    #####################################
    plt.scatter(xi[0],xi[1], color='g', marker='s',label="W:"+str(W))
    
    #####################################
    # set label & title
    #####################################
    plt.xlabel('sepal length [cm]')
    plt.ylabel('petal length [cm]')
    plt.legend(loc='upper left')
    plt.title(f"Iteration:{iteration}-{step}{append_str}")
    plt.tight_layout()
    
    # plt.pause(0.005)
    # plt.savefig(f"figures/{iteration}-{step}{append_str}.jpg",dpi=300)

if __name__ == "__main__":
    
    # read in iris data
    df = pd.read_csv('https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data', header=None)
    # plot the iris data using scatter plot
    # select two classes: setosa and versicolor
    y = df.iloc[0:100, 4].values  # values method of a pandas dataframe yields Numpy array
    y = np.where(y == 'Iris-setosa', -1, 1)

    # select two features: sepal length and petal length for visualization
    X = df.iloc[0:100, [0,2]].values
        

    ppn = Perceptron(eta=0.5, n_iter=10)
    ppn.fit_with_plot(X, y)
    
    



