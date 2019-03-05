/**
*@brief Description: 动态规划法求解钢条切割问题
*@  File:CutMod.c
*@Author:LiBing
*@  Date:2019/02/28
*@  note:     
*@warning: 
*/
#include <stdlib.h>
#include <math.h>
//错误返回值定义
#define MALLOC_ERR		 1   


double MemoizedCutRodAux(double *p, int n, double *r)
{
	double q = 0;
	int i;
	if (r[n] >= 0)
		return r[n];
	if (n == 0)
		q = 0;
	else
	{
		q = INT_MIN;
		for (i = 1; i <= n; i++)
		{
			q = fmax(q, p[i] + MemoizedCutRodAux(p, n - i, r));
		}
	}
	r[n] = q;
	return q;
}

/**
*@brief Description:
*@param[in]		name
*@param[out]	name
*@note:
*@waring:
*/
int  MemoizedCutRod(double *p,int n,double *q)
{
	double *ri = (double *)malloc((n+1) * sizeof(double));
	if (ri==NULL)
	{
		return MALLOC_ERR;
	}
	int i;
	for (i=0;i<=n;i++)
	{
		ri[i] = INT_MIN;
	}
	*q= MemoizedCutRodAux(p, n, ri);
	free(ri);
	return 0;
}

int BottomUpCutRod(double *p, int n,double *rn,int *s)
{
	double *r = (double *)malloc((n+1) * sizeof(double));
	r[0] = 0;
	double q = 0;
	int i;
	int j;
	for (j = 1; j <= n; j++)
	{
		q = INT_MIN;
		for (i=1;i<=j;i++)
		{
			if (q<p[i-1]+r[j-i])
			{
				q = p[i-1] + r[j - i];
				s[j] = i;			
			}
		}
		r[j] = q;
	}
	*rn = r[n];
	return 0;
}

