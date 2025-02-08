"""
CSCI3330 - Homework 1
"""

import numpy as np

def conv_nested(image, kernel):
    """A naive implementation of convolution filter.

    This is a naive implementation of convolution using 4 nested for-loops.
    This function computes convolution of an image with a kernel and outputs
    the result that has the same shape as the input image.

    Args:
        image: numpy array of shape (Hi, Wi).
        kernel: numpy array of shape (Hk, Wk).

    Returns:
        out: numpy array of shape (Hi, Wi).
    """
    Hi, Wi = image.shape
    Hk, Wk = kernel.shape
    out = np.zeros((Hi, Wi))

    ### YOUR CODE HERE
    # flip kernel
    kernel = np.flipud(np.fliplr(kernel))

    # convolve
    for h in range(Hi):
        for w in range(Wi):
            for i in range(Hk):
                for j in range(Wk):
                    if h - (Hk // 2) + i >= 0 and h - (Hk // 2) + i < Hi and w - (Wk // 2) + j >= 0 and w - (Wk // 2) + j < Wi:
                        out[h][w] += image[h - (Hk // 2) + i][w - (Wk // 2) + j] * kernel[i][j]
    

    ### END YOUR CODE
    
    return out

def zero_pad(image, pad_height, pad_width):
    """ Zero-pad an image.

    Ex: a 1x1 image [[1]] with pad_height = 1, pad_width = 2 becomes:

        [[0, 0, 0, 0, 0],
         [0, 0, 1, 0, 0],
         [0, 0, 0, 0, 0]]         of shape (3, 5)

    Args:
        image: numpy array of shape (H, W).
        pad_width: width of the zero padding (left and right padding).
        pad_height: height of the zero padding (bottom and top padding).

    Returns:
        out: numpy array of shape (H+2*pad_height, W+2*pad_width).
    """

    H, W = image.shape
    out = None

    ### YOUR CODE HERE
    # init out
    out = np.zeros((H+2*pad_height, W+2*pad_width))

    # fill the non-zero part
    out[pad_height : pad_height + H, pad_width : pad_width + W] = image
    ### END YOUR CODE

    return out


def conv_fast(image, kernel):
    """ An efficient implementation of convolution filter.

    This function uses element-wise multiplication and np.sum()
    to efficiently compute weighted sum of neighborhood at each
    pixel.

    Hints:
        - Use the zero_pad function you implemented above
        - There should be two nested for-loops
        - You may find np.flip() and np.sum() useful

    Args:
        image: numpy array of shape (Hi, Wi).
        kernel: numpy array of shape (Hk, Wk).

    Returns:
        out: numpy array of shape (Hi, Wi).
    """
    Hi, Wi = image.shape
    Hk, Wk = kernel.shape
    out = np.zeros((Hi, Wi))

    ### YOUR CODE HERE
    # pad iamge
    image = zero_pad(image, pad_height=Hk // 2, pad_width=Wk // 2)

    # flip kernel
    kernel = np.flipud(np.fliplr(kernel))

    # find sum
    for i in range(Hi):
        for j in range(Wi):
            out[i][j] += np.sum(image[i : i + Hk, j :  j + Wk] * kernel)

    out = out / np.sum(out)

    ### END YOUR CODE
    return out
    

def cross_correlation(f, g):
    """ Cross-correlation of f and g.

    Hint: use the conv_fast function defined above.

    Args:
        f: numpy array of shape (Hf, Wf).
        g: numpy array of shape (Hg, Wg).

    Returns:
        out: numpy array of shape (Hf, Wf).
    """

    out = None
    ### YOUR CODE HERE
    kernel = np.flipud(np.fliplr(g))

    out = conv_fast(f, kernel)
    ### END YOUR CODE

    return out

def zero_mean_cross_correlation(f, g):
    """ Zero-mean cross-correlation of f and g.

    Subtract the mean of g from g so that its mean becomes zero.

    Hint: you should look up useful numpy functions online for calculating the mean.

    Args:
        f: numpy array of shape (Hf, Wf).
        g: numpy array of shape (Hg, Wg).

    Returns:
        out: numpy array of shape (Hf, Wf).
    """

    out = None
    ### YOUR CODE HERE
    # find mean
    mean = np.mean(g)
    g = g - mean

    kernel = np.flipud(np.fliplr(g))

    out = conv_fast(f, kernel)
    ### END YOUR CODE

    return out

def normalized_cross_correlation(f, g):
    """ Normalized cross-correlation of f and g.

    Normalize the subimage of f and the template g at each step
    before computing the weighted sum of the two.

    Hint: you should look up useful numpy functions online for calculating 
          the mean and standard deviation.

    Args:
        f: numpy array of shape (Hf, Wf).
        g: numpy array of shape (Hg, Wg).

    Returns:
        out: numpy array of shape (Hf, Wf).
    """

    out = None
    ### YOUR CODE HERE
    # find arguments
    Hf, Wf = f.shape
    Hg, Wg = g.shape

    # pad
    f_padded =  zero_pad(f, pad_height=Hg // 2, pad_width=Wg // 2)

    # find cc
    out = np.zeros(f.shape)

    g_mean = np.mean(g)
    g_sigma = np.std(g)
    g_normal = (g - g_mean) / g_sigma
    
    for i in range(Hf):
        for j in range(Wf):
            patch_f = f_padded[i : i + Hg, j :  j + Wg]
            patch_mean = np.mean(patch_f)
            patch_sigma = np.std(patch_f)

            patch_normal = (patch_f - patch_mean) / patch_sigma
            
            out[i][j] = np.sum(patch_normal * g_normal)
    

    ### END YOUR CODE
    return out
