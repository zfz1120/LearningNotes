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
			str[n]=getchar();
}
