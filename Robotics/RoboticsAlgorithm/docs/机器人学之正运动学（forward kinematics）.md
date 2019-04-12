# 机器人学之正运动学（forward kinematics）

![机器人正运动学](image\机器人正运动学.gif)

## 关键概念

- 对于一个开链机器人，给定一个固定参考系{s}和一个固定于连杆的连杆的坐标系{b}, 该坐标系表示机器人末端。正运动学(forward kinematics)是从关节变量$\theta$到坐标系{b}在坐标系{s}中的位置和方向的映射$T(\theta)$。
- 开链机器人正运动学的D-H(Denavit{Hartenberg )表示，是从固定于每个连杆的参考坐标系的相对位移描述的，若连杆坐标系标号为{0}，$\dots$ ，{$n+1$}，{0}是固定坐标系{s}, {$i$}是固定于连杆$i$的关节$i(i=1,\dots,n)$, {$n+1$}是末端坐标系{b}, 那么正运动学表示为

$$
T_{0,n+1}(\theta)=T_{01}(\theta_1)\ldots T_{n-1,n}(\theta_n)T_{n,n+1}
$$

​      这里$\theta_i$表示关节$i$变量，$T_{n,n+1}$表明末端坐标系在坐标系{n}中的构型。如果末端坐标系{b}选择与坐标系{n}重合，我们可以省掉坐标系{n+1}.

- D-H(Denavit{Hartenberg )约定分配给每个连杆的参考坐标系遵循严格的规定。根据规定，连杆坐标系{$i-1$}和{$i$}之间坐标系变换只用4个参数进行参数化，即D-H参数。其中三个参数描述运动机构，第4个参数是关节变量。表示两个连杆间的变换需要的最少参数是4个。
- 正运动学也可以表示成如下的指数积（空间形式）

$$
T(\theta)=e^{[\mathcal S_1]\theta_1  }\ldots e^{[\mathcal S_n]\theta_n}M,
$$

这里$\mathcal S_i=(\omega_i,v_i)$是沿关节$i$正向运动的螺旋轴在固定系坐标{s}中表达，$\theta_i$是关节$i$的变量，$M\in SE(3)$表示机器人末端坐标系{b}的零位(初始位置)。这不需要分别定义每个连杆坐标系，只需要定义$M$和螺旋轴$\mathcal S_1,\dots, \mathcal S_n$。

- 指数积公式也可以等效地写为物体坐标系形式

$$
T(\theta)=Me^{[\mathcal B_1] \theta_1}\ldots e^{[\mathcal B_2]\theta_n},
$$

这里$\mathcal B_i=[Ad_{M^{-1}}]S_i, i=1, \dots, n; \mathcal B_i=(\omega_i,v_i)$ 是关节$i$的螺旋轴在初始状态在坐标系{b}中的表达。

- 通用机器人描述格式(URDF)是一种文件格式，机器人操作系统(ROS)和其他软件使用它描述机器人的运动学，惯性，视觉特性等信息，这种格式用于一般包含母连杆和子连杆的树形机器人，包括开链机构。

## 指数积公式的算法实现

该部分主要包括两个公式的实现，

- 一个是空间形式的: T = FKinSpace(M,Slist,thetalist) , 给定末端在初始构型M和螺旋轴Blist在固定坐标系的表达，以及关节变量thetalist，计算末端在固定坐标系的构型。
- 一个是物体坐标系形式的: T = FKinBody(M,Blist,thetalist) , 给定末端在初始构型M和螺旋轴Blist在物体坐标系的表达，以及关节变量thetalist，计算末端在物体坐标系的构型。

实现代码用到了上一篇博客的刚体运动算法，代码较长，就不放在这里了。下面只列出两个公式的实现代码。代码不断更新迭代，完整的最新源码放在github--[链接](https://github.com/libing403/LearningNotes/tree/master/Robotics/RoboticsAlgorithm)

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
*@brief			Description: Computes the end-effector frame given the zero position of the end-effector M,
*				the list of joint screws Slist expressed in the fixed-space frame, and the list of joint values thetalist.
*@param[in]		M			the zero position of the end-effector expressed in the fixed-space frame.
*@param[in]		Joint		Num	the number of joints.
*@param[in]		Slist		the list of joint screws Slist expressed in the fixed-space frame.
*							in the format of a matrix with the screw axes as the column.
*@param[in]		thetalist   the list of joint values.
*@param[out]	T			the end-effector frame expressed in the fixed-space frame.
*@return		No return value.
*@note:			when Slist is a matrix ,make sure that columns number of Slist is equal to JointNum,
*				rows number of Slist 6 .The function call should be written as
*				FKinBody(...,(double *)Slist,...).
*@waring:
*/
void FKinSpace(double M[4][4],int  JointNum,double *Slist, double *thetalist,double T[4][4])
{
	int i, j, k, l;
	double se3mat[4][4];
	double T2[4][4];
	double exp6[4][4];
	double V[6];
	Matrix4Equal(M, T);
	for (i= JointNum-1;i>=0;i--)
	{
		for (l=0;l<6;l++)
		{
			V[l] = Slist[l*JointNum+i];//get each column of Slist.
		}
		VecTose3(V, se3mat);
		for (j=0;j<4;j++)
		{
			for (k=0;k<4;k++)
			{
				se3mat[j][k] = se3mat[j][k] * thetalist[i];
			}
		}
		MatrixExp6(se3mat, exp6);
		Matrix4Mult(exp6, T, T2);
		Matrix4Equal(T2, T);
	}
	return ;
}

/**
*@brief			Description:Computes the end-effector frame given the zero position of the end-effector M,
*				the list of joint screws Blist expressed in the end-effector frame, and the list of joint values thetalist.
*@param[in]		M			the zero position of the end-effector expressed in the end-effector frame.
*@param[in]		JointNum	the number of joints.
*@param[in]		Blist		the list of joint screws Slist expressed in the end-effector frame.
*							in the format of a matrix with the screw axes as the column.
*@param[in]		thetalist   the list of joint values.
*@param[out]	T			the end-effector frame expressed in the end-effector frame.
*@return		No return value.
*@note:			when Blist is a matrix ,make sure that columns number of Slist is equal to JointNum,
*				rows number of Slist 6 .The function call should be written as
*				FKinBody(...,(double *)Blist,...).
*@waring:
*/
void FKinBody(double M[4][4], int  JointNum, double *Blist, double thetalist[], double T[4][4])
{
	int i, j, k, l;
	double se3mat[4][4];
	double T2[4][4];
	double exp6[4][4];
	double V[6];
	Matrix4Equal(M, T);
	for (i = 0; i < JointNum ; i++)
	{
		for (l = 0; l < 6; l++)
		{
			V[l] = Blist[l*JointNum + i];//get each column of Slist.
		}
		VecTose3(V, se3mat);
		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 4; k++)
			{
				se3mat[j][k] = se3mat[j][k] * thetalist[i];
			}
		}
		MatrixExp6(se3mat, exp6);
		Matrix4Mult(T, exp6, T2);
		Matrix4Equal(T2, T);
	}
	return ;
}
```









参考文献

Kenvin M. Lynch , Frank C. Park, Modern Robotics Mechanics,Planning , and Control. May 3, 2017

