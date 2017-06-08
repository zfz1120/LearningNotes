# C语言数据类型

<center>

<img src="image\广西大学荷花.jpg" width="500">

*广西大学荷花-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%B9%BF%E8%A5%BF%E5%A4%A7%E5%AD%A6%E9%A3%8E%E6%99%AF%E8%8D%B7%E8%8A%B1&step_word=&hs=2&pn=46&spn=0&di=4537789520&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=2764808382%2C2587124551&os=2595004347%2C1350532638&simid=4148632060%2C651037203&adpicid=0&lpn=0&ln=1982&fr=&fmq=1496887584684_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fimg.pconline.com.cn%2Fimages%2Fupload%2Fupc%2Ftx%2Fphotoblog%2F1106%2F21%2Fc1%2F8074845_8074845_1308624551546.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3F1r_z%26e3Brv5gstgj_z%26e3Bv54_z%26e3BvgAzdH3F1ri5p5AzdH3Fstfp_d8danbd_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

按计算机的存储方式可分为两大基本类型：**整数类型**和**浮点数类型**，不同的种类提供了不同的范围和精度。

## 关键字

创建基本数据类型要用到8个关键字：int、long、short、unsigned、char、float、double、signed（ANSI C）。

## 有符号整数

int是所有系统中基本整数类型。

long 或long int 可存储的整数应大于或等于int可储存的最大数；long至少是32位。

short 或short int 整数应小于或等于int 储存的最大数；short至少是16位。通常，long比short 大。例如，在pc中C DOS 编译器提供16位的short和int、32位的long。这完全取决于系统。

C99标准提供了long long类型，至少和long一样大，至少是64位。

## 无符号整数

无符号整数只有0和正值，这使得该类型能表示的正数范围更大。在所需的类型前面加上关键字unsigned： unsigned int、unsigned long、unsigned short、unsigned long long。单独的unsigned相当于unsigned int。

## 字符

字符是如A、&、+这样的印刷符号。根据定义，char类型的变量占用1字节的内存。过去，char类通常是8位。然而，C在处理更大的字符集时，char类型可以是16位，或者32位。

这种类型的关键字是char。一些实现使用符号char，但是其他实现使用无符号的char。ANSIC允许使用关键字signed和unsigned指定所需类型。从技术上看，char、unsigned char和signed char是3种不同的类型，但是char类型与其他两种类型的表示方法相同。

## 布尔类型（C99）

_Bool 是C99新增的布尔类型。它是一个无符号整数类型，只能储存0（表示假）或1（表示真）。包含stdbool.h头文件后，可以用bool表示 _Bool、true表示1、false表示0，让代码与C++兼容。

## 浮点数和复浮点数类型

C99识别两种浮点数类型：实浮点数和复浮点数。浮点类型由这两种类型构成。

实浮点数可以是正值或复值。C识别3种实浮点数类型。

float是系统中的基本浮点数类型。它至少可以精确表示6位有效数字，通常float为32位。

double（可能）表示更大的浮点数。它能表示比float更多的有效数字和更大的指数。它至少能精确表示10位有效数字。通常double为64位。

long double（可能）表示更大的浮点数。它能表示比double更多的有效数字和更大的指数。

复数由两部分组成：实部和虚部。C99规定一个复数在内部用一个有两个元素的数组表示，第一个元素表示实部，第二个元素表示虚部。有3种复浮点数类型。

float _Complex表示实部和虚部都是float类型的值。

double _Complex表示实部虚部都是double类型的值。

long double _Complex表示实部和虚部都是long double类型的值。

每种情况，前缀部分的类型都称为相应的实数类型（corresponding real type）。例如，double是double _Complex相应的实数类型。

C99中，复数类型在独立环境中是可选的，这样的环境中不需要操作系统也可以运行C程序。在C11中，复数类型在独立环境和主机环境都是可选的。

有3种虚数类型。它们在独立环境和主机环境中（C程序在一种操作系统下运行的环境）都是可选的。虚数只有虚部。这3中类型如下。

float _Imaginary表示虚部是float类型的值。

double _Imaginary表示虚部是double类型的值。

long double _Imaginary表示虚部是long double类型的值。

可以用实数和I值类初始化复数，I定义在complex.h头文件中，表示i（即-1的平方根）。

```c
#include <complex.h>                       //I定义在该头文件中
double _Complex z= 3.0;                    //实部=3.0，虚部=0
double _Complex w= 4.0*I;                  //实部=0.0，虚部=4.0
double _Complex u=6.0-8.0*I;               //实部=6.0，虚部=-8.0
```

complex.h库包含一些返回复数实部和虚部的函数。

## 类型的打印转换说明

|            类型             |   转换说明(十进制)   |         转换说明(八进制；十六进制)          |
| :-----------------------: | :-----------: | :-----------------------------: |
|            int            |      %d       | 八进制：%o, %#o;十六进制：%x,%X,%#x, %#X |
|           float           |  %f, %e, %E   |       八进制： ; 十六进制：%a, %A        |
|          double           |  %f, %e, %E   |       八进制： ; 十六进制：%a, %A        |
|    short (或short int)     |      %hd      |       八进制：%ho ; 十六进制：%hx        |
|      long (long int)      |      %ld      |       八进制：%lo ; 十六进制：%lx        |
| long long(或long long int) |     %lld      |      八进制：%llo ; 十六进制：%llx       |
|          usigned          |      %u       |       八进制：%uo ; 十六进制：%ux        |
|  long float或long double   | %Ld, %Le, %LE |      八进制： ; 十六进制：%La, %LA       |
|                           |               |                                 |