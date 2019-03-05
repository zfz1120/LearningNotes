/**
*@brief Description: 归并排序算法的实现函数
*@  File:MergeSort.c
*@Author:LiBing
*@  Date:2019/02/24
*@  note:     
*@warning: 
*/

#include <stdlib.h>
#define MALLOC_ERR        1  //动态分配内存失败
/**
*@brief Description:合并两个排好序（从小到大）的子数组，合并过程中并排好序（从小到大）.
*@param[in][out]		A		数组A，存放合并前的子数组元素，以及合并后排好序的元素.
*@param[in]				p		第一个子数组L的起始元素在A中的下标.
*@param[in]				q		第一个子数组L的结束元素在A中的下标.
*@param[in]				r		第二个子数组R的结束元素在A中的下标
*@return：0：成功，非零失败.
*@retval				0		成功
*@retval				1		动态分配内存失败
*@note:输入时两个子数组是紧挨着存放在数组A中，A中可能还有其他元素，即A=[...,L,R,...];
*@warning:
*/
int Merge(double *A, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	double *L = (double *)malloc(n1 * sizeof(double));
	if (L==NULL)
	{
		return MALLOC_ERR;
	}
	double *R = (double *)malloc(n2 * sizeof(double));
	if (R == NULL)
	{
		return MALLOC_ERR;
	}
	int i = 0;
	int j = 0;
	int k = 0;
	//分解A为L，R
	for (i=0;i<n1;i++)
	{
		L[i] = A[p + i ];
	}
	for (j=0;j<n2;j++)
	{
		R[j] = A[q + j + 1];
	}
	i = 0;
	j = 0;
	//合并L,R
	for (k = p; k < r + 1; k++)
	{
		if (i<n1&&j<n2)//L和R均未遍历完才需要比较
		{
			if (L[i] <= R[j])
			{
				A[k] = L[i];
				i = i + 1;
			}
			else
			{
				A[k] = R[j];
				j = j + 1;
			}
		}
		else
		{
			//无需比较，直接拷贝剩余的元素
			if (i<n1)
			{
				A[k] = L[i];
				i = i + 1;
			}
			if (j < n2)
			{
				A[k] = R[j];
				j = j + 1;
			}
		}
	}
	free(L);
	free(R);
	return 0;
}

/**
*@brief Description:采用归并排序算法对数组A中第p个元素到第r个的元素进行排序（从小到大）.
*@param[in][out]		A		数组A，存放排序前的元素，以及排序后的元素.
*@param[in]				p		起始元素在A中的下标.
*@param[in]				r		结束元素在A中的下标.
*@return：0：成功，非零失败.
*@retval				0		成功
*@retval				1		动态分配内存失败
*@note:输入时两个子数组是紧挨着存放在数组A中，A中可能还有其他元素，即A=[...,L,R,...];
*@warning:
*/
int MergeSort(double *A, int p, int r)
{
	int ret = 0;
	if (p<r)//需要排序的元素个数大于1才需要进行排序操作
	{
		int q = (int)((p + r) / 2);
		//归并排序
		ret=MergeSort(A, p, q);
		if (ret)
		{
			return ret;
		}
		ret=MergeSort(A, q + 1, r);
		if (ret)
		{
			return ret;
		}
		//合并两个排好序的子序列
		ret=Merge(A, p, q, r);
		if (ret)
		{
			return ret;
		}
	}
	return 0;
}