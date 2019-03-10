/**
*@brief Description: Test demos of software.
*@  File:TestDemo.c
*@Author:LiBing
*@  Date:2019/03/01
*@  note:     
*@warning: 
*/
#include <stdio.h>
#include <math.h>
#include "RobotAlgorithmModule.h"

void test_GrublersFormula();
void test_RotInv();
void test_VecToso3();
void test_so3ToVec();
void test_AxisAng3();
void test_MatrixExp3();
void test_MatrixLog3();
void test_RpToTrans();
void test_TransToRp();
void test_TransInv();
void test_VecTose3();
void test_se3ToVec();
void test_Adjoint();
void test_AxisAng6();
void test_MatrixExp6();
void test_MatrixLog6();
int main()
{
	test_MatrixExp3();
	return 0;
}

void test_GrublersFormula()
{
	int N = 8;
	int m = 3;
	int J = 9;
	int f[9] = { 1,1,1,1,1,1,1,1,1 };
	int dof = GrublersFormula(m, N, J, f);
	printf("dof=%d\n", dof);
}

void test_RotInv()
{
	double R[3][3] =
	{
		0,0,1,
		1,0,0,
		0,1,0
	};
	double InvR[3][3] = { {0} };
	RotInv(R, InvR);
	int i;
	printf("R:\n");
	for (i = 0; i < 3; i++)
	{
		printf("%lf %lf %lf\n", R[i][0], R[i][1], R[i][2]);
	}
	printf("InvR:\n");
	for (i=0;i<3;i++)
	{
		printf("%lf %lf %lf\n", InvR[i][0], InvR[i][1], InvR[i][2]);
	}
}

void test_VecToso3()
{
	double omg[3] = {1,2,3};
	double so3[3][3] = { {0} };
	int i;
	VecToso3(omg, so3);
	printf("omg:\n");

	printf("%lf %lf %lf\n", omg[0], omg[1], omg[2]);

	printf("so3:\n");
	for (i = 0; i < 3; i++)
	{
		printf("%lf %lf %lf\n", so3[i][0], so3[i][1], so3[i][2]);
	}
}

void test_so3ToVec()
{
	double so3[3][3] = 
	{
		0, -3, 2,
		3, 0, -1,
		-2, 1, 0
	};
	double omg[3] = { 0 }; 
	int i;
	so3ToVec(so3, omg);

	printf("so3:\n");
	for (i = 0; i < 3; i++)
	{
		printf("%lf %lf %lf\n", so3[i][0], so3[i][1], so3[i][2]);
	}
	printf("omg:\n");
	printf("%lf %lf %lf\n", omg[0], omg[1], omg[2]);

}

void test_AxisAng3()
{
	double expc3[3] = { 1,2,3 };
	double omghat[3] = { 0 };
	double theta = 0;
	int ret = AxisAng3(expc3, omghat, &theta);
	if (ret)
	{
		printf("AxisAng3 error,norm of exp3 is 0\n");
		return ;
	}

	printf("expc3:\n");
	printf("%lf %lf %lf\n", expc3[0], expc3[1], expc3[2]);
	printf("omg:\n");
	printf("%lf %lf %lf\n", omghat[0], omghat[1], omghat[2]);
	printf("theta:\n");
	printf("%lf\n", theta);
	return;
}


void test_MatrixExp3()
{
	double so3mat[3][3] = 
	{
		0, -3, 2,
		3, 0, -1,
		-2, 1, 0 
	};
	double R[3][3] = {{ 0 }};
	MatrixExp3(so3mat, R);
	printf("R:\n");
	int i;
	for (i = 0; i < 3; i++)
	{
		printf("%lf %lf %lf\n", R[i][0], R[i][1], R[i][2]);
	}

	return;
}


void test_MatrixLog3()
{
	double theta = 30 * PI / 180;
	double R[3][3] =
	{
		0, 0, 1,
		1, 0, 0,
		0, 1, 0
	};
	double so3Mat[3][3] = { 0 };
	MatrixLog3(R, so3Mat);
	printf("so3Mat:\n");
	int i;
	for (i = 0; i < 3; i++)
	{
		printf("%lf %lf %lf\n", so3Mat[i][0], so3Mat[i][1], so3Mat[i][2]);
	}
	return;
}

void test_RpToTrans()
{
	double R[3][3] =
	{
		1,0,0,
		0,0,-1,
		0,1,0
	};
	double p[3] = { 1,2,5 };
	double T[4][4] = { {0} };
	RpToTrans(R, p, T);
	printf("T:\n");
	int i;
	for (i = 0; i < 4; i++)
	{
		printf("%lf %lf %lf %lf\n", T[i][0], T[i][1], T[i][2], T[i][3]);
	}
	return;
}

void test_TransToRp()
{
	double T[4][4] = {
		1, 0, 0, 0,
		0, 0, -1, 0,
		0, 1, 0, 3,
		0, 0, 0, 1
	};
	double R[3][3] = { {0} };
	double p[3] = { 0 };
	TransToRp(T, R, p);
	printf("R:\n");
	int i;
	for (i = 0; i < 3; i++)
	{
		printf("%lf %lf %lf\n", R[i][0], R[i][1], R[i][2]);
	}
	printf("p:\n");
	printf("%lf %lf %lf\n", p[0],p[1],p[2]);
	return;

}

void test_TransInv()
{
	double T[4][4] = {
		1, 0, 0, 0,
		0, 0, -1, 0,
		0, 1, 0, 3,
		0, 0, 0, 1	
	};
	double InvT[4][4];
	TransInv(T, InvT);
	printf("InvT:\n");
	int i;
	for (i = 0; i < 4; i++)
	{
		printf("%lf %lf %lf %lf\n", InvT[i][0], InvT[i][1], InvT[i][2], InvT[i][3]);
	}
	return;
}

void test_VecTose3()
{
	double V[6] = { 1,2,3,4,5,6 };
	double se3Mat[4][4];
	VecTose3(V, se3Mat);
	printf("se3Mat:\n");
	int i;
	for (i = 0; i < 4; i++)
	{
		printf("%lf %lf %lf %lf\n", se3Mat[i][0], se3Mat[i][1], se3Mat[i][2], se3Mat[i][3]);
	}
	return;
}


void test_se3ToVec()
{
	double V[6] = { 0 };
	double se3Mat[4][4] = {
		0, -3, 2, 4,
		3, 0, -1, 5,
		-2, 1, 0, 6,
		0, 0, 0, 0
	};
	se3ToVec(se3Mat, V);
	int i;
	printf("V:\n");
	for (i=0;i<6;i++)
	{
		printf("%lf\n", V[i]);
	}
	return;
}


void test_Adjoint()
{
	double T[4][4] = {
		1, 0, 0, 0,
		0, 0, -1, 0,
		0, 1, 0, 3,
		0, 0, 0, 1
	};
	double AdT[6][6] = { {0} };
	Adjoint(T, AdT);
	int i;
	int j;
	printf("AdT:\n");
	for (i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			printf("%lf  ", AdT[i][j]);
		}
		printf("\n");
	}

	return;
}

void test_AxisAng6()
{
	double expc6[6] = { 0, 0, 0, 0, 0, 0 };
	double S[6];
	double theta;
	int ret = AxisAng6(expc6, S, &theta);
	if (ret)
	{
		printf("failure:the input expc6 is a zero vector \n ");
		return;
	}
	printf("S:\n");
	int i;
	for (i = 0; i < 6; i++)
	{
		printf("%lf\n", S[i]);
	}
	printf("theta:\n");
	printf("%lf\n", theta);
	return;
}


void test_MatrixExp6()
{
	double se3Mat[4][4] =
	{
		0, 0, 0, 0,
		0, 0, -1.570796, 2.3562,
		0, 1.570796, 0, 2.3562,
		0, 0, 0, 0
	};
	double T[4][4];
	MatrixExp6(se3Mat, T);
	int i;
	printf("T:\n");
	for (i = 0; i < 4; i++)
	{
		printf("%lf %lf %lf %lf\n", T[i][0], T[i][1], T[i][2], T[i][3]);
	}
	return;
}


void test_MatrixLog6()
{
	double T[4][4] =
	{
		1, 0, 0, 0,
		0, 0, -1, 0,
		0, 1, 0, 3,
		0, 0, 0, 1
	};
	double se3mat[4][4];
	MatrixLog6(T, se3mat);
	int i;
	printf("se3mat:\n");
	for (i = 0; i < 4; i++)
	{
		printf("%lf %lf %lf %lf\n", se3mat[i][0], se3mat[i][1], se3mat[i][2], se3mat[i][3]);
	}

	return;
}