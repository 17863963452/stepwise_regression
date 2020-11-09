## ./mean_module/mean_module.h

```c
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
void print(double** arr,int x,int y);
double** stdv(double** arr,int x,int y);
double** correlation(double** arr,int x,int y);
double* mean(double** arr,int x,int y);
double** cov(double** arr,int x,int y);
double det(double** arr,int x);
double partical_correlation(double** arr,int x,int y,int a,int b);
double multiple_correlation(double** arr,int x,int y,int a);
void swap(double* arr1,double* arr2,int x);
```

## ./mean_module/mean_module.c

```c
#include "mean_module.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
void print(double** arr,int x,int y){
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            printf("%f ",*(*(arr+i)+j));
        }
        printf("\n");
    }
}
double multiple_correlation(double** arr,int x,int y,int a){
    double det1,det2;
    int m=0,n=0;
    double** correlation_arr=correlation(arr,x,y);
    double** tmp=(double**)malloc(sizeof(double*)*(x-1));
    for(int i=0;i<x-1;i++)
        *(tmp+i)=(double*)malloc(sizeof(double)*(x-1));
    a--;
    for(int i=0;i<x-1;i++){
        if(m==a)m++;
        for(int j=0;j<x-1;j++){
            if(n==a)n++;
            *(*(tmp+i)+j)=*(*(correlation_arr+m)+n);
            n++;
        }
        m++;
        n=0;
    }
    det1=det(correlation_arr,x);
    det2=det(tmp,x-1)*pow(-1,a*2+2);
    for(int i=0;i<x;i++)
        free(*(correlation_arr+i));
    for(int i=0;i<x-1;i++)
        free(*(tmp+i));
    free(correlation_arr);
    free(tmp);
    return pow(1-det1/det2,0.5);
}
double partical_correlation(double** arr,int x,int y,int a,int b){
    int m=0,n=0,k=0,z=0;
    double tmp_det[3];
    double** correlation_arr=correlation(arr,x,y);
    double** tmp1=(double**)malloc(sizeof(double*)*(x-1));
    double** tmp2=(double**)malloc(sizeof(double*)*(x-1));
    double** tmp3=(double**)malloc(sizeof(double*)*(x-1));
    for(int i=0;i<x-1;i++){
        *(tmp1+i)=(double*)malloc(sizeof(double)*(x-1));
        *(tmp2+i)=(double*)malloc(sizeof(double)*(x-1));
        *(tmp3+i)=(double*)malloc(sizeof(double)*(x-1));
    }
    a--;
    b--;
    for(int i=0;i<x-1;i++){
        if(m==a)m++;
        if(k==b)k++;
        for(int j=0;j<x-1;j++){
            if(n==b)n++;
            if(z==a)z++;
            *(*(tmp1+i)+j)=*(*(correlation_arr+m)+n);
            *(*(tmp2+i)+j)=*(*(correlation_arr+m)+z);
            *(*(tmp3+i)+j)=*(*(correlation_arr+k)+n);
            n++;
            z++;
        }
        m++;
        k++;
        n=0;
        z=0;
    }
    tmp_det[0]=det(tmp1,x-1)*pow(-1,a+b+2);
    tmp_det[1]=det(tmp2,x-1)*pow(-1,a*2+2);
    tmp_det[2]=det(tmp3,x-1)*pow(-1,b*2+2);
    for(int i=0;i<x-1;i++){
        free(*(tmp1+i));
        free(*(tmp2+i));
        free(*(tmp3+i));
    }
    for(int i=0;i<x;i++)
        free(*(correlation_arr+i));
    free(tmp1);
    free(tmp2);
    free(tmp3);
    free(correlation_arr);
    return (-1.0)*tmp_det[0]/pow(tmp_det[1]*tmp_det[2],0.5);
}
double** stdv(double** arr,int x,int y){
    double** std_arr=(double**)malloc(sizeof(double*)*x);
    double* mean_arr=mean(arr,x,y);
    double** cov_arr=cov(arr,x,y);
    for(int i=0;i<x;i++)
        *(std_arr+i)=(double*)malloc(sizeof(double)*y);
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            *(*(std_arr+i)+j)=(*(*(arr+i)+j)-*(mean_arr+i))/pow((*(*(cov_arr+i)+i)),0.5);
        }
    }
    return std_arr;
}
double* mean(double** arr,int x,int y){
    double* mean_arr=(double*)malloc(sizeof(double)*x);
    double sum=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            sum+=*(*(arr+i)+j);
        }
        *(mean_arr+i)=sum/y;
        sum=0;
    }
    return mean_arr;
}
double** correlation(double** arr,int x,int y){
    double** correlation_arr=(double**)malloc(sizeof(double*)*x);
    double** std_arr=stdv(arr,x,y);
    double sum=0;
    for(int i=0;i<x;i++)
        *(correlation_arr+i)=(double*)malloc(sizeof(double)*x);
    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            for(int k=0;k<y;k++){
                sum+=(*(*(std_arr+i)+k))*(*(*(std_arr+j)+k));
            }
            *(*(correlation_arr+i)+j)=sum/(y-1);
            sum=0;
        }
    }
    return correlation_arr;
}
double** cov(double** arr,int x,int y){
    double** cov_arr=(double**)malloc(sizeof(double*)*x);
    double** anomaly_arr=(double**)malloc(sizeof(double*)*x);
    double* mean_arr=mean(arr,x,y);
    double sum=0,cov1=0;
    for(int i=0;i<x;i++){
        *(anomaly_arr+i)=(double*)malloc(sizeof(double)*y);
        *(cov_arr+i)=(double*)malloc(sizeof(double)*x);
    }
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            *(*(anomaly_arr+i)+j)=*(*(arr+i)+j)-*(mean_arr+i);
        }
    }
    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            for(int k=0;k<y;k++){
                sum+=(*(*(anomaly_arr+i)+k))*(*(*(anomaly_arr+j)+k));
            }
            *(*(cov_arr+i)+j)=sum/(y-1);
            sum=0;
        }
    }
    for(int i=0;i<x;i++)
        free(*(anomaly_arr+i));
    free(anomaly_arr);
    free(mean_arr);
    return cov_arr;
}
double det(double** arr,int x){
    double tmp[x],tmp1;
    double result=1;
    for(int i=0;i<x;i++){
        if(*(*(arr+i)+i)==0 && i!=x){
           swap(*(arr+i),*(arr+i+1),x);
           result*=(-1);
        }
        for(int j=i;j<x;j++){
            tmp[j]=*(*(arr+i)+j);
        }
        for(int k=i+1;k<x;k++){
            tmp1=*(*(arr+k)+i);
            for(int z=i;z<x;z++){
                *(*(arr+k)+z)+=(tmp[z]*(-1)*(tmp1/(tmp[i])));
            }
        }
    }
    for(int j=0;j<x;j++){
        result*=*(*(arr+j)+j);
    }
    return  result;
}
void swap(double* arr1,double* arr2,int x){
    double tmp;
    for(int i=0;i<x;i++){
        tmp=*(arr1+i);
        *(arr1+i)=*(arr2+i);
        *(arr2+i)=tmp;
    }
}

```

