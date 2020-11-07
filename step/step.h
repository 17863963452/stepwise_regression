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
