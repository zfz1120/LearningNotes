/**
*@brief Description: æÿ’Û‘ÀÀ„∫Ø ˝
*@  File:MatrixCalc.h
*@Author:LiBing
*@  Date:2019/02/26
*@  note:     
*@warning: 
*/
#ifndef MATRIXCALC_H_
#define MATRIXCALC_H_
#ifdef __cplusplus
extern "C" {
#endif
#define  MaxDimensions	1000

	int MatrixMultply(double A[][3], int ARow, int AColumn, 
		double B[][4], int BColumn, double C[][4]);



#ifdef __cplusplus
}
#endif

#endif//MATRIXCALC_H_