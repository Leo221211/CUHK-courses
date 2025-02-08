import numpy as np
import cv2
import random
import sys

if(len(sys.argv) <2):
    print('Error')
else:
    Input_Image=sys.argv[1]

# load image in "original_image"

K= cv2.imread(Input_Image,1)


# load image in "original_image"

#K= cv2.imread("C:\Desktop\CSE 573\Project 1\Project #2 Image_House.jpg",1)

row=K.shape[0]
col=K.shape[1]

J= row * col
Size = row,col,3
R = np.zeros(Size, dtype= np.uint8)
D=np.zeros((J,5))
arr=np.array((1,3))

#cv2.imshow("image", K)

counter=0  
iter=1.0        


threshold=30
current_mean_random = True
current_mean_arr = np.zeros((1,5))
below_threshold_arr=[]

# converted the image K[rows][col] into a feature space D. The dimensions of D are [rows*col][5]
for i in range(0,row):
    for j in range(0,col):      
        arr= K[i][j]
        
        for k in range(0,5):
            if(k>=0) & (k <=2):
                D[counter][k]=arr[k]
            else:
                if(k==3):
                    D[counter][k]=i
                else:
                    D[counter][k]=j
        counter+=1

while(len(D) > 0):
    #print J
    print(len(D))
#selecting a random row from the feature space and assigning it as the current mean    
    if(current_mean_random):
        current_mean= random.randint(0,len(D)-1)
        for i in range(0,5):
            current_mean_arr[0][i] = D[current_mean][i]
    below_threshold_arr=[]
    for i in range(0,len(D)):
        #print "Entered here"
        ecl_dist = 0
        color_total_current = 0
        color_total_new = 0
#Finding the eucledian distance of the randomly selected row i.e. current mean with all the other rows
        for j in range(0,5):
            ecl_dist += ((current_mean_arr[0][j] - D[i][j])**2)
                
        ecl_dist = ecl_dist**0.5

#Checking if the distance calculated is within the threshold. If yes taking those rows and adding 
#them to a list below_threshold_arr
      
        if(ecl_dist < threshold):
            below_threshold_arr.append(i)
            #print "came here"  
    
    mean_R=0
    mean_G=0
    mean_B=0
    mean_i=0
    mean_j=0
    current_mean = 0
    mean_col = 0
    
#For all the rows found and placed in below_threshold_arr list, calculating the average of 
#Red, Green, Blue and index positions.
    
    for i in range(0, len(below_threshold_arr)):
        mean_R += D[below_threshold_arr[i]][0]
        mean_G += D[below_threshold_arr[i]][1]
        mean_B += D[below_threshold_arr[i]][2]
        mean_i += D[below_threshold_arr[i]][3]
        mean_j += D[below_threshold_arr[i]][4]   
    
    mean_R = mean_R / len(below_threshold_arr)
    mean_G = mean_G / len(below_threshold_arr)
    mean_B = mean_B / len(below_threshold_arr)
    mean_i = mean_i / len(below_threshold_arr)
    mean_j = mean_j / len(below_threshold_arr)
    
#Finding the distance of these average values with the current mean and comparing it with iter

    mean_e_distance = ((mean_R - current_mean_arr[0][0])**2 + (mean_G - current_mean_arr[0][1])**2 + (mean_B - current_mean_arr[0][2])**2 + (mean_i - current_mean_arr[0][3])**2 + (mean_j - current_mean_arr[0][4])**2)
    
    mean_e_distance = mean_e_distance**0.5
    
    

    nearest_i = 0
    min_e_dist = 0
    counter_threshold = 0
# If less than iter, find the row in below_threshold_arr that has i,j nearest to mean_i and mean_j
#This is because mean_i and mean_j could be decimal values which do not correspond
#to actual pixel in the Image array.

    if(mean_e_distance < iter):
        #print "Entered here"
        '''    
        for i in range(0, len(below_threshold_arr)):
            new_e_dist = ((mean_i - D[below_threshold_arr[i]][3])**2 + (mean_j - D[below_threshold_arr[i]][4])**2 + (mean_R - D[below_threshold_arr[i]][0])**2 +(mean_G - D[below_threshold_arr[i]][1])**2 + (mean_B - D[below_threshold_arr[i]][3])**2)
            new_e_dist = new_e_dist**0.5
            if(i == 0):
                min_e_dist = new_e_dist
                nearest_i = i
            else:
                if(new_e_dist < min_e_dist):
                    min_e_dist = new_e_dist
                    nearest_i = i
'''                    
        new_arr = np.zeros((1,3))
        new_arr[0][0] = mean_R
        new_arr[0][1] = mean_G
        new_arr[0][2] = mean_B
        
# When found, color all the rows in below_threshold_arr with 
#the color of the row in below_threshold_arr that has i,j nearest to mean_i and mean_j
        for i in range(0, len(below_threshold_arr)):    
            R[D[below_threshold_arr[i]][3]][D[below_threshold_arr[i]][4]] = new_arr
            
# Also now don't use those rows that have been colored once.
            
            D[below_threshold_arr[i]][0] = -1
        current_mean_random = True
        new_D=np.zeros((len(D),5))
        counter_i = 0
        
        for i in range(0, len(D)):
            if(D[i][0] != -1):
                new_D[counter_i][0] = D[i][0]
                new_D[counter_i][1] = D[i][1]
                new_D[counter_i][2] = D[i][2]
                new_D[counter_i][3] = D[i][3]
                new_D[counter_i][4] = D[i][4]
                counter_i += 1
            
        
        D=np.zeros((counter_i,5))
        
        counter_i -= 1
        for i in range(0, counter_i):
            D[i][0] = new_D[i][0]
            D[i][1] = new_D[i][1]
            D[i][2] = new_D[i][2]
            D[i][3] = new_D[i][3]
            D[i][4] = new_D[i][4]
        
    else:
        current_mean_random = False
        
        current_mean_arr[0][0] = mean_R
        current_mean_arr[0][1] = mean_G
        current_mean_arr[0][2] = mean_B
        current_mean_arr[0][3] = mean_i
        current_mean_arr[0][4] = mean_j
            
        #cv2.imwrite("image"+ str(len(below_threshold_arr)) +".png", K)
            
    #if(len(total_array) >= 40000):
        #break
cv2.imshow("finalImage", R)
            #print  arr       
'''
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
#Axis3D(I)'''