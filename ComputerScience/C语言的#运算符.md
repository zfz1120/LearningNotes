# C语言的\#运算符

<center>

<img src="image\志存高远.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E7%A7%91%E5%AD%A6%E6%8E%A2%E7%B4%A2%E7%9A%84%E5%90%8D%E8%A8%80&step_word=&hs=0&pn=32&spn=0&di=373788470&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=367379532%2C130610843&os=1697458005%2C107926560&simid=3280890452%2C3806649384&adpicid=0&lpn=0&ln=1975&fr=&fmq=1497037777761_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fuploads.yjbys.com%2Fallimg%2F161226%2F4-161226115032.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fy3kyf_z%26e3Bv54AzdH3F4tg2ywgAzdH3F3tg237AzdH3Fd0bcm_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

## 引言

在类函数宏中（带参数的宏），\#号作为一个预处理运算符，可以把记号转换成字符串。

## 示例分析

下面是一个类函数宏：

```c
#define PSQR(X) printf("The square of X is %d. \n",((X)*(X))
```

假设这样使用宏：

```c
PSQR(8);
```

输出为

```tex
The square of X is 64.
```

注意双引号字符串中X被视为普通文本，而不是一个可被替换的记号。

C语言允许在字符串中包含宏参数。在类函数宏中（带参数的宏），\#号作为一个预处理运算符，可以把记号转换成字符串。例如，如果x是一个宏形参，那么`#x`就是转换为字符串“x”的**形参名 **。这个过程称为**字符串化**。

示例：

```c
/* subst.c -- substitute in string */
#include <stdio.h>
#define PSQR(x) printf("The square of " #x " is %d.\n",((x)*(x)))

int main(void)
{
    int y = 5;
    
    PSQR(y);
    PSQR(2 + 4);
    
    return 0;
}
```

该程序的输出如下：

```tiki wiki
The square of y is 25.
The square of 2 + 4 is 36.
```

调用第一个宏时，用“y”替换`#x`，调用第二个宏时，用"2 + 4"替换`#x`。ANSI C字符串的串联特性将这些字符串与printf()语句的其他字符串组合，生成最终的字符串。例如，第一次调用变成：

```c
printf("The square of ""y"" is %d.\n",((y)*(y)));
```

然后，字符串串联功能将这三个字符串组合成一个字符串：

```c
"The square of y is %d.\n"
```

注意，\#的这种作用只有在类函数宏的替换体中才能发挥这种作用。

---

参考资料：

史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.