# 机器人运动学之刚体运动算法（C语言）

![刚体运动](image\刚体运动.gif)

##摘要

在上一篇博客[ 刚体运动的矩阵表示和指数坐标表示](https://blog.csdn.net/libing403/article/details/88322800)总结了刚体运动的矩阵表示和指数坐标表示，介绍了它们之间的联系和相互转换的。这些算法在教材《 Modern Robotics Mechanics,Planning , and Control》给出了Matlab和python语言的实现。我在这里再给出这些算法的C语言实现。**欢迎反馈存在的bug。**

##头文件

提供的算法函数包括如下头文件AlgorithmModule.h声明的函数。

```c
/**
 * @brief			Description: Algorithm module of robotics, according to the
 *					book[modern robotics : mechanics, planning, and control].
 * @file:			RobotAlgorithmModule.h
 * @author:			LiBing
 * @date:			2019/03/01 12:50
 * Copyright(c) 	2019 LiBing. All rights reserved. 
 *					https://blog.csdn.net/libing403                               
 * 					 
 * Contact 			1540845930@qq.com
 * @note:     
 * @warning: 		
*/
#ifndef RobotALGORITHMMODULE_H_
#define RobotALGORITHMMODULE_H_
#ifdef __cplusplus
extern "C" {
#endif
	#define		PI					3.14159265358979323846
	//if the norm of vector is near zero(< 1.0E-6),regard as zero.
	#define		ZERO_VALUE			1.0E-6		
	//number of joints,be used when Compute the Jacobian.	

	/**
	*@brief			Description:use GrublersFormula calculate The number of degrees of
	*				freedom of a mechanism with links and joints.
	*@param[in]		N		the number of links( including the ground ).
	*@param[in]		m		the number of degrees of freedom of a rigid body
	*						(m = 3 for planar mechanisms and m = 6 for spatial mechanisms).
	*@param[in]		J		the number of joints.
	*@param[in]		f		the number of freedoms provided by each joint..
	*@return				The number of degrees of freedom of a mechanism
	*@note:					This formula holds only if all joint constraints are independent.
	*						If they are not independent then the formula provides a lower
	*						bound on the number of degrees of freedom.
	*@waring:
	*/
	int GrublersFormula(int m, int N,  int J, int *f);

	/**
	*@brief			Computes the inverse of the rotation matrix R.
	*@param[in]		R		rotation matrix .
	*@param[out]	InvR	inverse matrix of R.
	*@note					Input R must be a 3x3 rotation matrix.
	*/
	void RotInv(double R[3][3], double InvR[3][3]);

	/**
	*@brief			Description:Returns the 3 x 3 skew-symmetric matrix corresponding to omg.
	*@param[in]		omg		a unit 3-vector.
	*@param[out]	so3Mat	the 3 x 3 skew-symmetric matrix corresponding to omg.
	*@note:
	*@waring:
	*/
	void VecToso3(double omg[3], double so3Mat[3][3]);

	/**
	*@brief			Description:Returns the 3-vector corresponding to the 3×3 skew-symmetric matrix so3mat.
	*@param[in]		so3Mat		the 3×3 skew-symmetric matrix so3mat. 
	*@param[out]	omg			the 3-vector.
	*@note:
	*@waring:
	*/
	void so3ToVec(double so3Mat[3][3], double omg[3]);

	/**
	*@brief			Description:Extracts  the unit rotation axis omghat and the corresponding rotation angle theta from
	*				exponential coordinates omghat*theta for rotation, expc3.
	*@param[in]		expc3
	*@param[out]	omghat		the unit vector of rotation axis .
	*@param[out]	theta		rotation angle.
	*@retval        0			success.
	*@retval		1			failure,normal of expc3 is zero or near zero(<1.0E-6).
	*@note:
	*@waring:
	*/
	void AxisAng3(double expc3[3], double omghat[3], double *theta);

	/**
	*@brief			Description:Computes the rotation matrix R in SO(3) corresponding to
	*				the matrix exponential of so3mat in so(3).
	*@param[in]		so3Mat		[omghat]*theta,matrix exponential of so3mat in so(3).
	*@param[out]	R			rotation matrix R in SO(3).
	*@note:
	*@waring:
	*/
	void MatrixExp3(double so3Mat[3][3], double R[3][3]);

	/**
	*@brief			Description:Computes the matrix logarithm so3mat in so(3) of the rotation matrix R in SO(3).
	*@param[in]		R		the rotation matrix
	*@param[out]	so3Mat	matrix logarithm
	*@note:
	*@waring:
	*/
	void MatrixLog3(double R[3][3], double so3Mat[3][3]);

	/**
	*@brief			Description:Builds the homogeneous transformation matrix T corresponding to a rotation
	*				matrix R in SO(3) and a position vector p in R3.
	*@param[in]		R		a rotation matrix R in SO(3).
	*@param[in]		p		a position vector p in R3.
	*@param[out]	T		the homogeneous transformation matrix T.
	*@note:
	*@waring:
	*/
	void RpToTrans(double R[3][3], double p[3], double T[4][4]);

	/**
	*@brief			Description: Extracts the rotation matrix R and position vector p
	*				from a homogeneous transformation matrix T.
	*@param[in]		T		a homogeneous transformation matrix.
	*@param[out]	R		the rotation matrix.
	*@param[out]	p		position vector.
	*@note:
	*@waring:
	*/
	void TransToRp(double T[4][4], double R[3][3], double p[3]);

	/**
	*@brief			Description:Computes the inverse of a homogeneous transformation matrix T.
	*@param[in]		T		a homogeneous transformation matrix.
	*@param[out]	InvT	the inverse of T.
	*@note:
	*@waring:
	*/
	void TransInv(double T[4][4], double InvT[4][4]);

	/**
	*@brief			Description:Computes the se(3) matrix corresponding to a 6 - vector twist V.
	*@param[in]		V		a 6 - vector twist V.
	*@param[out]	se3Mat	the se(3) matrix.
	*@note:
	*@waring:
	*/
	void VecTose3(double V[6], double se3Mat[4][4]);

	/**
	*@brief			Description:Computes the 6-vector twist corresponding to an se(3) matrix se3mat.
	*@param[in]		se3Mat			an se(3) matrix.
	*@param[out]	V				he 6-vector twist.
	*@note:
	*@waring:
	*/
	void se3ToVec(double se3Mat[4][4], double V[6]);

	/**
	*@brief			Description:Computes the 6 × 6 adjoint representation [AdT ] of the homogeneous transformation matrix T.
	*@param[in]		T		a homogeneous transformation matrix.
	*@param[out]	AdT		the 6 × 6 adjoint representation [AdT ].
	*@note:
	*@waring:
	*/
	void Adjoint(double T[4][4], double AdT[6][6]);

	/**
	*@brief			Description: Extracts the normalized screw axis S and the distance traveled along the screw
	*				theta from the 6-vector of exponential coordinates S*theta.
	*@param[in]		expc6		the 6-vector of exponential coordinates.
	*@param[out]	S			the normalized screw axis.
	*@param[out]	theta		the distance traveled along the screw.
	*@retval		0			success;
	*@retval		1			failure,because the input expc6 is a zero vector
	*@note:
	*@waring:
	*/
	void AxisAng6(double expc6[6], double S[6], double *theta);

	/**
	*@brief			Description: Computes the homogeneous transformation matrix T in SE(3) corresponding to
	*				the matrix exponential of se3mat in se(3).
	*@param[in]		se3mat			the matrix exponential of se3mat in se(3).
	*@param[out]	T				the homogeneous transformation matrix T in SE(3).
	*@note:
	*@waring:
	*/
	void MatrixExp6(double se3Mat[4][4], double T[4][4]);

	/**
	*@brief			Description: Computes the matrix logarithm se3mat in se(3) of
	*				the homogeneous transformation matrix T in SE(3)
	*@param[in]		T			the homogeneous transformation matrix.
	*@param[out]	se3Mat		the matrix logarithm of T.
	*@note:
	*@waring:
	*/
	void MatrixLog6(double T[4][4], double se3Mat[4][4]);
```

##实现文件

以上函数的在如下的文件RobotAlgorithmModule.c中实现

```c
/**
 * @brief			Description: Algorithm module of robotics, according to the
 *					book[modern robotics : mechanics, planning, and control].
 * @file:			RobotAlgorithmModule.c
 * @author:			LiBing
 * @date:			2019/03/01 12:23
 * Copyright(c) 	2019 LiBing. All rights reserved. 
 *					https://blog.csdn.net/libing403                               				 
 * Contact 			1540845930@qq.com
 * @note:     
 * @warning: 		
*/

#include "RobotAlgorithmModule.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
*@brief Description:use GrublersFormula calculate The number of degrees of 
freedom of a mechanism with links and joints.
*@param[in]		N		the number of links( including the ground ).
*@param[in]		m		the number of degrees of freedom of a rigid body
*						(m = 3 for planar mechanisms and m = 6 for spatial mechanisms).
*@param[in]		J		the number of joints.
*@param[in]		f		the number of freedoms provided by each joint..
*@return				The number of degrees of freedom of a mechanism
*@note:					This formula holds only if all joint constraints are independent.
*						If they are not independent then the formula provides a lower 
*						bound on the number of degrees of freedom.
*@waring:
*/
int GrublersFormula(int m, int N, int J, int *f)
{
	int i;
	int dof;
	int c = 0;
	for (i=1;i<=J;i++)
	{
		c = c + f[i-1];
	}
	dof = m*(N - 1 - J) + c;
	return dof;
}

/**
*@brief Description: Make  matrix b equal to  matrix a.
*@param[in]			a		a 3 x 3  matrix.
*@param[out]		b		result,b=a.
*@return		No return value.
*@note:
*@waring:
*/
void Matrix3Equal(double a[][3], double b[][3])
{
	int i;
	int j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			b[i][j] = a[i][j];
		}
	}
	return;
}

/**
*@brief Description: Make  matrix b equal to  matrix a.
*@param[in]			a		a 4 x 4  matrix.
*@param[out]		b		result,b=a.
*@return		No return value.
*@note:
*@waring:
*/
void Matrix4Equal(double a[][4], double b[][4])
{
	int i;
	int j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			b[i][j] = a[i][j];
		}
	}
	return;
}


/**
*@brief Description:Calculate a 3 x 3  matrix add a 3 x 3  matrix.
*@param[in]		a		a 3 x 3  matrix.
*@param[in]		b		a 3 x 3  matrix.
*@param[out]	c		result of a+b.
*@return		No return value.
*@note:
*@waring:
*/
void Matrix3Add(double a[][3], double b[][3], double c[][3])
{
	int i;
	int j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return;
}

/**
*@brief Description:Calculate a 3 x 3  matrix Subtract a 3 x 3  matrix.
*@param[in]		a		a 3 x 3  matrix.
*@param[in]		b		a 3 x 3  matrix.
*@param[out]	c		result of a-b.
*@return		No return value.
*@note:
*@waring:
*/
void Matrix3Sub(double a[][3], double b[][3], double c[][3])
{
	int i;
	int j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			c[i][j] = a[i][j] - b[i][j];
		}
	}
	return;
}

/**
*@brief Description: Calculate two 3 x 3  matrix multiplication. 
*@param[in]		a		a 3 x 3  matrix.		
*@param[in]		b		a 3 x 3  matrix.	
*@param[out]	c		result of a*b.
*@return		No return value.
*@note:
*@waring:
*/
void Matrix3Mult(double a[][3],double b[][3],double c[][3])
{
	int i;
	int j;
	int k;
	for (i=0;i<3;i++)
	{		
		for (j=0;j<3;j++)
		{
			c[i][j] = 0.0;
			for (k=0;k<3;k++)
			{
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}

		}
	}
	return;
}

/**
*@brief Description: Calculate two 4 x 4  matrix multiplication.
*@param[in]		a		a 4 x 4  matrix.
*@param[in]		b		a 4 x 4  matrix.
*@param[out]	c		result of a*b.
*@return		No return value.
*@note:
*@waring:
*/
void Matrix4Mult(double a[][4], double b[][4], double c[][4])
{
	int i;
	int j;
	int k;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			c[i][j] = 0.0;
			for (k = 0; k < 4; k++)
			{
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}

		}
	}
	return;
}


/**
*@brief Description: Calculate  3 x 3  matrix multiply a value.
*@param[in]		a		a 3 x 3  matrix.
*@param[in]		Value	a scalar value.
*@param[out]	c		result of a*Value.
*@return		No return value.
*@note:
*@waring:
*/
void Matrix3MultValue(double a[][3], double Value, double c[][3])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			c[i][j] = a[i][j] * Value;
		}
	}
	return;
}

/**
*@brief Description: Calculate  4 x 4  matrix multiply a value.
*@param[in]		a		a 4 x 4  matrix.
*@param[in]		Value	a scalar value.
*@param[out]	c		result of a*Value.
*@return		No return value.
*@note:
*@waring:
*/
void Matrix4MultValue(double a[][4], double Value, double c[][4])
{
	int i;
	int j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			c[i][j] = a[i][j] * Value;
		}
	}
	return;
}


/**
*@brief Description:Computes the result of a 3 x 3 Matrix multiply a 3-vector.
*@param[in]		R			a 3 x 3 Matrix.
*@param[in]		vec1		an input of 3-vector.
*@param[out]	vec2		the output result of 3-vector.
*@return		No return value.
*@note:
*@waring:
*/
void Matrix3MultVec(double R[3][3], double vec1[3], double vec2[3])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		vec2[i] = 0;
		for (j=0;j<3;j++)
		{
			vec2[i] = vec2[i] + R[i][j] * vec1[j];
		}
	}
	return;
}

/**
*@brief Description:Computes a 3-vector add a 3-vector.
*@param[in]		vec1		a 3-vector.
*@param[in]		vec2		a 3-vector.
*@param[out]	vec3		result of vec1 + vec2;
*@return		No return value.
*@note:
*@waring:
*/
void Vec3Add(double vec1[3], double vec2[3], double vec3[3])
{
	vec3[0] = vec1[0] + vec2[0];
	vec3[1] = vec1[1] + vec2[1];
	vec3[2] = vec1[2] + vec2[2];
	return;
}


/**
*@brief Description:Computes result of two 3-vector cross product.
*@param[in]		vec1		a first 3-vector.
*@param[in]		vec2		a first 3-vector.
*@param[out]	vec3		result of vec1 cross product vec2.
*@return		No return value.
*@note:
*@waring:
*/
void Vec3Cross(double vec1[3],double vec2[3],double vec3[3])
{
	vec3[0] = vec1[1] * vec2[2] - vec2[1] * vec1[2];
	vec3[1] = -(vec1[0] * vec2[2] - vec2[0] * vec1[2]);
	vec3[2] = vec1[0] * vec2[1] - vec2[0] * vec1[1];
	return;
}

/**
*@brief Description:Computes a 3-vector multiply a scalar value.
*@param[in]		vec1			a 3-vector.
*@param[in]		value			a scalar value.
*@param[out]	vec2			result of vec1 * value. 
*@return		No return value.
*@note:
*@waring:
*/
void Vec3MultValue(double vec1[3], double value, double vec2[3])
{
	vec2[0] = vec1[0] * value;
	vec2[1] = vec1[1] * value;
	vec2[2] = vec1[2] * value;
	return;
}

/**
*@brief Description: Computes the norm of a 3-vector.
*@param[in]		vec			an input 3-vector.
*@retval		the norm of a an input 3-vector.
*@return		No return value.
*@note:
*@waring:
*/
double Vec3Norm(double vec[3])
{
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

/**
*@brief			Copy  matrix from a to  b .
*@param[in]		a		First matrix.
*@param[in]		m		rows of matrix a.
*@param[in]		n		columns of matrix a.
*@param[in]		b		Second matrix.
*@return		No return value.
*@note:
*@waring:
*/
void MatrixCopy(const double *a, int m, int n, double *b)
{
	memcpy(b, a, m*n * sizeof(double));
	return;
}

/**
*@brief			Computes Matrix transpose.
*@param[in]		a			a matrix.
*@param[in]		m			rows of matrix a.
*@param[in]		n			columns of matrix a.
*@param[out]	b			transpose of matrix a.
*@return		No return value.
*@note:
*@waring:
*/
void MatrixT(double *a, int m, int n, double *b)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			b[j*m + i] = a[i*n + j];
		}
	}
	return;
}



/**
*@brief			Computes matrix multiply.
*@param[in]		a		First matrix.
*@param[in]		m		rows of matrix a.
*@param[in]		n		columns of matrix b.
*@param[in]		b		Second matrix.
*@param[in]		l		columns of matrix b.
*@param[out]	c		result of a*b.
*@return		No return value.
*@note:
*@waring:
*/
void MatrixMult(const double *a, int m, int n, const double *b, int l, double *c)
{
	int i, j, k;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < l; j++)
		{
			c[i*l + j] = 0.0;
			for (k = 0; k < n; k++)
			{
				c[i*l + j] = c[i*l + j] + a[i*n + k] * b[k*l + j];
			}
		}
	}
	return;
}



/**
*@brief			Computes the inverse of the rotation matrix R.
*@param[in]		R		rotation matrix .
*@param[out]	InvR	inverse matrix of R.
*@return		No return value.
*@note					Input R must be a 3 x 3 rotation matrix.
*/
void RotInv(double R[3][3], double InvR[3][3])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			InvR[i][j] = R[j][i];
		}
	}
	return;
}

/**
*@brief Description:Returns the 3 x 3 skew-symmetric matrix corresponding to omg.
*@param[in]		omg		a 3-vector.
*@param[out]	so3Mat	the 3 x 3 skew-symmetric matrix corresponding to omg.
*@return		No return value.
*@note:
*@waring:
*/
void VecToso3(double omg[3],double so3Mat[3][3])
{
	so3Mat[0][0] = 0.0;		so3Mat[0][1] = -omg[2]; so3Mat[0][2] = omg[1];
	so3Mat[1][0] = omg[2];	so3Mat[1][1] = 0;		so3Mat[1][2] = -omg[0];
	so3Mat[2][0] = -omg[1];	so3Mat[2][1] = omg[0];	so3Mat[2][2] = 0.0;
	return;
}


/**
*@brief			Description:Returns the 3-vector corresponding to the 3 x 3 skew-symmetric matrix so3mat.
*@param[in]		so3Mat		a 3 x 3 skew-symmetric matrix so3mat.
*@param[out]	omg			the 3-vector.
*@return		No return value.
*@note:
*@waring:
*/
void so3ToVec(double so3Mat[3][3], double omg[3])
{
	omg[0] = so3Mat[2][1]; omg[1] = so3Mat[0][2]; omg[2] = so3Mat[1][0];
	return;
}


/**
*@brief			Description:Extracts  the unit rotation axis omghat and the corresponding
*				rotation angle theta from exponential coordinates omghat*theta for rotation, expc3.
*@param[in]		expc3			
*@param[out]	omghat		the unit vector of rotation axis .
*@param[out]	theta		rotation angle.
*@return		No return value.
*@note:
*@waring:
*/
void AxisAng3(double expc3[3],double omghat[3],double *theta)
{
	int i;
	int ret = 0;
	*theta = sqrt(expc3[0] * expc3[0] + expc3[1] * expc3[1] + expc3[2] * expc3[2]);
	if (*theta<ZERO_VALUE)
	{
		omghat[0] = 0.0;
		omghat[1] = 0.0;
		omghat[2] = 0.0;
		*theta = 0.0;
		return;
	}
	for (i=0;i<3;i++)
	{
		omghat[i]=expc3[i]/(*theta);
	}
	return ;
}

/**
*@brief			Description:Computes the rotation matrix R in SO(3) corresponding to
*				the matrix exponential of so3mat in so(3).
*@param[in]		so3Mat		[omghat]*theta,matrix exponential of so3mat in so(3).			
*@param[out]	R			rotation matrix R in SO(3).
*@return		No return value.
*@note:
*@waring:
*/
void MatrixExp3(double so3Mat[3][3],double R[3][3])
{
	double omgtheta[3];
	double omghat[3] = { 0 };
	double theta = 0;
	int ret = 0;
	int i;
	int j;
	double MatI3[3][3] =
	{
		1,0,0,
		0,1,0,
		0,0,1
	};
	so3ToVec(so3Mat, omgtheta);
	AxisAng3(omgtheta, omghat, &theta);
	if (theta<ZERO_VALUE)
	{
		Matrix3Equal(MatI3, R);
		return ;
	}
	else
	{

		//calculate formula(3.51) in book [modern robotics : mechanics,planning,and control]
		double omgmat[3][3];
		double temp[3][3];
		Matrix3MultValue(so3Mat, 1.0 / theta, omgmat);
		Matrix3Mult(omgmat, omgmat, temp);
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				R[i][j] = MatI3[i][j] + sin(theta)*so3Mat[i][j] / theta + (1 - cos(theta))*temp[i][j];
			}
		}
	}
	return;
}

/**
*@brief			Description:Computes the matrix logarithm so3mat in so(3) of the rotation matrix R in SO(3).
*@param[in]		R		the rotation matrix.
*@param[out]	so3Mat	matrix logarithm.
*@return		No return value.
*@note:
*@waring:
*/
void MatrixLog3(double R[3][3],double so3Mat[3][3])
{
	double omg[3] = { 0 };
	double acosinput = (R[0][0] + R[1][1] + R[2][2] - 1.0) / 2;
	if (acosinput > 1.0)
	{
		memset(so3Mat, 0, 9 * sizeof(double));
	}
	else if (acosinput<=-1.0)
	{
		if ((1.0+R[2][2])>= ZERO_VALUE)
		{
			omg[0] = 1.0 / sqrt(2 * (1.0 + R[2][2]))*R[0][2];
			omg[1] = 1.0 / sqrt(2 * (1.0 + R[2][2]))*R[1][2];
			omg[2] = 1.0 / sqrt(2 * (1.0 + R[2][2]))*(1.0 + R[2][2]);
		}
		else if ((1.0+R[1][1]>=ZERO_VALUE))
		{
			omg[0] = 1.0 / sqrt(2 * (1.0 + R[1][1]))*R[0][1];
			omg[1] = 1.0 / sqrt(2 * (1.0 + R[1][1]))*(1.0 + R[1][1]);
			omg[2] = 1.0 / sqrt(2 * (1.0 + R[1][1]))*R[2][1];
		}
		else 
		{
			omg[0] = 1.0 / sqrt(2 * (1.0 + R[0][0]))*(1.0 + R[0][0]);
			omg[1] = 1.0 / sqrt(2 * (1.0 + R[0][0]))*R[1][0];
			omg[2] = 1.0 / sqrt(2 * (1.0 + R[0][0]))*R[2][0];
		}
		omg[0] = PI*omg[0];
		omg[1] = PI*omg[1];
		omg[2] = PI*omg[2];
		VecToso3(omg, so3Mat);
	}
	else
	{
		int i;
		int j;
		double theta = acos(acosinput);
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				so3Mat[i][j] = 1.0 / (2.0*sin(theta))*(R[i][j] - R[j][i])*theta;
			}
		}
	}

	return;
}

/**
*@brief					Description:Builds the homogeneous transformation matrix T corresponding to a rotation 
*						matrix R in SO(3) and a position vector p in R3.
*@param[in]		R		a rotation matrix R in SO(3).
*@param[in]		p		a position vector p in R3.
*@param[out]	T		the homogeneous transformation matrix T.
*@return		No return value.
*@note:
*@waring:
*/
void RpToTrans(double R[3][3], double p[3], double T[4][4])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			T[i][j] = R[i][j];
		}
	}
	T[0][3] = p[0];
	T[1][3] = p[1];
	T[2][3] = p[2];
	T[3][0] = 0.0; 
	T[3][1] = 0.0; 
	T[3][2] = 0.0;
	T[3][3] = 1.0;
	return;
}

/**
*@brief Description: Extracts the rotation matrix R and position vector p 
from a homogeneous transformation matrix T.
*@param[in]		T		a homogeneous transformation matrix.
*@param[out]	R		the rotation matrix.
*@param[out]	p		position vector.
*@return		No return value.
*@note:
*@waring:
*/
void TransToRp(double T[4][4], double R[3][3], double p[3])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			R[i][j] = T[i][j];
		}
	}
	p[0] = T[0][3];
	p[1] = T[1][3];
	p[2] = T[2][3];
	return;
}

/**
*@brief Description:Computes the inverse of a homogeneous transformation matrix T.
*@param[in]		T		a homogeneous transformation matrix.
*@param[out]	InvT	the inverse of T.
*@return		No return value.
*@note:
*@waring:
*/
void TransInv(double T[4][4],double InvT[4][4])
{
	double R[3][3];
	double InvR[3][3];
	double p[3];
	double p2[3];
	TransToRp(T, R, p);
	RotInv(R, InvR);
	Matrix3MultValue(InvR, -1.0, R);
	Matrix3MultVec(R, p, p2);
	RpToTrans(InvR, p2, InvT);
	return;
}

/**
*@brief Description:Computes the se(3) matrix corresponding to a 6-vector twist V.
*@param[in]		V		a 6-vector twist V.
*@param[out]	se3Mat	the se(3) matrix.
*@return		No return value.
*@note:
*@waring:
*/
void VecTose3(double V[6], double se3Mat[4][4])
{
	double so3Mat[3][3];
	double omg[3];
	int i;
	int j;
	omg[0] = V[0];
	omg[1] = V[1];
	omg[2] = V[2];
	VecToso3(omg, so3Mat);
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			se3Mat[i][j] = so3Mat[i][j];
		}

	}
	se3Mat[0][3] = V[3];
	se3Mat[1][3] = V[4];
	se3Mat[2][3] = V[5];
	se3Mat[3][0] = 0.0;
	se3Mat[3][1] = 0.0;
	se3Mat[3][2] = 0.0;
	se3Mat[3][3] = 0.0;
	return;
}

/**
*@brief Description:Computes the 6-vector twist corresponding to an se(3) matrix se3mat.
*@param[in]		se3Mat			an se(3) matrix.
*@param[out]	V				he 6-vector twist.
*@return		No return value.
*@note:
*@waring:
*/
void se3ToVec(double se3Mat[4][4],double V[6])
{
	V[0] = se3Mat[2][1];
	V[1] = se3Mat[0][2];
	V[2] = se3Mat[1][0];
	V[3] = se3Mat[0][3];
	V[4] = se3Mat[1][3];
	V[5] = se3Mat[2][3];
	return;
}

/**
*@brief Description:Computes the 6 x 6 adjoint representation [AdT ] 
of the homogeneous transformation matrix T.
*@param[in]		T		a homogeneous transformation matrix.
*@param[out]	AdT		the 6 x 6 adjoint representation [AdT ].
*@return		No return value.
*@note:
*@waring:
*/
void Adjoint(double T[4][4], double AdT[6][6])
{
	double R[3][3];
	double p[3];
	double so3Mat[3][3];
	int i;
	int j;
	TransToRp(T, R, p);
	VecToso3(p, so3Mat);
	
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			AdT[i][j] = R[i][j];
		}
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 3; j < 6; j++)
		{
			AdT[i][j] = 0.0;
		}
	}
	for (i=3;i<6;i++)
	{
		for (j = 3; j < 6; j++)
		{
			AdT[i][j] = R[i-3][j-3];
		}
	}
	double mat[3][3];
	Matrix3Mult(so3Mat, R, mat);
	for (i = 3; i < 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			AdT[i][j] = mat[i-3][j];
		}
	}

	return;
}

/**
*@brief			Description: Computes a normalized screw axis representation S of a screw described by 
*				a unit vector s in the direction of the screw axis, located at the point q, with pitch h.
*@param[in]		q		a point lying on the screw axis.
*@param[in]		s		a unit vector in the direction of the screw axis.
*@param[in]		h		the pitch of the screw axis.
*@param[in]		S		a normalized screw axis representation.
*@return		No return value.
*@note:
*@waring:
*/
void ScrewToAxis(double q[3], double s[3], double h,double S[6])
{
	double v[3];
	double temp[3];
	Vec3Cross(s, q, temp);
	Vec3MultValue(temp, -1.0, temp);
	Vec3MultValue(s, h, v);
	Vec3Add(v, temp, v);
	S[0] = s[0];
	S[1] = s[1];
	S[2] = s[2];
	S[3] = v[0];
	S[4] = v[1];
	S[5] = v[2];
	return;
}

/**
*@brief Description: Extracts the normalized screw axis S and the distance traveled along the screw
theta from the 6-vector of exponential coordinates S*theta.
*@param[in]		expc6		the 6-vector of exponential coordinates.
*@param[out]	S			the normalized screw axis.
*@param[out]	theta		the distance traveled along the screw.
*@return		No return value.
*@note:
*@waring:
*/
void AxisAng6(double expc6[6],double S[6],double *theta)
{
	*theta = Vec3Norm(expc6);
	if (*theta<ZERO_VALUE)
	{
		*theta = Vec3Norm(&expc6[3]);
		if (*theta<ZERO_VALUE)
		{
			*theta=0.0;
			//S is undefine,no motion at all.
			S[0] = 0.0; S[1] = 0.0; S[2] = 0.0; S[3] = 0.0; S[4] = 0.0; S[5] = 0.0;
			return;
		}
	}
	Vec3MultValue(expc6, 1.0 / (*theta), S);
	Vec3MultValue(&expc6[3], 1.0 / (*theta), &S[3]);
	return ;
}

/**
*@brief			Description: Computes the homogeneous transformation matrix T in SE(3) corresponding to
*				the matrix exponential of se3mat in se(3).
*@param[in]		se3mat			the matrix exponential of se3mat in se(3).
*@param[out]	T				the homogeneous transformation matrix T in SE(3).
*@return		No return value.
*@note:
*@waring:
*/
void MatrixExp6(double se3Mat[4][4], double T[4][4])
{
	int i;
	int j;
	double so3mat[3][3];
	double omgmat[3][3];
	double temp[3][3];
	double Gtheta[3][3];
	double p[3];
	double v[3];
	double omgtheta[3];
	double omghat[3];
	double theta;
	double MatI3[3][3] =
	{
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0
	};
	TransToRp(se3Mat, so3mat, p);//extracts so3mat from se3mat
	so3ToVec(so3mat, omgtheta);
	if (Vec3Norm(omgtheta)<ZERO_VALUE)
	{
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				T[i][j] = MatI3[i][j];
			}
		}
		T[0][3] = se3Mat[0][3];
		T[1][3] = se3Mat[1][3];
		T[2][3] = se3Mat[2][3];
		T[3][0] = 0.0;
		T[3][1] = 0.0;
		T[3][2] = 0.0;
		T[3][3] = 1.0;
	}
	else
	{
		AxisAng3(omgtheta, omghat, &theta);
		MatrixExp3(so3mat, temp);
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				T[i][j] = temp[i][j];
			}
		}
		Matrix3MultValue(so3mat, 1.0/theta,omgmat);
		Matrix3Mult(omgmat, omgmat, temp);
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				Gtheta[i][j] = MatI3[i][j] * theta + (1.0 - cos(theta))*omgmat[i][j] + (theta - sin(theta))*temp[i][j];
			}
		}	
		v[0] = p[0] / theta; 
		v[1] = p[1] / theta;
		v[2] = p[2] / theta;
		Matrix3MultVec(Gtheta, v, p);
		T[0][3] = p[0]; T[1][3] = p[1]; T[2][3] = p[2];
		T[3][0] = 0.0;
		T[3][1] = 0.0;
		T[3][2] = 0.0;
		T[3][3] = 1.0;
	}
	return;
}


/**
*@brief Description: Computes the matrix logarithm se3mat in se(3) of 
the homogeneous transformation matrix T in SE(3)
*@param[in]		T			the homogeneous transformation matrix.			
*@param[out]	se3Mat		the matrix logarithm of T.
*@return		No return value.
*@note:
*@waring:
*/
void MatrixLog6(double T[4][4], double se3Mat[4][4])
{
	int i;
	int j;
	double R[3][3];
	double so3mat[3][3];
	double p[3];
	TransToRp(T, R, p);
	MatrixLog3(R, so3mat);
	int flag = 0;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			if (fabs(so3mat[i][j])<ZERO_VALUE)
			{
				continue;
			}
			else
			{
				flag = 1;
				break;
			}
		}
	}
	if (!flag)
	{
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				se3Mat[i][j] = 0.0;
			}

		}
		se3Mat[0][3] = T[0][3];
		se3Mat[1][3] = T[1][3];
		se3Mat[2][3] = T[2][3];
		se3Mat[3][0] = 0.0;
		se3Mat[3][1] = 0.0;
		se3Mat[3][2] = 0.0;
		se3Mat[3][3] = 0.0;
	}
	else
	{
		double MatI3[3][3] =
		{
			1.0,0.0,0.0,
			0.0,1.0,0.0,
			0.0,0.0,1.0
		};
		double v[3];
		double temp[3][3];
		double InvGtheta[3][3];
		double theta = acos((R[0][0] + R[1][1] + R[2][2] - 1.0) / 2.0);
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				se3Mat[i][j] = so3mat[i][j];
			}
		}

		Matrix3Mult(so3mat, so3mat, temp);
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				InvGtheta[i][j] = MatI3[i][j] - 0.5*so3mat[i][j] + (1.0 / theta - 0.5*1.0 / tan(0.5*theta))*temp[i][j] / theta;
			}
		}
		Matrix3MultVec(InvGtheta, p, v);
		se3Mat[0][3] = v[0];
		se3Mat[1][3] = v[1];
		se3Mat[2][3] = v[2];
		se3Mat[3][0] = 0.0;
		se3Mat[3][1] = 0.0;
		se3Mat[3][2] = 0.0;
		se3Mat[3][3] = 0.0;
	}
	return ;
}

```

##测试demo

对头文件所列的每个函数均进行了测试，测试demo如下，每个函数的测试程序以test为前缀。如果要修改某个函数的测试参数，直接在test_xxx函数里修改，在main函数调用它就可以了。

```c
/**
 * @brief			Description: Test Demos for robot algorithm modules.
 * @file:			TestDemo.c
 * @author:			LiBing
 * @date:			2019/03/01 12:20
 * Copyright(c) 	2019 LiBing. All rights reserved. 
 *					https://blog.csdn.net/libing403  					 
 * Contact 			1540845930@qq.com
 * @note:     
 * @warning: 		
*/
#include <stdio.h>
#include <math.h>
#include "RobotAlgorithmModule.h"
#define M_PI  3.14159265358979323846
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
	test_JacobianSpace();
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
	AxisAng3(expc3, omghat, &theta);
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
	AxisAng6(expc6, S, &theta);

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

```

接下来继续学习机器人的正运动学和逆运动学，以及基本算法的实现。



参考文献

Kenvin M. Lynch , Frank C. Park, Modern Robotics Mechanics,Planning , and Control. May 3, 2017