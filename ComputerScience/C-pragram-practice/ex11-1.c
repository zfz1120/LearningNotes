#include <stdio.h>
 	int main()
	{
		int n=5;
		char str[6];
		char *pstr;
		printf("请输入5个字符:\n");
		pstr=strin(str,n);
		printf("输入的字符为：\n %s\n",*pstr);
	}
	char * strin(char * str,int n)
	{
		int count=0;
		char ch;
        while(count<=n)
		{
			ch=getchar();
			str[count]=strcat(str,ch);
		}
		return str;

	}
