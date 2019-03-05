/**
*@brief Description: ¾ØÕóÔËËãµÄº¯Êı
*@  File:F:MatrixCalc.c
*@Author:LiBing
*@  Date:2019/02/26
*@  note:     
*@warning: 
*/

#include "MatrixCalc.h"

int MatrixMultply(double A[][3],int ARow,int AColumn, double B[][4],int BColumn,double C[][4] )
{
	int i;
	int j;
	int k;
	for (i=0;i<ARow;i++)
	{
		for (j=0;j<BColumn;j++)
		{
			C[i][j] = 0.0;
			for (k=0;k<AColumn;k++)
			{
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}

	}
	return 0;
}