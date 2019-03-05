/**
*@brief Description: 
*@  File:MergeSort.h
*@Author:LiBing
*@  Date:2019/02/24
*@  note:     
*@warning: 
*/


#ifndef MERGESORT_H_
#define MERGESORT_H_
#ifdef __cplusplus
extern "C" {
#endif
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
	int Merge(double *A, int p, int q, int r);


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
	int MergeSort(double *A, int p, int r);


#ifdef __cplusplus
}
#endif 
#endif//MERGESORT_H_