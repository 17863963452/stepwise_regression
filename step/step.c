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
*Name            :stepwise_regression
*Fun             :逐步回归函数
*InputParaments  :correlation_arr为相关系数阵的首地址，x,y分别为data的行列，f1为F alpha1,f2为F alphaa2;
*OutputParaments :回归函数系数数组
****************************************************************/
double* stepwise_regression(double** correlation_arr,int x,int y,double f1,double f2){
    double* arr;
    int* status=(int*)malloc(sizeof(int)*(x-1));
    double* result=(double*)malloc(sizeof(double)*(x-1));
    int max_index,min_index;
    arr=get_partical_correlation_cofficient_arr(correlation_arr,x,x);
    int l=0,w=0,j=0;
    for(int i=0;i<x-1;i++)
        status[i]=0;
    max_index=max(sort(arr,x-1),status,x-1);
    min_index=min(sort(arr,x-1),status,x-1);
    while(True){
        if(w>=3){
            if(f_out(correlation_arr,x,y,arr[min_index],l)<f2&&status[min_index]==1){
                transformation(correlation_arr,x,x,min_index);
                status[min_index]=0;
                l++;
                w--;
            }
        }
        if(f_in(correlation_arr,x,y,arr[max_index],l)>=f1&&status[max_index]==0){
            transformation(correlation_arr,x,x,max_index);
            status[max_index]=1;
            l++;
            w++;
        }else{break;}
        arr=get_partical_correlation_cofficient_arr(correlation_arr,x,x);
        max_index=max(sort(arr,x-1),status,x-1);
        min_index=min(sort(arr,x-1),status,x-1);
    }
    for(int i=0;i<x-1;i++){
        if(status[i]==1)
            result[i]=*(*(correlation_arr+i)+x-1);
        else
            result[i]=0;
        printf("%f\n",result[i]);
    }
    return result;
}
/***************************************************************
*Name            :min
*Fun             :求最小值索引的函数
*InputParaments  :arr为数组，n为数组的长度，m为;
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
double partical_correlation_cofficient(double** arr,int x,int k,int y,int l){
    double result;
    transformation(arr,x,y,l);
    result=pow(*(*(arr+k)+y-1),2)/(*(*(arr+k)+k));
    transformation(arr,x,y,l);
    return result;
}
double* get_partical_correlation_cofficient_arr(double** correlation_arr,double x,double y){
   double* a=(double*)malloc(sizeof(double)*(x-1));
   for(int i=0;i<x-1;i++){
       *(a+i)=partical_correlation_cofficient(correlation_arr,x-1,i,y,i);
   }
   return a;
}
double** transformation(double** correlation_arr,int x,int y,int k){
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
