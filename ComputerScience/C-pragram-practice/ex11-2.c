/*修改并编程练习1的函数，在n个字符后停止，或读到第一个空白、制表符或换行时
 * 停止，哪个先遇到哪个停止。不能只是用scanf()*/
#include <stdio.h>
#include<string.h>
#define LEN 5
void strin(char * str);
int main(void)
{
	char str[LEN];
	printf("请输入5个字符：\n");
	strin(str);
	puts("输入的5个字符为：");
	for(int n=0;n<LEN;n++)
			putchar(str[n]);
}
void strin(char * str)
{
	for(int n=0;n<LEN;n++)
	{
		if((str[n]=getchar())=='\n' || str[n]=='	' || str[n]==' ')
				break;
	}
}
