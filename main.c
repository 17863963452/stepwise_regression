#include "linear.h"
#include "./mean_module/mean_module.h"
#include "./step/step.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE* fp=fopen("./data/result.txt","r");
    int j=0,i=0;
    double f1,f2;
    double** arr=(double**)malloc(sizeof(double*)*89);
    double** arr1=(double**)malloc(sizeof(double*)*89);
    double** correlation_arr;
    double* stepwise_regression_arr;
    double* predict_arr=(double*)malloc(sizeof(double)*88);
    f1=f2=3.28;
    for(int i=0;i<89;i++){
        *(arr+i)=(double*)malloc(sizeof(double)*837);
        *(arr1+i)=(double*)malloc(sizeof(double)*83);
    }
    while(!feof(fp)){
        if(j==837){
            j=0;
            i++;
        }
        fscanf(fp,"%lf",*(arr+i)+j);
        j++;
    }
    for(int i=0;i<89;i++){
        for(int j=750;j<833;j++){
            *(*(arr1+i)+j-750)=*(*(arr+i)+j);
        }
    }
    for(int i=0;i<88;i++)
        *(predict_arr+i)=*(*(arr+i)+833);
    //correlation_arr=correlation(arr,5,13);
    //stepwise_regression_arr=stepwise_regression(arr,5,20,2,2);
    // correlation_arr=correlation(arr,89,834);
    //stepwise_regression_arr=stepwise_regression(arr,89,837,2,2);
    printf("%f\n",predict(arr,89,833,predict_arr));
    //printf("%f\n",r(arr,89,833));
    //print(stepwise_regression_arr,2,sizeof(stepwise_regression_arr)/(*(*stepwise_regression_arr))/2);
    //sum_of_squares_of_deviations(arr,4,12);
    //print(regression,3,1);
    return 0;
}
