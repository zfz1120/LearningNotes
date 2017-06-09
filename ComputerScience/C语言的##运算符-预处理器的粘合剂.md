# C语言的\#\#运算符-预处理器的粘合剂

<center>

<img src="image\路虽远行则至.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%9D%9A%E6%8C%81%E7%9A%84%E5%90%8D%E8%A8%80&step_word=&hs=0&pn=0&spn=0&di=130503359470&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=3640296637%2C2377378283&os=4263340294%2C734970500&simid=3081243213%2C3804932549&adpicid=0&lpn=0&ln=1931&fr=&fmq=1497039637495_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fwww.xpdq.net%2Fpic%2Ffckimg%2F7(19).jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bxr1q_z%26e3BgjpAzdH3FgjofAzdH3F4tg2xtg2AzdH3Fdaln_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

## 引言

与\#运算符类似，`##`运算符可以用于类函数宏的替换部分。而且，还可以用于宏对象的替换部分。`##`运算符可以把两个记号组合成一个。

## 示例分析

```c
// glue.c -- use the ## operator
#include <stdio.h>
#define XNAME(n) x ## n
#define PRINT_XN(n) printf("x" #n " = %d\n", x ## n);

int main(void)
{
    int XNAME(1) = 14;  // becomes int x1 = 14;
    int XNAME(2) = 20;  // becomes int x2 = 20;
    int x3 = 30;
    PRINT_XN(1);        // becomes printf("x1 = %d\n", x1);
    PRINT_XN(2);        // becomes printf("x2 = %d\n", x2);
    PRINT_XN(3);        // becomes printf("x3 = %d\n", x3);
    return 0;
}
```

该程序的输出结果如下：

```tex
x1 = 14
x2 = 20
x3 = 30
```

注意，PRINT_XN()宏用`#`运算符组合字符串，`##`运算符把记号组合为一个新的标识符。

`##`运算符在命名一些特殊要求的变量名的时候很有帮助，例如，把已有的变量名作为宏参数，在已有变量名加后缀或者前缀，定义新变量名。当旧变量名发生变化时，新的变量名也自动跟着变化，若要修改新变量名的前缀或后缀，只需修改宏定义就行了，而不必去找每个变量定义的地方。