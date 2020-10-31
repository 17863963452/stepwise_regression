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
