## ./step/sort.h

```c
void swap_a_b(double* a ,double* b);
int* sort(double* data1, int len);
```

## ./step/sort.c

```c
#include "sort.h"
#include <stdlib.h>
/***************************************************************
*Name            :swap_a_b
*Fun             :交换函数
*InputParaments  :a,b为两个数的地址;
*OutputParaments :None
****************************************************************/
void swap_a_b(double* a ,double* b) {
	double t;
	t = *a;
	*a = *b;
	*b = t;
}

/***************************************************************
*Name            :sort
*Fun             :冒泡排序，返回索引
*InputParaments  :data1是待排序的数据;len是数组长度。
*OutputParaments :索引数组
****************************************************************/
int* sort(double* data1, int len) {
    double data[len];
    int* index=(int*)malloc(sizeof(int)*len);
    double tmp[len];
	//索引初始化
	for (int i = 0; i < len; i++) {
		index[i] = i;
        data[i]=data1[i];
        tmp[i]=data[i];
	}
	for (int i = 0; i < len-1; i++) {
		for (int j = i+1 ; j < len; j++) {
            if (data[i] < data[j]) {
                swap_a_b(data+i,data+j);
            }
		}
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0 ; j < len; j++) {
            if(tmp[i]==data[j])
                index[i]=j;
        }
    }
    return index;
}
```

## ./step/step.h

```c
#include "../mean_module/mean_module.h"
#pragma once
double predict(double** arr,int x,int y,double* arr1);
void transformation(double** arr,int x,int y,int k);
double partical_correlation_cofficient(double** arr,int x,int k,int y,int l);
double* stepwise_regression(double** correlation_arr,int x,int y,double f1,double f2);
double* get_partical_correlation_cofficient_arr(double** correlation_arr,double x,double y);
int max(int* arr,int* status,int n);
int min(int* arr,int* status,int n);
double f_in(double** correlation_arr,int x,int y,double pcc,int l);
double f_out(double** correlation_arr,int x,int y,double pcc,int l);
```

## ./step/step.c

```c
#include "step.h"
#include "../mean_module/mean_module.h"
#include<stdlib.h>
#include "sort.h"
#define True 1
#define False 0
/***************************************************************
*Name            :f_out
*Fun             :F剔除计算函数
*InputParaments  :correlation_arr为相关系数阵的首地址，x,y分别为data的行列，pcc为偏相关系数,l为变换次数;
*OutputParaments :F剔除大小
****************************************************************/
double f_out(double** correlation_arr,int x,int y,double pcc,int l){
    double result=pcc/((*(*(correlation_arr+x-1)+x-1))/(y-l-1));
    return result;
}
/***************************************************************
*Name            :f_in
*Fun             :F引入计算函数
*InputParaments  :correlation_arr为相关系数阵的首地址，x,y分别为data的行列，pcc为偏相关系数,l为变换次数;
*OutputParaments :F引入大小
****************************************************************/
double f_in(double** correlation_arr,int x ,int y,double pcc,int l){
    double result=pcc/((*(*(correlation_arr+x-1)+x-1)-pcc)/(y-l-2));
    return result;
}
/***************************************************************
*Name            :predict
*Fun             :预报函数
*InputParaments  :arr为二维数组，x,y分别为arr的行列，arr1为预测环流指数数组;
*OutputParaments :预报结果
****************************************************************/
double predict(double** arr,int x,int y,double* arr1){
    double* a=stepwise_regression(arr,x,y,9,9);
    double result=0;
    for(int i=0;i<x-1;i++)
        result+=(*(a+i)*(*(arr1+i)));
    result+=*(a+x-1);
    free(a);
    return result;
}
/***************************************************************
*Name            :stepwise_regression
*Fun             :逐步回归函数
*InputParaments  :correlation_arr为相关系数阵的首地址，x,y分别为data的行列，f1为F alpha1,f2为F alphaa2;
*OutputParaments :回归函数系数数组
****************************************************************/
double* stepwise_regression(double** arr,int x,int y,double f1,double f2){
    double* arr1,**cov_arr,*mean_arr;
    double sum=0;
    double** correlation_arr;
    correlation_arr=correlation(arr,x,y);
    int* status=(int*)malloc(sizeof(int)*(x-1));
    double* result=(double*)malloc(sizeof(double)*(x-1));
    double* result1=(double*)malloc(sizeof(double)*x);
    int max_index,min_index;
    arr1=get_partical_correlation_cofficient_arr(correlation_arr,x,x);
    int l=0,w=0,j=0;
    for(int i=0;i<x-1;i++)
        status[i]=0;
    max_index=max(sort(arr1,x-1),status,x-1);
    min_index=min(sort(arr1,x-1),status,x-1);
    while(True){
        if(w>=3){
            if(f_out(correlation_arr,x,y,arr1[min_index],l)<f2&&status[min_index]==1){
                transformation(correlation_arr,x,x,min_index);
                status[min_index]=0;
                l++;
                w--;
            }
        }
        if(f_in(correlation_arr,x,y,arr1[max_index],l)>=f1&&status[max_index]==0){
            transformation(correlation_arr,x,x,max_index);
            status[max_index]=1;
            l++;
            w++;
        }else{break;}
        arr1=get_partical_correlation_cofficient_arr(correlation_arr,x,x);
        max_index=max(sort(arr1,x-1),status,x-1);
        min_index=min(sort(arr1,x-1),status,x-1);
    }
    for(int i=0;i<x-1;i++){
        if(status[i]==1)
            result[i]=*(*(correlation_arr+i)+x-1);
        else
            result[i]=0;
    }
    cov_arr=cov(arr,x,y);
    for(int i=0;i<x-1;i++)
        *(result+i)*=pow((*(*(cov_arr+x-1)+x-1)*(y-1))/(*(*(cov_arr+i)+i)*(y-1)),0.5);
    mean_arr=mean(arr,x,y);
    for(int i=0;i<x-1;i++){
       *(result1+i)=*(result+i);
       sum+=((*(result+i))*(*(mean_arr+i)));
    }
    *(result1+x-1)=*(mean_arr+x-1)-sum;
    free(result);
    return result1;
}
/***************************************************************
*Name            :min
*Fun             :求最小值索引的函数
*InputParaments  :arr为数组，status为是否引入方程，引入为1,不引入为0，n为数组的长度;
*OutputParaments :回归函数系数数组
****************************************************************/
int min(int* arr,int* status,int n){
    int j,k=0;
    for(int i=0;i<n;i++){
        if(status[i]==1){
            k++;
            if(k==1)
                j=i;
            if(arr[i]>arr[j])
                j=i;
        }
    }
    return j;
}
int max(int* arr,int* status,int n){
    int j,k=0;
    for(int i=0;i<n;i++){
        if(status[i]==0){
            k++;
            if(k==1)
                j=i;
            if(arr[i]<arr[j])
                j=i;
        }
    }
    free(arr);
    return j;
}
/***************************************************************
*Name            :partical_correlation_cofficient
*Fun             :偏相关系数函数
*InputParaments  :arr为数组，x,y分别为行列，k,l对应ppt;
*OutputParaments :偏相关系数
****************************************************************/
double partical_correlation_cofficient(double** arr,int x,int k,int y,int l){
    double result;
    transformation(arr,x,y,l);
    result=pow(*(*(arr+k)+y-1),2)/(*(*(arr+k)+k));
    transformation(arr,x,y,l);
    return result;
}
/***************************************************************
*Name            :get_partical_correlation_cofficient_arr
*Fun             :偏相关系数数组函数
*InputParaments  :correlation_arr为相关系数数组，x,y分别为行列;
*OutputParaments :偏相关系数数组首地址
****************************************************************/
double* get_partical_correlation_cofficient_arr(double** correlation_arr,double x,double y){
   double* a=(double*)malloc(sizeof(double)*(x-1));
   for(int i=0;i<x-1;i++){
       *(a+i)=partical_correlation_cofficient(correlation_arr,x-1,i,y,i);
   }
   return a;
}
/***************************************************************
*Name            :transformation
*Fun             :变换函数
*InputParaments  :correlation_arr为相关系数数组，x,y分别为行列，k对应ppt;
*OutputParaments :None
****************************************************************/
void transformation(double** correlation_arr,int x,int y,int k){
    double tmp_arr[x][y];
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            tmp_arr[i][j]=*(*(correlation_arr+i)+j);
        }
    }
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(i==k&&j==k)
                *(*(correlation_arr+i)+j)=1/tmp_arr[k][k];
            else if(i!=k&&j==k)
                *(*(correlation_arr+i)+j)=(-1)*tmp_arr[i][k]/tmp_arr[k][k];
            else if(i==k&&j!=k)
                *(*(correlation_arr+i)+j)=tmp_arr[k][j]/tmp_arr[k][k];
            else
                *(*(correlation_arr+i)+j)=tmp_arr[i][j]-tmp_arr[i][k]*tmp_arr[k][j]/tmp_arr[k][k];
        }
    }
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            tmp_arr[i][j]=*(*(correlation_arr+i)+j);
        }
    }
}
```

