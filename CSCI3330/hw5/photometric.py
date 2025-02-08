# ##################################################################### #
# 16385: Computer Vision Homework 4
# Carnegie Mellon University
# Spring 2020
# ##################################################################### #

import numpy as np
from skimage.io import imread
from skimage.color import rgb2xyz
from matplotlib import pyplot as plt
from scipy.sparse import kron as spkron
from scipy.sparse import eye as speye
from scipy.sparse.linalg import lsqr as splsqr
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import warnings

def renderLambertianImage(albedoIm, normalIm, lightVec):

    """
    Question 1


    Parameters
    ----------
    albedoIm : numpy.ndarray
        Albedo image of shape h x w

    normalIm : numpy.ndarray
        Normals reshaped as an h x w x 3 image

    lightVec : numpy.ndarray
        Lighting vector of size 1 x 1 x 3

    Returns
    -------
    image : numpy.ndarray
        The rendered image
    """
    image = 0

    ### YOUR CODE HERE
    image = np.clip(np.sum(normalIm * lightVec, axis=-1) * albedoIm, 0, None)
    ### END YOUR CODE

    return image


def loadData(path = ".data/"):

    """
    Question 2

    Load data from the path given. The images are stored as input_n.tif
    for n = {1...7}. The source lighting directions are stored in
    sources.mat.

    Paramters
    ---------
    path: str
        Path of the data directory

    Returns
    -------
    I : numpy.ndarray
        The 7 x P matrix of vectorized images

    L : numpy.ndarray
        The 3 x 7 matrix of lighting directions

    s: tuple
        Image shape

    """

    ### YOUR CODE HERE
    # get I_mat
    images = []
    for i in range(1, 8):
        image_path = path + f"PhotometricStereo/female_0{i}.tif"
        image = imread(image_path, as_gray=True)
        images.append(image)

    # stack
    flattened_imgs = []
    for image in images:
        flattened_imgs.append(image.reshape(-1))

    I_mat = np.stack(flattened_imgs, axis=0)

    # load light source
    # get L
    L = np.load('data/sources.npy').T

    # get image shape
    s = images[0].shape

    ### END YOUR CODE

    return I_mat, L, s


def estimatePseudonormalsCalibrated(I, L):

    """
    Question 2

    In photometric stereo, estimate pseudonormals from the
    light direction and image matrices

    Parameters
    ----------
    I : numpy.ndarray
        The 7 x P array of vectorized images

    L : numpy.ndarray
        The 3 x 7 array of lighting directions

    Returns
    -------
    B : numpy.ndarray
        The 3 x P matrix of pesudonormals
    """

    B = None

    ### YOUR CODE HERE
    L = L.T     # P x 7
    B = np.linalg.inv(L.T @ L) @ L.T @ I
    ### END YOUR CODE

    return B


def estimateAlbedosNormals(B):

    '''
    Question 2

    From the estimated pseudonormals, estimate the albedos and normals

    Parameters
    ----------
    B : numpy.ndarray
        The 3 x P matrix of estimated pseudonormals

    Returns
    -------
    albedos : numpy.ndarray
        The vector of albedos

    normals : numpy.ndarray
        The 3 x P matrix of normals
    '''

    albedos = None
    normals = None

    ### YOUR CODE HERE
    albedos = np.sqrt(np.sum(B ** 2, axis=0)) # (P,)

    normals = B / (albedos + 1e-4)
    # normals = B / albedos

    ### END YOUR CODE

    return albedos, normals


def displayAlbedosNormals(albedos, normals, s):

    """
    Question 2

    From the estimated pseudonormals, display the albedo and normal maps

    Parameters
    ----------
    albedos : numpy.ndarray
        The vector of albedos

    normals : numpy.ndarray
        The 3 x P matrix of normals

    s : tuple
        Image shape

    Returns
    -------
    albedoIm : numpy.ndarray
        Albedo image of shape s

    normalIm : numpy.ndarray
        Normals reshaped as an s x 3 image

    """

    albedoIm = None
    normalIm = None

    ### YOUR CODE HERE
    albedoIm = albedos.reshape(s)
    normalIm = normals.T.reshape((*s, 3))
    ### END YOUR CODE

    return albedoIm, normalIm


def estimateShape(normals, s):

    """
    Question 2

    Integrate the estimated normals to get an estimate of the depth map
    of the surface.

    Parameters
    ----------
    normals : numpy.ndarray
        The 3 x P matrix of normals

    s : tuple
        Image shape

    Returns
    ----------
    surface: numpy.ndarray
        The image, of size s, of estimated depths at each point

    """

    surface = None

    ### YOUR CODE HERE
    # un-normalized normal
    # add a small value to the z coordinate before dividing
    non_normalized = normals / (normals[2, :] + 1e-6)
    # non_normalized = normals / normals[2, :]


    zx = non_normalized[0, :].reshape(s)
    zy = non_normalized[1, :].reshape(s)

    surface = integrateFrankot(zx, zy)

    ### END YOUR CODE

    return surface


def plotSurface(surface): 

    """
    Question 2 

    Plot the depth map as a surface

    Parameters
    ----------
    surface : numpy.ndarray
        The depth map to be plotted

    Returns
    -------
        None

    """
    ### YOUR CODE HERE
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Generate x, y coordinate grids
    x, y = np.meshgrid(np.arange(surface.shape[1]), np.arange(surface.shape[0]))

    # Plot the surface
    # ax.plot_surface(y, x, surface, cmap='viridis')
    ax.plot_surface(x,y, surface, cmap='viridis')


    # Set labels and title
    ax.set_title('3D Surface')

    # Show the plot
    plt.show()
    ### END YOUR CODE

def integrateFrankot(zx, zy, pad = 512):

    """
    Implement the Frankot-Chellappa algorithm for enforcing integrability
    and normal integration

    Parameters
    ----------
    zx : numpy.ndarray
        The image of derivatives of the depth along the x image dimension

    zy : tuple
        The image of derivatives of the depth along the y image dimension

    pad : float
        The size of the full FFT used for the reconstruction

    Returns
    ----------
    z: numpy.ndarray
        The image, of the same size as the derivatives, of estimated depths
        at each point

    """

    # Raise error if the shapes of the gradients don't match
    if not zx.shape == zy.shape:
        raise ValueError('Sizes of both gradients must match!')

    # Pad the array FFT with a size we specify
    h, w = 512, 512

    # Fourier transform of gradients for projection
    Zx = np.fft.fftshift(np.fft.fft2(zx, (h, w)))
    Zy = np.fft.fftshift(np.fft.fft2(zy, (h, w)))
    j = 1j

    # Frequency grid
    [wx, wy] = np.meshgrid(np.linspace(-np.pi, np.pi, w),
                           np.linspace(-np.pi, np.pi, h))
    absFreq = wx**2 + wy**2

    # Perform the actual projection
    with warnings.catch_warnings():
        warnings.simplefilter('ignore')
        z = (-j*wx*Zx-j*wy*Zy)/absFreq

    # Set (undefined) mean value of the surface depth to 0
    z[0, 0] = 0.
    z = np.fft.ifftshift(z)

    # Invert the Fourier transform for the depth
    z = np.real(np.fft.ifft2(z))
    z = z[:zx.shape[0], :zx.shape[1]]

    return z


