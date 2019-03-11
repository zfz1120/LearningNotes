/**
*@brief Description: Algorithm module of robotics, according to the
book [modern robotics : mechanics,planning,and control].
*@  AlgorithmModule.h
*@Author:LiBing
*@  Date:2019/03/01
*@  note:     
*@warning: 
*/
#ifndef RobotALGORITHMMODULE_H_
#define RobotALGORITHMMODULE_H_
#ifdef __cplusplus
extern "C" {
#endif
	#define		PI					3.14159265358979323846
	//if the norm of vector is near zero(< 1.0E-6),regard as zero.
	#define		ZERO_VALUE			1.0E-6		

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
	int GrublersFormula(int m, int N,  int J, int *f);

	/**
	*@brief Computes the inverse of the rotation matrix R.
	*@param[in]		R		rotation matrix .
	*@param[out]	InvR	inverse matrix of R.
	*@note					Input R must be a 3x3 rotation matrix.
	*/
	void RotInv(double R[3][3], double InvR[3][3]);

	/**
	*@brief Description:Returns the 3 x 3 skew-symmetric matrix corresponding to omg.
	*@param[in]		omg		a unit 3-vector.
	*@param[out]	so3Mat	the 3 x 3 skew-symmetric matrix corresponding to omg.
	*@note:
	*@waring:
	*/
	void VecToso3(double omg[3], double so3Mat[3][3]);

	/**
	*@brief Description:Returns the 3-vector corresponding to the 3×3 skew-symmetric matrix so3mat.
	*@param[in]		name
	*@param[out]	name
	*@note:
	*@waring:
	*/
	void so3ToVec(double so3Mat[3][3], double omg[3]);

	/**
	*@brief Description:Extracts  the unit rotation axis omghat and the corresponding rotation angle theta from
	exponential coordinates omghat*theta for rotation, expc3.
	*@param[in]		expc3
	*@param[out]	omghat		the unit vector of rotation axis .
	*@param[out]	theta		rotation angle.
	*@retval        0			success.
	*@retval		1			failure,normal of expc3 is zero or near zero(<1.0E-6).
	*@note:
	*@waring:
	*/
	int AxisAng3(double expc3[3], double omghat[3], double *theta);

	/**
	*@brief Description:Computes the rotation matrix R in SO(3) corresponding to
	the matrix exponential of so3mat in so(3).
	*@param[in]		so3Mat		[omghat]*theta,matrix exponential of so3mat in so(3).
	*@param[out]	R			rotation matrix R in SO(3).
	*@note:
	*@waring:
	*/
	void MatrixExp3(double so3Mat[3][3], double R[3][3]);

	/**
	*@brief Description:Computes the matrix logarithm so3mat in so(3) of the rotation matrix R in SO(3).
	*@param[in]		R		the rotation matrix
	*@param[out]	so3Mat	matrix logarithm
	*@note:
	*@waring:
	*/
	void MatrixLog3(double R[3][3], double so3Mat[3][3]);

	/**
	*@brief Description:Builds the homogeneous transformation matrix T corresponding to a rotation
	matrix R in SO(3) and a position vector p in R3.
	*@param[in]		R		a rotation matrix R in SO(3).
	*@param[in]		p		a position vector p in R3.
	*@param[out]	T		the homogeneous transformation matrix T.
	*@note:
	*@waring:
	*/
	void RpToTrans(double R[3][3], double p[3], double T[4][4]);

	/**
	*@brief Description: Extracts the rotation matrix R and position vector p
	from a homogeneous transformation matrix T.
	*@param[in]		T		a homogeneous transformation matrix.
	*@param[out]	R		the rotation matrix.
	*@param[out]	p		position vector.
	*@note:
	*@waring:
	*/
	void TransToRp(double T[4][4], double R[3][3], double p[3]);

	/**
	*@brief Description:Computes the inverse of a homogeneous transformation matrix T.
	*@param[in]		T		a homogeneous transformation matrix.
	*@param[out]	InvT	the inverse of T.
	*@note:
	*@waring:
	*/
	void TransInv(double T[4][4], double InvT[4][4]);

	/**
	*@brief Description:Computes the se(3) matrix corresponding to a 6 - vector twist V.
	*@param[in]		V		a 6 - vector twist V.
	*@param[out]	se3Mat	the se(3) matrix.
	*@note:
	*@waring:
	*/
	void VecTose3(double V[6], double se3Mat[4][4]);

	/**
	*@brief Description:Computes the 6-vector twist corresponding to an se(3) matrix se3mat.
	*@param[in]		se3Mat			an se(3) matrix.
	*@param[out]	V				he 6-vector twist.
	*@note:
	*@waring:
	*/
	void se3ToVec(double se3Mat[4][4], double V[6]);

	/**
	*@brief Description:Computes the 6 × 6 adjoint representation [AdT ] of the homogeneous transformation matrix T.
	*@param[in]		T		a homogeneous transformation matrix.
	*@param[out]	AdT		the 6 × 6 adjoint representation [AdT ].
	*@note:
	*@waring:
	*/
	void Adjoint(double T[4][4], double AdT[6][6]);

	/**
	*@brief Description: Extracts the normalized screw axis S and the distance traveled along the screw
	theta from the 6-vector of exponential coordinates S*theta.
	*@param[in]		expc6		the 6-vector of exponential coordinates.
	*@param[out]	S			the normalized screw axis.
	*@param[out]	theta		the distance traveled along the screw.
	*@retval		0			success;
	*@retval		1			failure,because the input expc6 is a zero vector
	*@note:
	*@waring:
	*/
	int AxisAng6(double expc6[6], double S[6], double *theta);

	/**
	*@brief Description: Computes the homogeneous transformation matrix T in SE(3) corresponding to
	the matrix exponential of se3mat in se(3).
	*@param[in]		se3mat			the matrix exponential of se3mat in se(3).
	*@param[out]	T				the homogeneous transformation matrix T in SE(3).
	*@note:
	*@waring:
	*/
	int MatrixExp6(double se3Mat[4][4], double T[4][4]);

	/**
	*@brief Description: Computes the matrix logarithm se3mat in se(3) of
	the homogeneous transformation matrix T in SE(3)
	*@param[in]		T			the homogeneous transformation matrix.
	*@param[out]	se3Mat		the matrix logarithm of T.
	*@note:
	*@waring:
	*/
	int MatrixLog6(double T[4][4], double se3Mat[4][4]);

	/**
	*@brief Description: Computes the end-effector frame given the zero position of the end-effector M,
	the list of joint screws Slist expressed in the fixed-space frame, and the list of joint values thetalist.
	*@param[in]		M			the zero position of the end-effector expressed in the fixed-space frame.
	*@param[in]		JointNum	the number of joints.
	*@param[in]		Slist		the list of joint screws Slist expressed in the fixed-space frame.
	*@param[in]		thetalist   the list of joint values.
	*@param[out]	T			the end-effector frame expressed in the fixed-space frame.
	*@note:
	*@waring:
	*/
	int FKinSpace(double M[4][4], int  JointNum, double Slist[][6], double thetalist[], double T[4][4]);

	/**
	*@brief Description:Computes the end-effector frame given the zero position of the end-effector M,
	the list of joint screws Blist expressed in the end-effector frame, and the list of joint values thetalist.
	*@param[in]		M			the zero position of the end-effector expressed in the end-effector frame.
	*@param[in]		JointNum	the number of joints.
	*@param[in]		Blist		the list of joint screws Slist expressed in the end-effector frame.
	*@param[in]		thetalist   the list of joint values.
	*@param[out]	T			the end-effector frame expressed in the end-effector frame.
	*@note:
	*@waring:
	*/
	int FKinBody(double M[4][4], int  JointNum, double Blist[][6], double thetalist[], double T[4][4]);

#ifdef __cplusplus
}
#endif

#endif//RobotALGORITHMMODULE_H_