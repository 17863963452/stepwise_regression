#include "linear.h"
#include "./mean_module/mean_module.h"
#include "./step/step.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE* fp=fopen("./data/M_Atm_Nc_t.txt","r");
    int j=0,i=0;
    double f1,f2;
    double** arr=(double**)malloc(sizeof(double*)*88);
    double** correlation_arr;
    double* stepwise_regression_arr;
    //int a[3]={3,7,9};
    f1=f2=3.28;
    for(int i=0;i<88;i++)
        *(arr+i)=(double*)malloc(sizeof(double)*837);
    while(!feof(fp)){
        if(j==837){
            j=0;
            i++;
        }
        fscanf(fp,"%lf",*(arr+i)+j);
        j++;
    }
    //correlation_arr=correlation(arr,5,13);
    print(arr,88,837);
    //stepwise_regression_arr=stepwise_regression(arr,5,20,2,2);
    //correlation_arr=correlation(arr,5,13);
    //stepwise_regression_arr=stepwise regression(correlation_arr,5,13,3.28);
    //print(stepwise_regression_arr,2,sizeof(stepwise_regression_arr)/(*(*stepwise_regression_arr))/2);
    //sum_of_squares_of_deviations(arr,4,12);
    //print(regression,3,1);
    return 0;
}
