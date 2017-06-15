# C语言的预处理和条件编译指令



<center>

<img src="image\很多一分钟加起来就是人生.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E7%8F%8D%E6%83%9C%E6%97%B6%E9%97%B4&step_word=&hs=0&pn=111&spn=0&di=169832985740&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=3076736185%2C1057463264&os=3450619954%2C857616664&simid=3289131508%2C348863461&adpicid=0&lpn=0&ln=1942&fr=&fmq=1497421430527_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fwww.mzdzfx.com%2Fnjdt%2FUploadFiles_6919%2F201207%2F2012070311020046.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3B4z1zux_z%26e3Bv54AzdH3Fg31pAzdH3Fvyg3AzdH3Fda8da0AzdH3Fb0m_z%26e3Bip4s&gsm=3c&rpstart=0&rpnum=0)*

</center>

# 预处理简介

- C语言由源代码生成的各阶段如下：

C源程序－>编译预处理－>编译－>优化程序－>汇编程序－>链接程序－>可执行文件

其中 编译预处理阶段，读取c源程序，对其中的伪指令（以`#`开头的指令）和特殊符号进行处理。或者说是扫描源代码，对其进行初步的转换，产生新的源代码提供给编译器。预处理过程先于编译器对源代码进行处理。

​       在C 语言中，并没有任何内在的机制来完成如下一些功能：在编译时包含其他源文件、定义宏、根据条件决定编译时是否包含某些代码。要完成这些工作，就需要使用预处理程序。尽管在目前绝大多数编译器都包含了预处理程序，但通常认为它们是独立于编译器的。预处理过程读入源代码，检查包含预处理指令的语句和宏定义，并 对源代码进行响应的转换。预处理过程还会删除程序中的注释和多余的空白字符。

- 伪指令（或预处理指令）定义：

​      预处理指令是以#号开头的代码行。`#`号必须是该行除了任何空白字符外的第一个字符。`#`后是指令关键字，在关键字和`#`号之间允许存在任意个数的空白字符。整行语句构成了一条预处理指令，该指令将在编译器进行编译之前对源代码做某些转换。下面是部分预处理指令：

> >指令         用途
>
> ```tex
> #           空指令，无任何效果
> #include    包含一个源代码文件
> #define     定义宏
> #undef      取消已定义的宏
> #if         如果给定条件为真，则编译下面代码
> #ifdef      如果宏已经定义，则编译下面代码
> #ifndef     如果宏没有定义，则编译下面代码
> #elif       如果前面的#if给定条件不为真，当前条件为真，则编译下面代码，其实就是else if的简写
> #endif      结束一个#if……#else条件编译块
> #error      停止编译并显示错误信息
> ```

## 预处理指令

预处理指令主要包括以下四个方面：

- 宏定义指令。前面博客已经介绍--《[C语言的宏之明示常量](http://blog.csdn.net/libing403/article/details/72973301) 》，《[C语言的宏之带参数宏](http://blog.csdn.net/libing403/article/details/72973720) 》
- 条件编译指令。
- 头文件包含指令。前面博客已经介绍--《[C语言的头文件详解](http://blog.csdn.net/libing403/article/details/72984059) 》
- 特殊符号（即预定义宏）。



## 条件编译指令

 程序员可以通过定义不同的宏来决定编译程序对哪些代码进行处理。条件编译指令将决定那些代码被编译，而哪些是不被编译的。可以根据表达式的值或者某个特定的宏是否被定义来确定编译条件。下面介绍常用的条件编译指令。

- **`#ifdef、#else`和`#endif` 指令**

  示例：

  ```c
  #ifdef MAVIS
       #include "horse.h" //如果已经用#define定义了MAVIS，则执行下面的指令
  	 #define STABLES 5
  #else
  	#include "cow.h"    //如果没有用#define定义MAVIS，则执行下面的指令
      #define STABLES 15
  #endif
  ```

  上面的缩进格式只有侥幸的编译器和ANSI标准才支持，太旧的编译器，必须左对齐所有的指令或至少左对齐`#`号。

  `#ifdef`指令说明，如果预处理器已经定义了后面的标识符（MAVIS），则则行`#else`或`#endif`指令之前所有指令并编译所有C代码。如果预处理器未定义MAVIS，且有`#else`指令，则执行`#else`和`#endif`指令之间的所有代码。

- **`#ifndef`指令 **

  `#ifndef`指令与`ifdef`指令用法类似，也可以和`#else、#endif`一起使用，但是他们的逻辑相反。`#ifndef`指令判断后面的标识符是否未定义，常用于定义之前未定义的常量。通常，包含多个头文件时，其中的头文件可能包含了相同的宏定义，**#ifndef指令可以防止相同的宏被重复定义。**在首次定义一个宏的头文件中用`#ifndef`指令激活定义，随后的其他头文件中的定义都被忽略。如下示例：

  ```c
  /*arrays.h*/
  #ifndef SIZE 100
          #define SIZE 100
  #endif
  ```

  **`#ifndef`指令还有另一种用法。**假设有上面的arrays.h头文件，然后把下面一行代码放入一个头文件中：

  `#include "arrays.h"`

  SIZE被定义为100。但是如果把下面的代码放入该头文件:

  ```c
  #define SIZE 10
  #include "arrays.h"
  ```

  因为Size已经被设置为10，因此会调过arrays.h中的`#define SIZE 100`这行diamante，防止重复宏定义。**#ifndef指令通常用于防止多次包含一个文件。**因此应该像下面这样设置头文件：

  ```c
  /*things.h*/
  #ifndef THING_H_
  	#define THINGS_H_
      /*省略了头文件中其他内容*/
  #endif
  ```

  假设该文件被包含了多次，当预处理器首次发现该文件被包含时，`THINGS_H_`是未定义的，所以定义了`THINGS_H_`，并接着处理该文件的其他部分。当预处理器第二次发现该文件被包含时，`THINGS_H_`是已定义的，所哟预处理器调过了该文件的其他部分。

  如何确保待测试表示符没有在别处定义？实现的供应商这样做：用文件名作为标识符、使用大写字符、下划线代替文件名中的点字符、用下划线字符做前缀或后缀。例如stdio.h头文件，有许多类似的代码：

  ```c
  #ifndef _STDIO_H
  #define _STDIO_H
  //省略了文件的内容
  #endif
  ```

  我们也可以这样做，但是由于标准中使用了下划线作为前缀，因此，我们自己的代码汇总不要这样写，避免与标准头文件中的宏发生冲突。应该像下面是一个示例那样写：

  ```c
  // names.h --避免重复包含的头文件写法

  #ifndef NAMES_H_
  #define NAMES_H_

  // constants
  #define SLEN 32

  // structure declarations
  struct names_st
  {
      char first[SLEN];
      char last[SLEN];
  };

  // typedefs
  typedef struct names_st names;

  // function prototypes
  void get_names(names *);
  void show_names(const names *);
  char * s_gets(char * st, int n);

  #endif
  ```

- **`#if`和`#elif`**指令

  `#if`指令检测跟在制造另关键字后的常量表达式。如果表达式为真，则编译后面的代码，知道出现`#else、#elif`或`#endif`为止；否则就不编译。`#endif`用于终止`#if`预处理指令。

  示例：

  ```c
  #if SYS ==1
  	#include "ibmpc.h"
  #elif SYS ==2
  	#include "vax.h"
  #elif SYS ==3
  	#include "mac.h"
  #else
  	#include "general.h"
  #endif
  ```

  还有一种写法。define是一个预处理运算符，如果它的参数是用#define定义过，则返回1；否则返回0。这样它可以与`#elif`一起使用。因此上面的代码还可以写成下面的形式：

  ```c
  #if define (IBMPC)
  	#include "ibmpc.h"
  #elif define (VAX)
  	#include "vax.h"
  #elif define (MAC)
  	#include "mac.h"
  #else
  	#include "general.h"
  #endif
  ```

  如果在VAX机上运行着几行代码，那么应该在文件前面用下面的代码定义VAX:

  `#define VAX`

**条件还有一个好处是让程序更容易移植，改变文件开头的几个关键定义，即可根据不同的系统设置不同的值和包含不同的文件。**

## 预定义宏

预编译程序可以识别一些特殊的符号。预编译程序对于在源程序中出现的这些串将用合适的值进行替换。C标准规定了一些预定义宏，如下表所示：

<center>

表1 预定义宏

</center>

| 宏                  | 含义                                       |
| ------------------ | ---------------------------------------- |
| `__DATE__`         | 预处理的日期（"Mmm dd yyyy"形式的字符串字面量，如Nov 23 2013） |
| `__FILE__`         | 表示当前源代码文件名的字符串字面量                        |
| `__LINE__`         | 表示当前源代码文件中行号的整型常量                        |
| `__STDC__`         | 设置为1时，表明实现遵循C标准                          |
| `STDC_HOSTED`      | 本机环境设置为1；否则设置为0                          |
| `__STDC_VERSION__` | 支持C99标准，设置为199901L；支持C11设置为201112L       |
| `__TIME__`         | 翻译代码的时间，格式为"hh:mm:ss"                    |

其中一些预定义宏时C99新增的，如果使用GCC编译器，必须设置-std=c99或-std=c11。

示例：

```c
// predef.c -- predefined identifiers
#include <stdio.h>
void why_me();

int main()
{
    printf("The file is %s.\n", __FILE__);
    printf("The date is %s.\n", __DATE__);
    printf("The time is %s.\n", __TIME__);
    printf("The version is %ld.\n", __STDC_VERSION__);
    printf("This is line %d.\n", __LINE__);
    printf("This function is %s\n", __func__);
    why_me();
    
    return 0;
}

void why_me()
{
    printf("This function is %s\n", __func__);
    printf("This is line %d.\n", __LINE__);
}
```

该程序的输出如下：

```tex
The file is predef.c.
The date is Jun 14 2017.
The time is 14:06:55.
The version is 199901.
This is line 11.
This function is main
This function is why_me
This is line 21.
```

### `#line和#error`指令

`#line`指令重置`__LINE__`和`__FILE__`宏报告的行号和文件名。可以这样使用`#line`:

```c
#line 1000    //把当前行号重置为1000
#line 10 "cool.c"  //把行号重置为10，把文件名重置为cool.c
```

`#error`指令让预处理器发出一条错误信息，该信息包含指令中的文本。如果可能的话，编译过程应该中断。可以这样使用`#error`指令：

```c
#if __STDC_VERSION_!=201112L
#error Not C11

#endif
```

编译以上代码后，输出如下：

```tex
$ gcc newish.c
newish.c:14:2: error: #error Not C11
$ gcc -std=c11 newish.c
$
```

如果编译器支持旧版标准，则会编译失败，如果支持C11标准，就能成功编译。

----

参考资料：

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

[2] C语言条件编译及编译预处理阶段.--[来源](http://www.cnblogs.com/rusty/archive/2011/03/27/1996806.html)

