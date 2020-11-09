#include "test.h"
#include"../mean_module/mean_module.h"
#include<stdlib.h>
double check(double** arr,int x,int y){
    return (regression_sum_of_squares(arr,x,y)/(x-1))/(sum_of_squares_of_deviations(arr,x,y)/(y-x));
}
double r(double** arr,int x,int y){
    double ssod=sum_of_squares_of_deviations(arr,x,y);
    double** cov_arr=cov(arr,x,y);
    double tmp=*(*(cov_arr+x-1)+x-1)*(y-1);
    return pow(1-ssod/tmp,0.5);
}
double residual_variance(double** arr,int x,int y){
    double ssod=sum_of_squares_of_deviations(arr,x,y);
    return ssod/(y-x-2);
        
}
double regression_sum_of_squares(double** arr,int x,int y){
    double* mean_arr=mean(arr,x,y);
    double sum=0;
    double** l=linear_regression(arr,x,y);
    double yt1[y];
    for(int i=0;i<y;i++)
        yt1[i]=0;
    for(int i=0;i<y;i++){
        for(int j=0;j<x-1;j++){
            yt1[i]+=((*(*(l+j)))*(*(*(arr+j)+i)));
        }
        yt1[i]+=*(*(l+x-1));
    }
    for(int i=0;i<y;i++)
        sum+=pow(yt1[i]-*(mean_arr+x-1),2);
    free(mean_arr);
    return sum;
}
double sum_of_squares_of_deviations(double** arr,int x,int y){
    double* l=stepwise_regression(arr,x,y,2,2);
    double yt1[y];
    double sum=0;
    for(int i=0;i<y;i++)
        yt1[i]=0;
    for(int i=0;i<y;i++){
        for(int j=0;j<x-1;j++){
            yt1[i]+=((*(l+j))*(*(*(arr+j)+i)));
        }
        yt1[i]+=*(l+x-1);
    }
    for(int i=0;i<y;i++)
        sum+=pow(*(*(arr+x-1)+i)-yt1[i],2);
    return sum;
}
double** multiple_matrix(double** mat1,int m,int p,double** mat2,int p1,int n){
    double sum=0;
    double** result=(double**)malloc(sizeof(double*)*m);
    for(int i=0;i<m;i++)
        *(result+i)=(double*)malloc(sizeof(double)*n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<p;k++){
                sum+=(*(*(mat1+i)+k))*(*(*(mat2+k)+j));
            }
                *(*(result+i)+j)+=sum;
                sum=0;
        }
    }
    return result;
}
double** linear_regression(double** arr,int x,int y){
    double** correlation_arr=correlation(arr,x,y);
    double** cov_arr,**tmp;
    double* mean_arr;
    double sum=0;
    double** solve_arr=solve(correlation_arr,x-1,x);
    double** solve_arr1=(double**)malloc(sizeof(double*)*(x-1));
    double** result=(double**)malloc(sizeof(double)*x);
    for(int i=0;i<x-1;i++)
        *(solve_arr1+i)=(double*)malloc(sizeof(double)*1);
    for(int i=0;i<x;i++)
        *(result+i)=(double*)malloc(sizeof(double)*1);
    for(int i=0;i<x-1;i++)
        *(*(solve_arr1+i))=*(*(solve_arr+i)+x-1);
    tmp=multiple_matrix(solve_arr,x-1,x-1,solve_arr1,x-1,1);
    cov_arr=cov(arr,x,y);
    for(int i=0;i<x-1;i++)
        *(*(tmp+i))*=pow((*(*(cov_arr+x-1)+x-1)*(y-1))/(*(*(cov_arr+i)+i)*(y-1)),0.5);
    mean_arr=mean(arr,x,y);
    for(int i=0;i<x-1;i++){
        *(*(result+i))=*(*(tmp+i));
        sum+=((*(*(tmp+i)))*(*(mean_arr+i)));
    }
    *(*(result+x-1))=*(mean_arr+x-1)-sum;
    for(int i=0;i<x;i++)
        free(*(correlation_arr+i));
    for(int i=0;i<x-1;i++){
        free(*(tmp+i));
        free(*(solve_arr+i));
        free(*(solve_arr1+i));
    }
    free(correlation_arr);
    free(solve_arr);
    free(solve_arr1);
    free(tmp);
    return result;
}
double** transpose(double** arr,int x,int y){
    double** result=(double**)malloc(sizeof(double*)*y);
    for(int i=0;i<y;i++)
        *(result+i)=(double*)malloc(sizeof(double)*x);
    for(int i=0;i<x;i++)
        for(int j=0;i<y;j++)
            *(*(result+j)+i)=*(*(arr+i)+j);
    return result;
}
double** solve(double** arr,int x,int y){
    double tmp_arr[x][y];
    double** result=(double**)malloc(sizeof(double*)*x);
    for(int i=0;i<x;i++){
        *(result+i)=(double*)malloc(sizeof(double)*y);
        for(int j=0;j<y;j++){
            tmp_arr[i][j]=*(*(arr+i)+j);
        }
    }
    for(int k=0;k<x;k++){
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(i==k&&j==k)
                    *(*(result+i)+j)=1/tmp_arr[k][k];
                else if(i!=k&&j==k)
                    *(*(result+i)+j)=(-1)*tmp_arr[i][k]/tmp_arr[k][k];
                else if(i==k&&j!=k)
                    *(*(result+i)+j)=tmp_arr[k][j]/tmp_arr[k][k];
                else
                    *(*(result+i)+j)=tmp_arr[i][j]-tmp_arr[i][k]*tmp_arr[k][j]/tmp_arr[k][k];
            }
        }
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                tmp_arr[i][j]=*(*(result+i)+j);
            }
        }
    }
    return result;
}
