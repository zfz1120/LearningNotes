# C语言的宏之明示常量

<center>

<img src="image\封面-追寻生命的意义.jpg">

图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E7%94%9F%E5%91%BD%E7%9A%84%E6%84%8F%E4%B9%89%E5%90%8D%E8%A8%80&step_word=&hs=0&pn=55&spn=0&di=50700306140&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=4146389931%2C2449175597&os=780915895%2C2964941918&simid=4261059814%2C669710991&adpicid=0&lpn=0&ln=1974&fr=&fmq=1496998479695_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fpic.baike.soso.com%2Fp%2F20140707%2F20140707111124-1294728875.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fkwthj_z%26e3Bf5257_z%26e3Bv54AzdH3Feb9bm8m0_z%26e3Bip4&gsm=0&rpstart=0&rpnum=0)

</center>

## 引言

预处理功能是C语言特有的功能，它是在对源程序正式编译前由预处理程序完成的，程序员在程序中用预处理命令来调用这些功能。

宏定义可以带有参数，宏调用时是以实参代换形参，而不是“值传送”。

为了避免宏代换时发生错误，宏定义中的字符串应加括号，字符串中出现的形式参数两边也应加括号。

文件包含是预处理的一个重要功能，它可用来把多个源文件连接成一个源文件进行编译，结果将生成一个目标文件。

条件编译允许只编译源程序中满足条件的程序段，使生成的目标程序较短，从而减少了内存的开销并提高了程序的效率。

使用预处理功能便于程序的修改、阅读、移植和调试，也便于实现模块化程序设计。

## 明示常量(符号常量)

\#define预处理指令和其他预处理指令一样，以\#号作为一行的开始。ANSI和后来的标准都允许\#号前有空格或制表符，而且还允许在\#和指令的其余部分之间有空格。但是旧版的C要求指令从一行最左边开始，而且\#和其余部分之间不能有空格。指令可以出现在源文件的任何地方，其定义从质量出现的地方到该文件末尾有效。我们大量使用\#define指令来定义**明示常量(也叫符号常量)。**

示例：

```c
/* preproc.c -- simple preprocessor examples */
#include <stdio.h>
#define TWO 2        /* you can use comments if you like   */
#define OW "Consistency is the last refuge of the unimagina\
tive. - Oscar Wilde" /* a backslash continues a definition */
/* to the next line                   */
#define FOUR  TWO*TWO
#define PX printf("X is %d.\n", x)
#define FMT  "X is %d.\n"

int main(void)
{
    int x = TWO;
    
    PX;  /*宏展开后变成 printf("X is %d.\n", x); */
    x = FOUR;
    printf(FMT, x);
    printf("%s\n", OW);
    printf("TWO: OW\n");
    
    return 0;
}
```

每行\#define（逻辑行）都由3部分组成。第一部分是\#define指令本身。第二部分是选定的缩写，**也成为宏**，宏的名称必须遵循C变量的命名规则。第三部分（指令行的其余部分）称为**替换列表或替换体。**一旦预处理器在程序中找到宏的实例后，就会用替换体代替该宏。从宏编程最终替换文本的过程称为**宏展开。**注意，可以在\#define行使用标准C注释。

宏可以代表任何字符串，甚至可以表示整个C表达式。

宏定义还可以包含其他宏（一些编译器不支持这种嵌套功能）。

```c
 printf(FMT, x);
```

变成了

```
printf("X is %d.\n", x);
```

一般而言，预处理器发现程序中的宏后，会用宏等价的替换文本进行替换。如果替换的字符串中还包含宏，则继续替换这些宏。唯一例外的是双引号汇总的宏。因此，下面的语句：

```c
printf("TWO: OW\n");
```

打印的是

```c
TWO: OW
```

而不是

```c
2:"Consistency is the last refuge of the unimaginative. - Oscar Wilde
```

## 宏定义的几点说明[^1]

1) 宏定义是用宏名来表示一个字符串，在宏展开时又以该字符串取代宏名，这只是一种简单的替换。字符串中可以含任何字符，可以是常数，也可以是表达式，预处理程序对它不作任何检查，如有错误，只能在编译已被宏展开后的源程序时发现。

2) 宏定义不是说明或语句，在行末不必加分号，如加上分号则连分号也一起替换。

3) 宏定义必须写在函数之外，其作用域为宏定义命令起到源程序结束。如要终止其作用域可使用`#undef`命令。

4) 宏名在源程序中若用引号括起来，则预处理程序不对其作宏代换。

5) 宏定义允许嵌套，在宏定义的字符串中可以使用已经定义的宏名，在宏展开时由预处理程序层层代换（一些编译器不支持这种嵌套功能）。

6) 习惯上宏名用大写字母表示，以便于与变量区别。但也允许用小写字母。

7) 可用宏定义表示数据类型，使书写方便。例如：

```c
#define UINT unsigned int
```

在程序中可用UINT作变量说明：

```c
UINT a, b;
```

应注意用宏定义表示数据类型和用typedef定义数据说明符的区别。宏定义只是简单的字符串代换，是在预处理完成的，而typedef是在编译时处理的，它不是作简单的代换，而是对类型说明符重新命名。被命名的标识符具有类型定义说明的功能。

## 结语

那么，何时使用字符常量？对于绝大部分数字常量，应该使用字符常量。如果在算式中用字符常量代替数字，常量名能更清楚地表达该数字的含义。如果是表示数组大小的数字，用符号常量更容易改变数组的大小和循环次数。如果数字是系统代码（如，EOF），用符号常量表示的代码更容易移植。助记、易更改、可移植，这些都是符号常量很有价值的特性。

---

参考资料

[^1]: C语言宏定义---[来源](http://c.biancheng.net/cpp/html/65.html)

2. 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.