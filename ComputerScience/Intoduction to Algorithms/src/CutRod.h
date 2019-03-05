/**
*@brief Description: 动态规划法求解钢条切割最优方案
*@  File:CutRod.h
*@Author:LiBing
*@  Date:2019/02/28
*@  note:     
*@warning: 
*/

#ifndef CUTROD_H_
#define CUTROD_H_
#ifdef __cplusplus
extern "C" {
#endif
	int  MemoizedCutRod(double *p, int n, double *r);
	int BottomUpCutRod(double *p, int n, double *r, int *s);



#ifdef __cplusplus
}
#endif
#endif