/**
*@brief Description: 
*@  File:GetMaximumSubarray.c
*@Author:LiBing
*@  Date:2019/02/24
*@  note:     
*@warning: 
*/
#include <limits.h>

#define INDEX_ERR	1  //输入索引错误，输入的High小于low.
/**
*@brief Description:寻找跨越数组A中间点（A[low...mid]和A[mid+1...high]）的最大子数组.
*@param[in]		A			输入数组.
*@param[in]		low			起始元素的下标.
*@param[in]		high		末尾元素的下标.
*@param[in]		mid			中间点的元素（左侧数组的末尾元素）的下标.
*@param[out]	CrossSum	最大子数组的所有元素之和.
*@param[out]	CrossLow	子数组起始元素的下标.
*@param[out]	CrossHigh	子数组末尾元素的下标.
*@note:			
*@waring:
*/
int FindMaxCrossingSubarray(double *A, int low, int mid, int high, double *CrossSum, int *CrossLow, int *CrossHigh)
{
	double LeftSum = INT_MIN;
	double RightSum = INT_MIN;
	double sum = A[mid];
	int i = 0;
	int MaxLeft = mid;
	int MaxRight = mid+1;
	for (i=mid;i>=low;i--)
	{
		sum = sum + A[i];
		if (sum>LeftSum)
		{
			LeftSum = sum;
			MaxLeft = i;
		}
	}
	sum = 0;
	for (i=mid+1;i<=high;i++)
	{
		sum = sum + A[i];
		if (sum>RightSum)
		{
			RightSum = sum;
			MaxRight = i;
		}
	}
	*CrossSum = LeftSum + RightSum;
	*CrossLow = MaxLeft;
	*CrossHigh = MaxRight;
	return 0;
}

/**
*@brief Description:寻找数组A（或指定A中连续元素构成的数组）和最大的非空连续子数组.
*@param[in]		A		输入数组.
*@param[in]		low		起始元素的下标.
*@param[in]		high	末尾元素的下标.
*@param[out]	MaxSum	最大子数组的所有元素之和.
*@param[out]	SubLow	子数组起始元素的下标.
*@param[out]	SubHigh	子数组末尾元素的下标.
*@return		返回0执行成功，返回非零执行失败.
*@retval		0	执行成功
*@retval		1	输入索引错误，输入的High小于low.
*@note:			这里输入指定数组的下标p,q,使得该算法可以寻找A中某部分连续元素构成的数组的最大子数组，
*				当要寻找整个数组A的最大子数组时，p=0,r为A中末尾元素的下标.
*@waring:
*/
int FindMaxSubarray(double *A, int low, int high, double *MaxSum, int *SubLow, int *SubHigh)
{
	int mid = 0;
	int LeftLow;
	int LeftHigh;
	int RightLow;
	int RightHigh;
	int CrossLow;
	int CrossHigh;
	double LeftSum;
	double RightSum;
	double CrossSum;
	int ret = 0;
	if (high<low)//输入索引错误
	{
		return INDEX_ERR;
	}
	if (high==low)//只有一个元素
	{
		*MaxSum = A[low];
		*SubLow = low;
		*SubHigh = low;
	}
	else
	{
		//分解子问题
		mid = (int)((low + high) / 2);
		//寻找中间点左侧的最大子数组
		ret=FindMaxSubarray(A, low, mid, &LeftSum, &LeftLow, &LeftHigh);
		if (ret)
		{
			return ret;
		}
		//寻找中间点右侧的最大子数组
		ret = FindMaxSubarray(A, mid+1, high, &RightSum, &RightLow, &RightHigh);
		if (ret)
		{
			return ret;
		}
		//寻找跨越中间点的最大子数组
		ret = FindMaxCrossingSubarray(A, low, mid, high, &CrossSum, &CrossLow, &CrossHigh);
		if (ret)
		{
			return ret;
		}
		//子问题的解合成原问题的解
		if (LeftSum>=RightSum && LeftSum>=CrossSum)
		{
			*MaxSum = LeftSum;
			*SubLow = LeftLow;
			*SubHigh = LeftHigh;
		}
		else if (RightSum>=LeftSum && RightSum>=CrossSum)
		{
			*MaxSum = RightSum;
			*SubLow = RightLow;
			*SubHigh = RightHigh;
		}
		else
		{
			*MaxSum = CrossSum;
			*SubLow = CrossLow;
			*SubHigh = CrossHigh;
		}
	}
	return 0;
}