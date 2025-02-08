import numpy as np


def conv(image, kernel):
    """ An implementation of convolution filter.

    This function uses element-wise multiplication and np.sum()
    to efficiently compute weighted sum of neighborhood at each
    pixel.

    Args:
        image: numpy array of shape (Hi, Wi).
        kernel: numpy array of shape (Hk, Wk).

    Returns:
        out: numpy array of shape (Hi, Wi).
    """
    Hi, Wi = image.shape
    Hk, Wk = kernel.shape
    out = np.zeros((Hi, Wi))

    # For this assignment, we will use edge values to pad the images.
    # Zero padding will make derivatives at the image boundary very big,
    # whereas we want to ignore the edges at the boundary.
    pad_width0 = Hk // 2
    pad_width1 = Wk // 2
    pad_width = ((pad_width0,pad_width0),(pad_width1,pad_width1))
    padded = np.pad(image, pad_width, mode='edge')

    ### YOUR CODE HERE
    kernel = np.flip(kernel)
    for i in range(Hi):
        for j in range(Wi):
            out[i][j] += np.sum(padded[i: i + Hk, j :  j + Wk] * kernel)

    ### END YOUR CODE

    return out

def gaussian_kernel(size, sigma):
    """ Implementation of Gaussian Kernel.

    This function follows the gaussian kernel formula,
    and creates a kernel matrix.

    Hints:
    - Use np.pi and np.exp to compute pi and exp.

    Args:
        size: int of the size of output matrix.
        sigma: float of sigma to calculate kernel.

    Returns:
        kernel: numpy array of shape (size, size).
    """

    kernel = np.zeros((size, size))

    ### YOUR CODE HERE
    k = size // 2
    for i in range(size):
        for j in range(size):
            kernel[i][j] = (1 / (2 * np.pi * sigma ** 2)) * np.exp(-((i - k) ** 2 + (j - k) ** 2) / (2 * sigma **2))
    ### END YOUR CODE
            
    kernel = kernel / np.sum(kernel)

    return kernel

def partial_x(img):
    """ Computes partial x-derivative of input img.

    Hints:
        - You may use the conv function in defined in this file.

    Args:
        img: numpy array of shape (H, W).
    Returns:
        out: x-derivative image.
    """

    out = None

    ### YOUR CODE HERE
    kernel = np.array([[0.5, 0, -0.5]])
    out = conv(img, kernel)

    ### END YOUR CODE

    return out

def partial_y(img):
    """ Computes partial y-derivative of input img.

    Hints:
        - You may use the conv function in defined in this file.

    Args:
        img: numpy array of shape (H, W).
    Returns:
        out: y-derivative image.
    """

    out = None

    ### YOUR CODE HERE
    kernel = np.array([[0.5],
                       [0],
                       [-0.5]])
    out = conv(img, kernel)

    ### END YOUR CODE

    return out

def gradient(img):
    """ Returns gradient magnitude and direction of input img.

    Args:
        img: Grayscale image. Numpy array of shape (H, W).

    Returns:
        G: Magnitude of gradient at each pixel in img.
            Numpy array of shape (H, W).
        theta: Direction(in degrees, 0 <= theta < 360) of gradient
            at each pixel in img. Numpy array of shape (H, W).

    Hints:
        - Use np.sqrt and np.arctan2 to calculate square root and arctan
    """
    G = np.zeros(img.shape)
    theta = np.zeros(img.shape)

    ### YOUR CODE HERE
    img_x = partial_x(img)
    img_y = partial_y(img)

    G = np.sqrt(img_x * img_x + img_y * img_y)
    theta = (np.arctan2(img_y, img_x) * 180 / np.pi) % 360
    ### END YOUR CODE

    return G, theta


def edge_thinning(G, theta):
    """ Thinning the edges using non-maximum suppression.

    This function performs non-maximum suppression along the direction
    of gradient (theta) on the gradient magnitude image (G).

    Args:
        G: gradient magnitude image with shape of (H, W).
        theta: direction of gradients with shape of (H, W).

    Returns:
        out: non-maxima suppressed image.
    """
    H, W = G.shape
    out = np.zeros((H, W))

    # Round the gradient direction to the nearest 45 degrees
    theta = np.floor((theta + 22.5) / 45) * 45 % 360
    theta = theta % 360
    for i in range(1, H-1):
      for j in range(1,W-1):
        current_angle = theta[i,j]
        if current_angle == 0 or current_angle == 180:
          neighbors = [G[i, j-1], G[i, j+1]]
        elif current_angle == 45 or current_angle == 225:
          neighbors = [G[i-1, j-1], G[i+1, j+1]]
        elif current_angle == 90 or current_angle == 270:
          neighbors = [G[i-1, j], G[i+1, j]]
        elif current_angle == 135 or current_angle == 315:
          neighbors = [G[i-1, j+1], G[i+1, j-1]]
        else:
          raise RuntimeError("Invalid theta value {}".format(current_angle))
        if G[i,j] >= np.max(neighbors):
          out[i,j] = G[i,j]
        else:
          out[i, j] = 0
    return out



def double_thresholding(img, high, low):
    """
    Args:
        img: numpy array of shape (H, W) representing NMS edge response.
        high: high threshold(float) for strong edges.
        low: low threshold(float) for weak edges.

    Returns:
        strong_edges: Boolean array representing strong edges.
            Strong edeges are the pixels with the values greater than
            the higher threshold.
        weak_edges: Boolean array representing weak edges.
            Weak edges are the pixels with the values smaller or equal to the
            higher threshold and greater than the lower threshold.
    """

    strong_edges = np.zeros(img.shape, dtype=bool)
    weak_edges = np.zeros(img.shape, dtype=bool)

    # strong_edges = np.zeros(img.shape, dtype=np.bool)
    # weak_edges = np.zeros(img.shape, dtype=np.bool)

    ### YOUR CODE HERE
    strong_edges[img > high] = True
    weak_edges[(img > low) & (img <= high)] = True
    ### END YOUR CODE

    return strong_edges, weak_edges


def get_neighbors(y, x, H, W):
    """ Return indices of valid neighbors of (y, x).

    Return indices of all the valid neighbors of (y, x) in an array of
    shape (H, W). An index (i, j) of a valid neighbor should satisfy
    the following:
        1. i >= 0 and i < H
        2. j >= 0 and j < W
        3. (i, j) != (y, x)

    Args:
        y, x: location of the pixel.
        H, W: size of the image.
    Returns:
        neighbors: list of indices of neighboring pixels [(i, j)].
    """
    neighbors = []

    for i in (y-1, y, y+1):
        for j in (x-1, x, x+1):
            if i >= 0 and i < H and j >= 0 and j < W:
                if (i == y and j == x):
                    continue
                neighbors.append((i, j))

    return neighbors

def link_edges(strong_edges, weak_edges):
    """ Find weak edges connected to strong edges and link them.

    Iterate over each pixel in strong_edges and perform breadth first
    search across the connected pixels in weak_edges to link them.
    Here we consider a pixel (a, b) is connected to a pixel (c, d)
    if (a, b) is one of the eight neighboring pixels of (c, d).

    Args:
        strong_edges: binary image of shape (H, W).
        weak_edges: binary image of shape (H, W).
    
    Returns:
        edges: numpy boolean array of shape(H, W).
    """

    H, W = strong_edges.shape
    indices = np.stack(np.nonzero(strong_edges)).T      # indices of strong edges
    edges = np.zeros((H, W), dtype=bool)

    # Make new instances of arguments to leave the original
    # references intact 
    weak_edges = np.copy(weak_edges)
    edges = np.copy(strong_edges)


    ### YOUR CODE HERE
    strong_list = [strong for strong in indices]

    while(len(strong_list) > 0):
        y, x = strong_list[0]

        # get neighbors
        neighbors = get_neighbors(y, x, H, W)

        # check if strong
        for nei_y, nei_x in neighbors:
            if weak_edges[nei_y, nei_x] and not edges[nei_y, nei_x]:
                edges[nei_y, nei_x] = True
                strong_list.append((nei_y, nei_x))

        # pop first element
        strong_list.pop(0)
    ### END YOUR CODE

    return edges

def canny(img, kernel_size=5, sigma=1.4, high=0.03, low=0.02): 
    """ Implement canny edge detector by calling functions above.

    Args:
        img: binary image of shape (H, W).
        kernel_size: int of size for kernel matrix.
        sigma: float for calculating kernel.
        high: high threshold for strong edges.
        low: low threashold for weak edges.
    Returns:
        edge: numpy array of shape(H, W).
    """
    ### YOUR CODE HERE
    # smooth
    kernel = gaussian_kernel(kernel_size, sigma)
    smoothed = conv(img, kernel)

    # gradient
    G, theta = gradient(smoothed)

    # edge thinning
    nms = edge_thinning(G, theta)

    # double thresholding
    strong_edges, weak_edges = double_thresholding(nms, high, low)

    # link 
    edge = link_edges(strong_edges, weak_edges)
    
    # Please use the given edge_thinning() as the NMS method
    ### END YOUR CODE

    return edge

def non_maximum_suppression(R, window_size=3):
    """ Apply non-maximum suppression to suppress non-maximal values
    in the Harris corner response map R.

    Args:
        R: numpy array of shape (H, W), the Harris corner response.
        window_size: int, the size of the neighborhood to consider for suppression.

    Returns:
        R_nms: numpy array of shape (H, W), where only local maxima are retained.
    """
    H, W = R.shape
    R_nms = np.zeros_like(R)
    offset = window_size // 2
    
    R_nms = np.zeros_like(R)

    ### YOUR CODE HERE
    # zero pad
    padded_R = np.zeros((H+2*offset, W+2*offset))
    padded_R[offset : offset + H, offset : offset + W] = R

    for i in range(H):
        for j in range(W):
            window = padded_R[i: i + window_size, j: j + window_size]
            if R[i, j] == np.max(window):
                R_nms[i, j] = R[i, j]

    ### END YOUR CODE
    
    return R_nms

def harris_corner_response(img, k=0.05, hsz=5):
    """ Calculate the harris corner reponse map R.

    Args:
        img: the input grayscale image.
        k: the parameter the determine the decision boundary for corners.
        hsz: the window size of the gaussian kernel.

    Returns:
        R: the harris response map R.
    """
    # Compute gradients
    Ix = partial_x(img)
    Iy = partial_y(img)
    Ixx = Ix ** 2
    Ixy = Iy * Ix
    Iyy = Iy ** 2

    # Apply Gaussian filter to smooth the gradients
    g_kernel = gaussian_kernel(2 * hsz+1, hsz/2)
    Sxx = conv(Ixx, g_kernel)
    Sxy = conv(Ixy, g_kernel)
    Syy = conv(Iyy, g_kernel)

    R = np.zeros_like(img)
    # Compute the harris corner response R
    ### YOUR CODE HERE
    # find sum in windows
    sum_kernel_len = hsz
    sum_kernel = np.ones((sum_kernel_len, sum_kernel_len))
    sum_kernel = sum_kernel / (sum_kernel_len ** 2)

    Sumxx = conv(Sxx, sum_kernel)
    Sumxy = conv(Sxy, sum_kernel)
    Sumyy = conv(Syy, sum_kernel)

    # find structure tensor for each pixel
    struct_tensor = np.stack([np.stack([Sumxx, Sumxy], axis=-1), np.stack([Sumxy, Sumyy], axis=-1)], axis=-2)
    
    det = np.linalg.det(struct_tensor)
    trace = np.trace(struct_tensor, axis1=-2, axis2=-1)


    # compute R
    R = det - k * trace ** 2

    ### END YOUR CODE

    return R


def hough_transform(img):
    """ Transform points in the input image into Hough space.

    Use the parameterization:
        rho = x * cos(theta) + y * sin(theta)
    to transform a point (x,y) to a sine-like function in Hough space.

    Args:
        img: binary image of shape (H, W).
        
    Returns:
        accumulator: numpy array of shape (m, n).
        rhos: numpy array of shape (m, ).
        thetas: numpy array of shape (n, ).
    """
    # Set rho and theta ranges
    W, H = img.shape
    diag_len = int(np.ceil(np.sqrt(W * W + H * H)))
    rhos = np.linspace(-diag_len, diag_len, diag_len * 2 + 1)
    thetas = np.deg2rad(np.arange(-90.0, 90.0))

    # Cache some reusable values
    cos_t = np.cos(thetas)
    sin_t = np.sin(thetas)
    num_thetas = len(thetas)

    # Initialize accumulator in the Hough space
    accumulator = np.zeros((2 * diag_len + 1, num_thetas), dtype=np.uint64)
    ys, xs = np.nonzero(img)

    # Transform each point (x, y) in image
    # Find rho corresponding to values in thetas
    # and increment the accumulator in the corresponding coordiate.
    ### YOUR CODE HERE
    for i in range(len(xs)):
        x = xs[i]
        y = ys[i]
        for t_idx in range(num_thetas):
            rho = (x * cos_t[t_idx] + y * sin_t[t_idx] + diag_len).astype(int)
            if rho >= 0 and rho <= 2 * diag_len:
                accumulator[rho][t_idx] += 1
    ### END YOUR CODE

    return accumulator, rhos, thetas
