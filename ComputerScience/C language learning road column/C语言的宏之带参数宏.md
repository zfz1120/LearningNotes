# C语言的宏之带参数宏

<center>

<img src="image\科学永无止境-爱因斯坦.jpg" width="500" >

*百度来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E7%94%9F%E5%91%BD%E7%9A%84%E5%90%8D%E8%A8%80&step_word=&hs=0&pn=23&spn=0&di=139239062600&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=2345797117%2C1184582099&os=3825731392%2C75616293&simid=3484991958%2C322711342&adpicid=0&lpn=0&ln=1974&fr=&fmq=1497001846776_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fwww.yw11.com%2Fuploads%2Fallimg%2F141015%2F5916-141015163321T3.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Byo88_z%26e3Bv54AzdH3F3tg21twgy7s7AzdH3F4tg26jg4tg2ywgAzdH3Fda898a8c_l8md_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

## 引言

C语言允许宏带有参数。在宏定义中的参数称为形式参数，在宏调用中的参数称为实际参数，这种宏外形和作用与函数类似，即类函数宏。但是它的行为和函数调用完全不同。对带参数的宏，在调用中，不仅要宏展开，而且要用实参去代换形参。类函数宏定义的圆括号中可以有一个或多个参数，随后这些参数出现在替换体中。

## 示例分析

下面是一个类函数宏的示例：

```c
#define SQUARE(X) X*X
```

在程序中可以这样使用：

```c
z= SQUARE(2);
```

这看上去像函数调用，但是它的行为和函数调用完全不同。

再看下面的示例：

```c
/* mac_arg.c -- macros with arguments */
#include <stdio.h>
#define SQUARE(X) X*X
#define PR(X)   printf("The result is %d.\n", X)
int main(void)
{
    int x = 5;
    int z;
    
    printf("x = %d\n", x);
    z = SQUARE(x);
    printf("Evaluating SQUARE(x): ");
    PR(z);
    z = SQUARE(2);
    printf("Evaluating SQUARE(2): ");
    PR(z);
    printf("Evaluating SQUARE(x+2): ");
    PR(SQUARE(x+2));
    printf("Evaluating 100/SQUARE(2): ");
    PR(100/SQUARE(2));
    printf("x is %d.\n", x);
    printf("Evaluating SQUARE(++x): ");
    PR(SQUARE(++x));
    printf("After incrementing, x is %x.\n", x);
    
    return 0;
}
```

输出结果如下，你的编译器输出甚至有可能与下面的结果完全不同。

```tex
x = 5
Evaluating SQUARE(x): The result is 25.
Evaluating SQUARE(2): The result is 4.
Evaluating SQUARE(x+2): The result is 17.
Evaluating 100/SQUARE(2): The result is 100.
x is 5.
Evaluating SQUARE(++x): The result is 49.
After incrementing, x is 7.
```

程序中， SQUARE(2)替换为`2*2`，x实际上起到参数的作用。前两行与预期相符，但是接下来的结果有点奇怪。导致这样结果的原因是预处理器 不做计算、不求值，只替换字符序列。对于SQUARE(x+2)，预处理器替换为 `x+2*x+2`。如果x=5，那么表达式的值为：

```tex
5+2*5+2 = 5+10+2=17
```

宏定义的时候多加几个括号可以解决这样的问题：

```c
#define SQUARE(X) (X)*(X)
```

现在SQUARE(2)变成`(x+2)*(x+2)`，可以得到正确结果。

但是加括号不能解决所有问题。最后一种情况的问题还是无法避免。

`SQUARE(++x)`变成了`++x*++x`，递增了两次，一次在乘法运算前，一次在乘法运算后：

```tex
++x*++x=6*7=42
```

由于标准并未对这类运算规定顺序，所以有些编译器得`6*7`。而有些编译器可能在乘法运算之前已经递增了x，所以`7*7`得49。在C标准中，对该表达式求值的这种情况称为未定义行为。无论哪种情况，x的开始值是5，虽然从源代码上看只递增了一次，但是x的最终值是7。

解决这个问题最简单的方法是，避免用++x作为宏参数。一般而言，不要在宏中使用递增或递减运算符。但是，++x可作为函数参数，因为编译器会对++x求值后，再把5传给函数。

----

参考资料：

 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.



