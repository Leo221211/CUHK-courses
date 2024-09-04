import numpy as np
import matplotlib.pyplot as plt
import sys
import math

def logistic_function(w,point):
    wTx=np.dot(w,point)
    return math.exp(wTx)/(1+math.exp(wTx))

def loss_cal(w):
    error=0
    i=0
    for point in points_position[:]:
        h=logistic_function(w,point)
        error-=points_label[i]*np.log(h)+(1-points_label[i])*np.log(1-h)
        i+=1
    error/=size
    return error
    
def logistic_regression(w):
    gradient=[0,0,0]
    i=0
    for point in points_position[:]:
        point = np.transpose(point)
        gradient+=point*(logistic_function(w,point)-points_label[i])
        i+=1
    gradient/=size
    gradient*=learning_rate
    gradient=np.transpose(gradient)
    w=w-gradient
    return w

def data_plot(points_position,points_label):
    colors=['red' if label==1 else 'blue' for label in points_label]
    plt.scatter(points_position[:,0],points_position[:,1],c=colors)
    plt.xlim(0,100)
    plt.ylim(0,100)
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.show()

def error_step_plot():
    colors='blue'
    plt.scatter(step[:], error_array[:], c=colors)
    plt.xlim(0, len(step))
    plt.ylim(0, np.ceil(np.amax(error_array)))
    plt.xlabel("num_of_steps")
    plt.ylabel("error")
    plt.show()

def cal_accuracy(w):
    accuracy=0
    i=0
    for point in points_position[:]:
        if ((logistic_function(w,point)<0.5)&(points_label[i]==0))|((logistic_function(w,point)>0.5)&(points_label[i]==1)):
            accuracy +=1
        i+=1
    accuracy/=size
    return accuracy

if __name__ == '__main__':
    learning_rate=0.002
    size=20
    w=np.array([0.0, 0.,  0.])
    error_array=np.empty((0,))
    step=np.arange(0,100000,1000)
    # step=np.arange(0,1000)
    
    points_position_list=[[4 ,5 ,12,29,30,36,36,54,58,70,72,76,78,82,87,90,90,92,95,98],
                          [49,4 ,28,18,65,32,1 ,29,76,12,26,55,4 ,15,95,70,55,84,14,21],
                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
                          ]
    points_position = np.array(points_position_list)
    points_position=np.transpose(points_position)
    points_label = np.array([0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0])
    data_plot(points_position,points_label)
    for i in range (0,100):
        w=logistic_regression(w)
        #error_array = np.append(error_array, loss_cal(w))
        if i%1000==0:
            error_array=np.append(error_array,loss_cal(w))
    #print(error_array)
    print(w)
    # print(error_array[99])
    error_step_plot()
    print(cal_accuracy(w))