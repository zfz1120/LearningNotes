# C语言的字符串处理函数strlen()

<center>

<img src="image\永远保持一颗好奇心.jpg" width="500">

图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E4%BF%9D%E6%8C%81%E5%A5%BD%E5%A5%87%E5%BF%83&step_word=&hs=0&pn=13&spn=0&di=82244369900&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=2567575087%2C1262844923&os=3602688194%2C4137518856&simid=4141148317%2C552222645&adpicid=0&lpn=0&ln=1973&fr=&fmq=1497169580356_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fvideos.chinaedu.com%2Fformaluser%2Fywmonthly%2Fuploadfile%2F115e03.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bvitgwj17_z%26e3Bv54AzdH3Fu564ws7fj6AzdH3Fyo45gpisyAzdH3Fxxv5gpjgp_z%26e3Bwfr%3Fvswfft1%3Dn8b%26g74%3Dda8n8d&gsm=0&rpstart=0&rpnum=0)

</center>

## 引言

C库提供了多个字符串处理函数，ANSI C把这些函数的原型放在string.h头文件中。其中最常用的有strlen()、strcat()、strcmp()、strncmp()、strcpy()和strncpy()。另外还有sprintf()，其原型在stdio.h头文件中。这些函数都在后面的博客进行详细分析。

## strlen()函数

strlen()函数用于统计字符串的长度，它会统计字符包括空格和标点符号，不统计空字符`\0`。注意与sizeof运算符区分，sizeof以字节为单位返回运算对象(变量名、类型名等)的大小。

示例：

```c
/* test_fit.c -- try the string-shrinking function */
#include <stdio.h>
#include <string.h> /* contains string function prototypes */
void fit(char *, unsigned int);

int main(void)
{
    char mesg[] = "Things should be as simple as possible,"
    " but not simpler.";
    
    puts(mesg);
    fit(mesg,38);
    puts(mesg);
    puts("Let's look at some more of the string.");
    puts(mesg + 39);
    
    return 0;
}

void fit(char *string, unsigned int size)
{
    if (strlen(string) > size)
        string[size] = '\0';
}
```

下面是该程序的输出：

```tex
Things should be as simple as possible, but not simpler.
Things should be as simple as possible
Let's look at some more of the string.
 but not simpler.
```

fit()函数把第39个元素的逗号换成了空字符`\0`。puts()函数在空字符出停止输出，并忽略其余字符。然而，这些字符还在缓冲区中，下面的函数调用把这些字符打印出来：

```c
puts(mesg + 8);
```

string.h头文件中包含了C字符串函数系列的原型，因此程序中要包含该头文件。