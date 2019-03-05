/**
*@brief Description: ≤‚ ‘À„∑®µƒ¿˝≥Ã
*@  File:Test_GrublersFormula.cpp
*@Author:LiBing
*@  Date:2019/03/01
*@  note:     
*@warning: 
*/
#include <stdio.h>
#include "AlgorithmModule.h"

int main()
{
	int N = 8;
	int m = 3;
	int J = 9;
	int f[9] = {1,1,1,1,1,1,1,1,1};
	int dof = GrublersFormula(m, N, J, f);
	printf("dof=%d\n",dof);
	return 0;
}