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
