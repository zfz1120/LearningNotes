/**
*@brief Description: 机器人学的算法模块的函数实现.
*@  File:AlgorithmModule.c
*@Author:LiBing
*@  Date:2019/03/01
*@  note:     
*@warning: 
*/

/**
*@brief Description:使用GrublersFormula公式计算机构的自由度.
*@param[in]		N		连杆的数目（包括大地）.
*@param[in]		m		连杆(刚体)的自由度（平面刚体m=3,空间刚体m=6）.
*@param[in]		J		关节的数量.
*@param[in]		f		数组，每个关节的自由度.
*@return				返回输入该机构的自由度.
*@note:					各个关节的约束是独立的才能使用该函数计算机构的自由度.
*@waring:
*/
int GrublersFormula(int m, int N, int J, int *f)
{
	int i;
	int dof;
	int c = 0;
	for (i=1;i<=J;i++)
	{
		//计算自由度的约束
		c = c + f[i-1];
	}
	dof = m*(N - 1 - J) + c;
	return dof;
}

