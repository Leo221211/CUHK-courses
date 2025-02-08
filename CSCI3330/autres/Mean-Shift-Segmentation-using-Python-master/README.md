# Mean-Shift-Segmentation-using-Python
Performed the mean shift segmentation to track objects over image sequences.
Mean Shift Segmentation
Implemented by:
Agam Deep Arora (50169805)
&
Debika Dutt (50170009)
Submission date: 14-Dec-15
2. Literature review
a. Review of the technologies in the project
While working on this project we learned to program in Python. We learned the functionalities of many python functions such as imread for reading an input, imshow to display the output and various others. We also learned about various Python libraries like scipy, numpy, sys, random and opencv. We realized the subtle difference python has from all of its contemporary languages like MATLAB.
b. Basic technologies learned in class:
1. Boundary preserving filtering by applying median filter to the input image
2. Mean Shift Filtering
3. Thresholding
4. Calculating Euclidean distance from one pixel to the other
5. Applications of normal or Epanechnikov kernels
6. Mean shift vector
7. Cluster Analysis
8. Image Segmentation
3. Project Final Report
Introduction
i) Mainly from literature reviews: Mean shift is a simple iterative process that shifts each data point to the average of data points in its neighborhood. This is considered as the local maxima of the probability density (density modes) given by the samples. Hence Mean shift segmentation avoids the estimation of probability density functions. No parameters are estimated and no specific function form is assumed. This technique was proposed by Fukunaga and Hostetler in the year 1975 and was recently generalized by Cheng. This generalization makes k-means like clustering algorithms in special cases. For Gaussian kernels, mean shift is a gradient mapping. Convergence is studied for mean shift iterations. Cluster analysis is treated as a deterministic problem of finding a fixed point of mean shift that characterizes the data.
ii) Overview of the project carried out: Mean shift is a non-parametric feature-space analysis technique to partition the image into semantically meaningful regions done by clustering the pixels in the image. We applied mean shift procedure to the plotted points after mapping the image on a feature space. We continue the process until
each point shifts towards a high density region until convergence. Lastly we retrace the image from the plotted dense points on the feature space.
The algorithms implemented are given below:
Mode Detection
 Using multiple initializations covering the entire feature space, employ the mean shift procedure to identify the stationary points of f(h,k).
 Prune these points to only retain the local maxima corresponding to the density modes.
Discontinuity Preserving filtering
 For each image pixel x(i), initialize step j=1 and y(I,1)=x(i)
 Compute y(I,j+1) until convergence y(i,cor).
 The filtered pixel values are defined as z(i)= (x(i)**s, y(i)**r
Mean shift image segmentation
 Employ the Mean shift discontinuity preserving filtering and store all the information about the d-dimensional convergence points y(i,con).
 Determine the clusters {C(p)}p=1,…,m by grouping all z(i) which are closer than hs in spatial domain and hr in the range domain.
 Assign L(i)={p|z(i)EC(p)} for each pixel i=1,…,n.
 If required eliminate regions smaller than P pixels.
Our Approach:
Working of the overall system:
1. The input image had r rows and c columns with each pixel having intensity values of R,G and B
2. The image features is extracted in a vector matrix M with dimensions [r*c],[5]containing range and spatial information.
3. We set a single threshold value h for this spatial range feature matrix and convergence criterion value iter.
4. A random row is selected from the vector matrix M as initial seed point which is the current mean.
5. We then calculate the Euclidean distance of all the other pixels in M with the current mean.
6. The distance is then compared with the threshold and if the value is within threshold we store the rows in a list.
7. We then find the new mean by averaging out each column of the selected points.
8. If the distance of the new mean and the current mean is less than iter the new mean is assigned to all the pixels in the image. After the convergence, we eliminate the indexes of all those pixels which are already marked.
9. Otherwise, we make the new mean as the current mean and this iteration is repeated again until we exhaust of all points.
i) Software used to implement: Enthought Canopy 1.6.1
Outcome and deviations:
i. Presentation of the project outcome:
The outcome of this project depends on the following criterion:
1. If the input image is of dimensions 512*512 and after it has been extracted into the feature space as 262144, 5 we must ensure that our mean shift algorithm is able to traverse all the rows until every point is exhausted.
2. If the Euclidean distance is within the threshold we ensure that we store the value of the rows within a list.
3. If the distance between the new mean and the current mean is greater than the iter value we set new mean value to all pixel points. Otherwise, new mean is set as the current mean.]
ii. Discussion of the outcome:
 Initially when we considered only RGB values without considering pixel co-ordinates/ location, the output image was missing many colors. The prominent features got lost with the insignificant features giving us only a rough output very different from the desired output. Therefore, we must include the image pixel index values in our Euclidean distance formula to get the desired output.
Incorrect outputs

 Also, there was a case when we misunderstood the fact the input image has e rows and c columns with each pixel having three colors R,G,B. We thought that the image is a 2D array with each pixel having either R, G or B value.
iii. Lessons learned from algorithmic development:
If we apply a uniform weighted kernel that assigns a weight of 1 to all pixels we get a rough image outcome with the image boundaries not properly outlined.
Now, on using a kernel (Preferably a normal or epanechnikov kernel), boundaries are properly outlined. We get two thresholds hs and hr with the kernels and apply the mean shift edge preserving filtering and store all the converged mean points. We get segmented boundaries over the original image.
Summary and Discussion
The Mean shift segmentation routine is implemented in two phases:
1) Mode Detection and Discontinuity preserving filtering
2) Mean Shift Clustering
• During the implementation, we have made sure that the image noise has been removed while the boundaries are preserved. Also as shown in the image above, when the feature space is created, the Red, Green and Blue values in each image pixel must be removed and placed in a new array. There were a wide variety of clustering strategies that were available like Agglomerative clustering, Divisive clustering, K-means clustering and K-medoids of which K-means clustering has been used.
The Mean shift segmentation has the following applications:
 Clustering
 Smoothing
 Tracking
Following are the Strengths and Weaknesses of the implemented algorithm:
Strengths
 The algorithm doesn’t assume any prior shape of data clusters
 It does not require to estimate the probability density function which reduces complexity by a huge margin.
 The code can handle arbitrary feature spaces.
 This code when improvised in real time, would be platform independent.
Weaknesses
 The window size (bandwidth selection) is not trivial
 Inappropriate window size can cause modes to be merged, or generate additional “shallow” modes  Use adaptive window size.
Lessons learned
We learned about various concepts in Computer Vision and Image Processing like image formation and its properties, basic image understanding techniques, how to represent an image mathematically, Image processing fundamentals, basic image segmentation techniques, Mathematical morphology for shape analysis. From homework problems we learnt to do various image processing techniques such as image convolution and image histogram equalization.
While working on this project we learned to program in Python. We learned the functionalities of many python functions such as imread for reading an input, imshow to display the output and various others. We also learned about various Python libraries like scipy, numpy, sys, random and opencv. We realized the subtle difference python has from all of its contemporary languages like MATLAB. Our working on the project made our concepts in Mean shift Segmentation, Mode detection and Discontinuity Preserving Filtering crystal clear.
Acknowledgement
We are very thankful to our Professor Dr.Chang Wen Cheng for teaching us Computer Vision and Image Processing and how to do Mean Shift. This project could not have been successfully completed without the help of our teaching assistant Radhakrishna Dasari, who was always ready to help with any doubts related to our project.
References: https://en.wikipedia.org/wiki/Mean_shift#Applications http://luthuli.cs.uiuc.edu/~daf/courses/CS-498-DAF-PS/Segmentation.pdf http://comaniciu.net/Papers/RobustAnalysisFeatureSpaces.pdf http://home.ku.edu.tr/mehyilmaz/public_html/mean-shift/00400568.pdf https://saravananthirumuruganathan.wordpress.com/2010/04/01/introduction-to-mean-shift-algorithm/ Lecture slides.
