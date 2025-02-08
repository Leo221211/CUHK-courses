"""
CSCI3330: Fundamentals of Applied Computer Vision -- HW3
Please submit before deadline (March 17, 2024) through blackboard
"""

import numpy as np
import random
from scipy.spatial.distance import squareform, pdist, cdist
from skimage.util import img_as_float
# Please be awared that no additional packages could be used
# Questions adopt additional packages WILL GET 0 SCORE

### Clustering Methods
def kmeans(features, k, num_iters=100):
    """ Use kmeans algorithm to group features into k clusters.

    K-Means algorithm can be broken down into following steps:
        1. Randomly initialize cluster centers
        2. Assign each point to the closest center
        3. Compute new center of each cluster
        4. Stop if cluster assignments did not change
        5. Go to step 2

    Args:
        features - Array of N features vectors. Each row represents a feature
            vector.
        k - Number of clusters to form.
        num_iters - Maximum number of iterations the algorithm will run.

    Returns:
        assignments - Array representing cluster assignment of each point.
            (e.g. i-th point is assigned to cluster assignments[i])
    """

    N, D = features.shape

    assert N >= k, 'Number of clusters cannot be greater than number of points'

    # Randomly initalize cluster centers
    idxs = np.random.choice(N, size=k, replace=False)
    centers = features[idxs]
    assignments = np.zeros(N, dtype=np.uint32)

    for n in range(num_iters):
        ### YOUR CODE HERE
        assignments_prev = assignments.copy()

        for i in range(N):      # all points
            # find square dist to each center
            square_dist = (features[i] - centers) ** 2
            square_dist = np.sqrt(np.sum(square_dist, axis=-1))

            # assign to the closest center
            assignments[i] = np.argmin(square_dist)

        for c in range(k):
            centers[c] = np.mean(features[assignments == c], axis=0)

        # check assignment
        if np.array_equal(assignments_prev, assignments):
            break
        ### END YOUR CODE
        
    return assignments

def kmeans_fast(features, k, num_iters=100):
    """ Use kmeans algorithm to group features into k clusters.

    This function makes use of numpy functions and broadcasting to speed up the
    first part(cluster assignment) of kmeans algorithm.

    Hints
    - You may find cdist (imported from scipy.spatial.distance) and np.argmin useful

    Args:
        features - Array of N features vectors. Each row represents a feature
            vector.
        k - Number of clusters to form.
        num_iters - Maximum number of iterations the algorithm will run.

    Returns:
        assignments - Array representing cluster assignment of each point.
            (e.g. i-th point is assigned to cluster assignments[i])
    """

    N, D = features.shape

    assert N >= k, 'Number of clusters cannot be greater than number of points'

    # Randomly initalize cluster centers
    idxs = np.random.choice(N, size=k, replace=False)
    centers = features[idxs]
    assignments = np.zeros(N, dtype=np.uint32)
    
    for n in range(num_iters):
        ### YOUR CODE HERE
        assignments_prev = assignments.copy()

        # find dist
        dists = cdist(features, centers)

        # cluster
        assignments = np.argmin(dists, axis=-1)

        for c in range(k):
            centers[c] = np.mean(features[assignments == c], axis=0)

        # check assignment
        if np.array_equal(assignments_prev, assignments):
            break
        ### END YOUR CODE

    return assignments


def kmeans_pp(features, k, num_iters=100):
    """ Use kmeans++ algorithm to initialize clusters. The optimization part 
        should be the same with kmeans_fast.

    K-Means++ algorithm search initial cluster centers with steps as follows:
        1. randomly select one point as initial center of one class;
        2. for each data sample, compute the distance between the sample and 
        nearest class, write it as D(x);
        3. Choose one new data point random as a new center, using a weighted 
        probablity distribution where a point x is chosen with probability 
        proportional to D(x)^2;
        4. Repeat steps 2 and 3 until all initial cluster centers are chosen;
        5. optimize following K-Means algorithm.
        

    Args:
        features - Array of N features vectors. Each row represents a feature
            vector.
        k - Number of clusters to form.
        num_iters - Maximum number of iterations the algorithm will run.

    Returns:
        assignments - Array representing cluster assignment of each point.
            (e.g. i-th point is assigned to cluster assignments[i])
    """
    

    N, D = features.shape

    assert N >= k, 'Number of clusters cannot be greater than number of points'
    assignments = np.zeros(N, dtype=np.uint32)
    ### YOUR CODE HERE
    # choose first center
    centers = np.zeros((k, 2))
    centers[0] = features[np.random.choice(N, size=1)]

    # choose other centers
    for i in range(1, k):
        dist = np.min(cdist(features, centers[:i]), axis=-1)      # D(x) for each data
        dist = dist ** 2
        dist /= np.sum(dist)        # normalize as probability

        centers[i] = features[np.random.choice(N, size=1, p=dist)]    # will not choose the same one since the probability is 0

    # K-means
    for _ in range(num_iters):
        assignments_prev = assignments.copy()

        # find dist
        dists = cdist(features, centers)

        # cluster
        assignments = np.argmin(dists, axis=-1)

        for c in range(k):
            centers[c] = np.mean(features[assignments == c], axis=0)

        # check assignment
        if np.array_equal(assignments_prev, assignments):
            break

    ### END YOUR CODE
    return assignments

def mean_shift(features, w, e=0.01):
    """ Run the Mean Shift clustering algorithm.

    The algorithm is conceptually simple:

    Given distribution of N pixels in feature space
    1. Set m_i=f_i as initial mean for each pixel i
    2. Repeat the following for each mean m_i:
        a. Place window of size w around m_i;
        b. Compute centroid m within the window. Set m_i=m;
        c. Stop if shift in mean m_i is less than a threshold e. m_i is the mode;
    3. Label all pixels that have the same mode as belonging to the same cluster.

    Hints
    - You may implement the Mean Shift algorithm with uniform kernel.
    - Please use square window for computation.
    - You may use normalization as the first step to ensure features from different 
    sources (e.g., RGB: 0~255, h/w: 0~720/0~1280) have the same data range (e.g., 0~1).

    Args:
        features - Array of N features vectors. Each row represents a feature
            vector.
        w - size of the square window centered at the centroid.
        e - threshold to stop optimization

    Returns:
        assignments - Array representing cluster assignment of each point.
            (e.g. i-th point is assigned to cluster assignments[i])
    """



    N, D = features.shape

    # Assign each point to its own cluster
    assignments = np.zeros(N, dtype=np.uint32)

    # Normalization
    # features = features / np.max(features, axis=0)

    # mean shift
    modes = features.copy()
    prev_modes = modes.copy()

    # for each iteration
    while True:
        # calculate all chebyshev dist for modes
        dists = cdist(features, modes, 'chebyshev')

        # find points inside window for each modes and update new mode
        # mode = np.mean((dists < (w/2)) * features.T, axis = -1)
        in_window_idx = dists < (w/2)
        for i in range(len(dists)):
            modes[i] = np.mean(features[in_window_idx[i]], axis=0)
    
        # Calculate the maximum shift distance
        max_shift = np.max(np.abs(prev_modes - modes))
        
        # If the maximum shift is below the threshold, stop updating
        if max_shift < e:
            break

        prev_modes = modes

    # Group final clusters that are too close to each other as the same cluster
    cluster_cnt = 1
    dists_modes = cdist(modes, modes, 'chebyshev')
    visited = np.zeros(len(modes), dtype=bool)
    for i in range(len(modes)):
        if not visited[i]:
            cluster_idx = np.where(dists_modes[i] < (w/2))[0]
            assignments[cluster_idx] = cluster_cnt
            visited[cluster_idx] = True
            cluster_cnt += 1

    assignments -= 1



    # mode_array = np.zeros(features.shape)

    # for n in range(N):
    #     feat = features[n]
    #     ### YOUR CODE HERE
    #     # init center
    #     mode = feat.copy()

    #     while True:
    #         # find pixels in window
    #         in_window_idx = np.where((np.max(np.abs(features - mode), axis=-1)) < (w/2))

    #         in_window_pts = features[in_window_idx]

    #         # find new centroid
    #         new_centroid = np.mean(in_window_pts, axis=0)

    #         # check shift
    #         if np.max(np.abs(new_centroid - mode)) < e:
    #         # shift = np.linalg.norm(mode - new_centroid)
    #         # if shift < e:
    #             mode_array[n] = new_centroid
    #             break

    #         # set new mode
    #         mode = new_centroid
    #     ### END YOUR CODE

    # # ### group final clusters that are too close to each other as a same cluster
    # cluster_cnt = 1
    # for i, mode in enumerate(mode_array):
    #     if assignments[i] == 0:         # not clustered
    #         cluster_idx = np.where(np.max(np.abs(mode_array - mode), axis=-1) < (w/2))
    #         assignments[cluster_idx] = cluster_cnt
    #         cluster_cnt += 1
    
    # assignments -= 1
    # ###

    return assignments


### Pixel-Level Features
def color_features(img):
    """ Represents a pixel by its color.

    Args:
        img - array of shape (H, W, C)

    Returns:
        features - array of (H * W, C)
    """
    H, W, C = img.shape
    img = img_as_float(img)
    features = np.zeros((H*W, C))



    ### YOUR CODE HERE
    features = img.reshape(-1, C)
    ### END YOUR CODE

    return features

def color_position_features(img):
    """ Represents a pixel by its color and position.

    Combine pixel's RGB value and xy coordinates into a feature vector.
    i.e. for a pixel of color (r, g, b) located at position (x, y) in the
    image. its feature vector would be (r, g, b, x, y).

    Don't forget to normalize features.

    Hints
    - You may find np.mgrid and np.dstack useful
    - You may use np.mean and np.std

    Args:
        img - array of shape (H, W, C)

    Returns:
        features - array of (H * W, C+2)
    """
    H, W, C = img.shape
    color = img_as_float(img)
    features = np.zeros((H*W, C+2))

    ### YOUR CODE HERE
    xy_coords = np.dstack(np.mgrid[0:H, 0:W])
    features[:, :C] = color.reshape(-1, C)
    features[:, C:] = xy_coords.reshape(-1, 2)
    features = (features - np.mean(features, axis=0)) / np.std(features, axis=0)
    ### END YOUR CODE

    return features

def my_features(img):
    """ Implement your own features

    Args:
        img - array of shape (H, W, C)

    Returns:
        features - array of (H * W, C)
    """
    H, W, C = img.shape
    features = np.zeros((H*W, C))

    ### YOUR CODE HERE
    # grayness feature
    color = img_as_float(img)
    grayness_color = color.reshape(-1, 3)

    features[:, 0] = np.sum(grayness_color * [0.299, 0.587, 0.114], axis = -1)

    # distance feature
    xy_coords = np.dstack(np.mgrid[0:H, 0:W]).reshape(-1, 2)
    dist = np.sqrt(np.sum(xy_coords ** 2, axis=-1))
    features[:, 1] = dist

    # texture
    # convolution
    def zero_pad(image, pad_height, pad_width):
        H, W = image.shape
        out = None
        out = np.zeros((H+2*pad_height, W+2*pad_width))
        out[pad_height : pad_height + H, pad_width : pad_width + W] = image
        return out
    
    def conv_fast(image, kernel):
        Hi, Wi = image.shape
        Hk, Wk = kernel.shape
        out = np.zeros((Hi, Wi))
        image = zero_pad(image, pad_height=Hk // 2, pad_width=Wk // 2)
        kernel = np.flipud(np.fliplr(kernel))
        for i in range(Hi):
            for j in range(Wi):
                out[i][j] += np.sum(image[i : i + Hk, j :  j + Wk] * kernel)
        out = out / np.sum(out)
        return out
    
    # laplacian (use green channel since green channel is most similar to brightness)
    laplacian_kernel = np.array([[-1,-1,-1],
                                 [-1, 8,-1],
                                 [-1,-1,-1]])
    img_laplacian = np.abs(conv_fast(color[:,:,1], laplacian_kernel))

    # set as feature
    features[:, 2] = img_laplacian.reshape(-1)

    # normalize with weight [2, 2, 1]
    features = features / np.max(features, axis=0)
    features = features * [2, 2, 1]

    ### END YOUR CODE
    return features

def downsize(img, scale):
    '''
    scale * scale patch is downsized in to one new pixel
    '''
    height, width, channels = img.shape

    # Calculate the new dimensions of the downsized image
    new_height = height // scale
    new_width = width // scale

    # Reshape the image to divide it into scale x scale patches
    patches = img[:new_height * scale, :new_width * scale, :].reshape(
        new_height, scale, new_width, scale, channels
    )

    # Compute the mean of each patch along the last two axes (height and width)
    downsized_img = np.mean(patches, axis=(1, 3))

    return downsized_img.astype(np.uint8)

def upscale(img, new_height, new_width):
    height = img.shape[0]
    width = img.shape[1]

    # Calculate the scale factors along each axis
    scale_height = new_height // height
    scale_width = new_width // width

    # Repeat each pixel value to match the new dimensions
    
    upscaled_img = np.zeros((new_height, new_width))
    upscaled_img[:scale_height*height, :scale_width*width] = np.repeat(np.repeat(img, scale_height, axis=0), scale_width, axis=1)

    return upscaled_img.astype(np.uint8)
