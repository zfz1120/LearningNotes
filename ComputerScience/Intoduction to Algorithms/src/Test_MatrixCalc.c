/**
*@brief Description: ≤‚ ‘æÿ’Û‘ÀÀ„∫Ø ˝
*@  File:Test_MatrixCalc.c
*@Author:LiBing
*@  Date:2019/02/26
*@  note:     
*@warning: 
*/
#include <stdio.h>
#include "MatrixCalc.h"
int main()
{
	double A[2][3] = { 1,2,3,
					4,5,6, };
	double B[3][4] = { 1,2,3,4,
					5,6,7,8,
					9,10,11,12 };
	double C[2][4] = { {0} };
	MatrixMultply(A, 2, 3, B, 4, C);
	return 0;

}