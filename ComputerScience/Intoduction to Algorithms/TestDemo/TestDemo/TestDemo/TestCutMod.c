#include "CutRod.h"
#include<stdio.h>
int test_MemoizedCutRod();
int test_BottomUpCutRod();
int main()
{
	test_BottomUpCutRod();
	return 0;

}

int test_MemoizedCutRod()
{
	int n = 10;
	double p[10] = { 1,5,8,9,10,17,17,20,24,30 };
	double q = 0;
	int ret = 0;
	ret = MemoizedCutRod(p, n, &q);
	if (ret)
	{
		printf("MemoizedCutMod error %d\n", ret);
	}
	printf("r=%lf\n", q);
	return 0;
}

test_BottomUpCutRod()
{
	int n = 10;
	double p[10] = { 1,5,8,9,10,17,17,20,24,30 };
	double rn=0;
	int s[10] = { 0 };
	int ret = 0;
	ret = MemoizedCutRod(p, n, &rn,s);
	if (ret)
	{
		printf("MemoizedCutMod error %d\n", ret);
	}
	printf("rn=%lf\n", rn);
	return 0;
}