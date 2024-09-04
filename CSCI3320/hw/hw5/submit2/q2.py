import numpy as np
import matplotlib.pyplot as plt

# Expectation Maximization (EM) algorithm for GMM
def em(data, num_cluster, num_iter=10000):
    """_summary_

    Args:
        data (_type_): N x 2
        num_cluster (_type_): 

    Others:
        mus: num_cluster x dim(2)
        covs: num_cluster x dim(2) x dim(2)
        pis: (num_cluster,)
        gammas: size x num_cluster
    """

    size, dim = data.shape

    # step 1: init
    # mus
    min_val = np.min(data, axis=0)
    max_val = np.max(data, axis=0)
    # # print(min_val, max_val)
    mus = np.random.uniform(min_val, max_val, size=(num_cluster, dim))
    # # print(mus)
    # mus = np.random.uniform(size=(num_cluster, dim))
    

    # # covs
    covs = np.random.randn(num_cluster, dim, dim)
    covs = np.matmul(covs, covs.transpose(0, 2, 1))    # ensure symmetric and positive
    # covs = np.zeros((num_cluster, dim, dim))
    # for c in range(num_cluster):
    #     covs[c] = np.eye(dim)  # Initialize with identity matrices

    # pis
    pis = np.ones(num_cluster) / num_cluster

    # print(f"init parameters:\n\nmean matrix:\n{mus}\n\ncovariance matrix:\n{covs}\n\nprior:\n{pis}")


    for _ in range(int(num_iter)):
        # step 2: E
        gammas = np.zeros((size, num_cluster))

        for c in range(num_cluster):
            gammas[:, c] = pis[c] * multivariate_normal(data, mus[c], covs[c])
            
        gammas /= np.sum(gammas, axis=1, keepdims=True)

        # step 3: M

        Nk = np.sum(gammas, axis=0)

        for c in range(num_cluster):
            mus[c] = np.dot(gammas[:, c], data) / Nk[c]
            covs[c] = np.dot(gammas[:, c] * (data - mus[c]).T, data - mus[c]) / Nk[c]
            pis[c] = Nk[c] / size
        
    return mus, covs, pis


# Helper function for multivariate normal PDF
def multivariate_normal(x, mean, covariance):
    inv_cov = np.linalg.inv(covariance)
    det_cov = np.linalg.det(covariance)
    exponent = -0.5 * np.sum((x - mean) @ inv_cov * (x - mean), axis=1)
    return np.exp(exponent) / np.sqrt((2 * np.pi)**x.shape[1] * det_cov)

def main():
    '''
    (a)
    '''
    ## param
    # Parameters for the Gaussian distributions
    mean1 = np.array([0, 0])
    cov1 = np.array([[1, 0.6],
                     [0.6, 1]])

    mean2 = np.array([3, 0])
    cov2 = np.array([[0.5, 0.4],
                     [0.4, 0.5]])

    num_points = [500, 500]

    # generate
    data1 = np.random.multivariate_normal(mean1, cov1, num_points[0])
    data2 = np.random.multivariate_normal(mean2, cov2, num_points[1])

    # data = np.vstack((data1, data2))
    # print(data.shape)


    '''
    (b)
    '''
    # plot
    plt.scatter(data1[:, 0], data1[:, 1], c='orange', label='Gaussian 1')
    plt.scatter(data2[:, 0], data2[:, 1], c='blue', label='Gaussian 2')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Data Points from Gaussian Mixture Model')
    plt.legend()

    '''
    (c)
    '''
    data = np.vstack((data1, data2))
    # print(data.shape)

    mus, covs, pis = em(data, 2)

    print(f"estimated parameters:\n\nmean matrix:\n{mus}\n\ncovariance matrix:\n{covs}\n\nprior:\n{pis}")

    plt.show()


if __name__=='__main__':
    main()