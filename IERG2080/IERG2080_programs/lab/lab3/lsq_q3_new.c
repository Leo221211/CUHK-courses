#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    double endTime,beginTime;
    int N,j,val=0,p=0,save=0;
    int sum=0,numm=0;
    beginTime=clock();
    scanf("%d",&N);
    int* num1;
    num1=(int*)malloc(N*sizeof(int));
    for(int i=0;i<N;i++){
        scanf("%d",&num1[i]);
        if(num1[i]<=0)numm++;
    }
    sum=num1[0];
    if(N==1){
        sum=save=num1[0];
        printf("%d",sum);
        free(num1);
        return 0;
    }
    if(N==2){
        if(num1[0]>0&&num1[1]>0)sum=sum+num1[0]+num1[1];
        else if(num1[0]>0&&num1[1]<=0)sum=num1[0];
        else if(num1[0]<=0&&num1[1]>0)sum=num1[1];
        else if(num1[0]<=0&&num1[1]<=0){
            if(num1[1]>num1[0])sum=num1[1];
            else sum=num1[0];
        }
        printf("%d",sum);
        free(num1);
        return 0;
    }
    if(numm==N){
        for(int i=0;i<N;i++){
            if(sum<num1[i])sum=num1[i];
        }
        printf("%d",sum);
        free(num1);
        return 0;
    }
    for(j=1;j<N-1;j++){
        if(save<sum)save=sum;
        if(num1[j]<=0){
            val=0;
            for(int i=j;i<N&&num1[i]<=0;i++){
                val+=num1[i];
                if(num1[i+1]>0&&i+1<N){
                    val+=num1[i+1];
                    j=i+1;
                }
                p=i+1;
            }
            if(p==N){
                    for(int l=p;l<N;l++){
                        if(sum>0){
                            printf("%d",sum);
                            free(num1);
                            return 0;
                        }
                        else if(sum<=0){
                            if(num1[l]>sum)sum=num1[l];
                        }
                    }
                    printf("%d",sum);
                    free(num1);
                    return 0;
                }
            if(j<N-1){
                if(sum+val>num1[j])sum+=val;
                else if(sum+val<=num1[j])sum=num1[j];
            }
            else if(j==N-1){
                if(sum+val>num1[j]&&val>0)sum+=val;
                else if(sum+val<=num1[j]&&sum<=num1[j])sum=num1[j];
            }
        }
        else if(num1[j]>0){
            if(sum>0)sum+=num1[j];
            else if(sum<=0)sum=num1[j];
        }
    }
    if(num1[N-1]>0&&num1[N-2]>0&&num1[N-3]<=0){
        if(sum>0)sum+=num1[N-1];
        else if(sum<=0)sum=num1[N-1];
    }
    else if(num1[N-1]>0&&num1[N-2]>0&&num1[N-3]>0){
        if(sum>0)sum+=num1[N-1];
        else if(sum<=0)sum=num1[N-1];
    }
    printf("%d ",save);
    free(num1);
    endTime=clock();
    printf("%lf ",endTime-beginTime);
    return 0;
}