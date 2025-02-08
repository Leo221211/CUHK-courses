from typing import Tuple

import numpy as np


def camera_from_world_transform(d: float = 1.0) -> np.ndarray:
    """Define a transformation matrix in homogeneous coordinates that
    transforms coordinates from world space to camera space, according
    to the coordinate systems in Question 1.


    Args:
        d (float, optional): Total distance of displacement between world and camera
            origins. Will always be greater than or equal to zero. Defaults to 1.0.

    Returns:
        T (np.ndarray): Left-hand transformation matrix, such that c = Tw
            for world coordinate w and camera coordinate c as column vectors.
            Shape = (4,4) where 4 means 3D+1 for homogeneous.
    """
    T = np.eye(4)
    ### YOUR CODE HERE
    # find rotate matrix
    row1 = np.array([-1 / np.sqrt(2), 0, 1 /  np.sqrt(2)])
    row2 = np.array([0, 1, 0])
    row3 = np.array([-1 / np.sqrt(2), 0, -1 /  np.sqrt(2)])
    R = np.vstack((row1, row2, row3))
    T[:3, :3] = R

    # shift
    t = np.array([0, 0, np.sqrt(2)]).T
    T[0:3, 3] = t
    ### END YOUR CODE
    assert T.shape == (4, 4)
    return T


def apply_transform(T: np.ndarray, points: np.ndarray) -> Tuple[np.ndarray]:
    """Apply a transformation matrix to a set of points.

    Hint: You'll want to first convert all of the points to homogeneous coordinates.
    Each point in the (3,N) shape edges is a length 3 vector for x, y, and z, so
    appending a 1 after z to each point will make this homogeneous coordinates.

    You shouldn't need any loops for this function.

    Args:
        T (np.ndarray):
            Left-hand transformation matrix, such that c = Tw
                for world coordinate w and camera coordinate c as column vectors.
            Shape = (4,4) where 4 means 3D+1 for homogeneous.
        points (np.ndarray):
            Shape = (3,N) where 3 means 3D and N is the number of points to transform.

    Returns:
        points_transformed (Tuple of np.ndarray):
            Transformed points.
            Shape = (3,N) where 3 means 3D and N is the number of points.
    """
    N = points.shape[1]
    assert points.shape == (3, N)

    # You'll replace this!
    points_transformed = np.zeros((3, N))

    ### YOUR CODE HERE
    # to homogeneous
    points_homogeneous = np.vstack((points, np.ones((1, N))))

    # transform
    # points_transformed_h = camera_from_world_transform() @ points_homogeneous 
    points_transformed_h = T @ points_homogeneous 


    # to normal
    points_transformed_h = points_transformed_h / points_transformed_h[3, :]
    points_transformed = points_transformed_h[:3, :]

    ### END YOUR CODE

    assert points_transformed.shape == (3, N)
    return points_transformed


def intersection_from_lines(
    a_0: np.ndarray, a_1: np.ndarray, b_0: np.ndarray, b_1: np.ndarray
) -> np.ndarray:
    """Find the intersection of two lines (infinite length), each defined by a
    pair of points.

    Args:
        a_0 (np.ndarray): First point of first line; shape `(2,)`. # x1, y1
        a_1 (np.ndarray): Second point of first line; shape `(2,)`. # x2, y2
        b_0 (np.ndarray): First point of second line; shape `(2,)`. #x3, y3
        b_1 (np.ndarray): Second point of second line; shape `(2,)`. #x4, y4

    Returns:
        np.ndarray:
    """
    # Validate inputs
    assert a_0.shape == a_1.shape == b_0.shape == b_1.shape == (2,)
    assert a_0.dtype == a_1.dtype == b_0.dtype == b_1.dtype == float

    # Intersection point between lines
    out = np.zeros(2)

    ### YOUR CODE HERE
    # cramers rule
    y2_y1 = a_1[1] - a_0[1]
    x1_x2 = a_0[0] - a_1[0]
    y4_y3 = b_1[1] - b_0[1]
    x3_x4 = b_0[0] - b_1[0]
    x1y2_x2y1 = a_0[0] * a_1[1] - a_1[0] * a_0[1]
    x3y4_x4y3 = b_0[0] * b_1[1] - b_1[0] * b_0[1]

    A = np.array([[y2_y1, x1_x2],
                  [y4_y3, x3_x4]])
    A1 = np.array([[x1y2_x2y1, x1_x2],
                   [x3y4_x4y3, x3_x4]])
    A2 = np.array([[y2_y1, x1y2_x2y1],
                  [y4_y3, x3y4_x4y3]])
    
    det_A = np.linalg.det(A)
    det_A1 = np.linalg.det(A1)
    det_A2 = np.linalg.det(A2)
    out[0] = det_A1 / det_A
    out[1] = det_A2 / det_A
    ### END YOUR CODE

    assert out.shape == (2,)
    assert out.dtype == float

    return out


def optical_center_from_vanishing_points(
    v0: np.ndarray, v1: np.ndarray, v2: np.ndarray
) -> np.ndarray:
    """Compute the optical center of our camera intrinsics from three vanishing
    points corresponding to mutually orthogonal directions.

    Hints:
    - Your `intersection_from_lines()` implementation might be helpful here.
    - It might be worth reviewing vector projection with dot products.

    Args:
        v0 (np.ndarray): Vanishing point in image space; shape `(2,)`.
        v1 (np.ndarray): Vanishing point in image space; shape `(2,)`.
        v2 (np.ndarray): Vanishing point in image space; shape `(2,)`.

    Returns:
        np.ndarray: Optical center; shape `(2,)`.
    """
    assert v0.shape == v1.shape == v2.shape == (2,), "Wrong shape!"

    optical_center = np.zeros(2)

    ### YOUR CODE HERE
    X1 = v0[0]
    Y1 = v0[1]
    X2 = v1[0]
    Y2 = v1[1]
    X3 = v2[0]
    Y3 = v2[1]

    A = np.array([[X3-X1, Y3-Y1],
                 [X3-X2, Y3-Y2]])
    A1 = np.array([[(X3-X1)* X2 + (Y3-Y1)*Y2, Y3-Y1],
                 [(X3-X2)* X1 + (Y3-Y2)*Y1, Y3-Y2]])
    A2 = np.array([[X3-X1, (X3-X1)* X2 + (Y3-Y1)*Y2],
                 [X3-X2, (X3-X2)* X1 + (Y3-Y2)*Y1]])
    
    det_A = np.linalg.det(A)
    det_A1 = np.linalg.det(A1)
    det_A2 = np.linalg.det(A2)
    optical_center[0] = det_A1 / det_A
    optical_center[1] = det_A2 / det_A
    ### END YOUR CODE

    assert optical_center.shape == (2,)
    return optical_center


def focal_length_from_two_vanishing_points(
    v0: np.ndarray, v1: np.ndarray, optical_center: np.ndarray
) -> np.ndarray:
    """Compute focal length of camera, from two vanishing points and the
    calibrated optical center.

    Args:
        v0 (np.ndarray): Vanishing point in image space; shape `(2,)`.
        v1 (np.ndarray): Vanishing point in image space; shape `(2,)`.
        optical_center (np.ndarray): Calibrated optical center; shape `(2,)`.

    Returns:
        float: Calibrated focal length.
    """
    assert v0.shape == v1.shape == optical_center.shape == (2,), "Wrong shape!"

    f = None

    ### YOUR CODE HERE
    x1 = v0[0]
    x2 = v0[1]

    y1 = v1[0]
    y2 = v1[1]

    cx = optical_center[0]
    cy = optical_center[1]

    f = np.sqrt(cx*(x1+y1) + cy*(x2+y2)  -x2*y2 -x1*y1 -(cx**2+cy**2))

    ### END YOUR CODE

    return float(f)