/**
*@brief Description: 
*@  File:GetMaximumSubarray.h
*@Author:LiBing
*@  Date:2019/02/24
*@  note:     
*@warning: 
*/
#ifndef FINDMAXSUBARRAY_H_
#define FINDMAXSUBARRAY_H_
#ifdef __cplusplus
extern "C" {
#endif
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
	int FindMaxSubarray(double *A, int low, int high, double *MaxSum, int *SubLow, int *SubHigh);

#ifdef __cplusplus
}
#endif
#endif//FINDMAXSUBARRAY_H_