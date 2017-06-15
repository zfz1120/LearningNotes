# C语言的文件随机访问fseek()和ftell()函数

<center>

<img src="image\不忘初心方得始终.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%8A%B1%E5%BF%97%E8%AF%97&step_word=&hs=0&pn=2&spn=0&di=140581925770&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=2708893485%2C688688996&os=1237721892%2C806204908&simid=3500724194%2C430949748&adpicid=0&lpn=0&ln=871&fr=&fmq=1497261964253_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fwww.23book.com%2Fupload%2F2016%2F02%2F01%2Fe3ae41bc-f996-4677-b588-c0b546c0dd67.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bdnk55h_z%26e3Bv54AzdH3F89aaaaAzdH3F8ndcc9_z%26e3Bfip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

我们要讨论3个问题：fseek()和ftell()函数的工作原理、如何使用二进制流、如何让程序可移植。

## fseek()与ftell()的工作原理

头文件：`#include <stdio.h>`

定义函数：`int fseek(FILE * stream, long offset, int whence);`

**函数说明：fseek()用来移动文件流的读写位置. **

1.参数stream 为已打开的文件指针。

2.参数offset 是偏移量，该参数表示要从起始点开始要移动的距离，干参数必须是一个long类型的值，可以为正(前移)，可以为负(向后移)，或者为0(保持不动)。

3.参数 whence 是模式，该参数确定起始点。根据ANSI标准，在stdio.h头文件中规定了几个表示模式的**明示标量(manifest constant)。**如下表所示：

<center>

表1 文件的起始点模式

</center>

| 模式       | 偏移量的起始点 |
| -------- | ------- |
| SEEK_SET | 文件开始处   |
| SEEK_CUT | 文件当前位置  |
| SEEK_END | 文件末尾    |

旧的实现可能缺少这些定义，可以用数值0L、1L、2L分别表示这3中模式。L表明其值是long类型。

下面是调用fseek()函数的一些示例，fp是一个文件指针：

```c
fseek(fp, 0L, SEEK_SET);       //定位至文件开始处
fseek(fp, 10L, SEEK_SET);      //定位至文件中的第10个字节
fseek(fp, 2L， SEEK_CUR);      //从文件当前位置前移2个字节
fseek(fp, 0L, SEEK_END);       //定位至文件结尾
fseek(fp, -10, SEEK_END);      //从文件结尾处回退10个字节
```

对于这些调用还有一些限制，后面会讨论。如果一切正常，fseek函数的返回值为0；如果出现错误(例如试图移动的距离超出了文件的范围），其返回值是-1。

ftell() 函数用来获取文件读写指针的当前位置，其原型为：
   ` long ftell(FILE * stream);`

【参数】stream 为已打开的文件指针。

【返回值】成功则返回当前的读写位置，失败返回 -1。

对于二进制文件，则返回从文件开头到结尾的字节数。

对于文本文件，返回的数值可能没有实际意义，但仍然可以用来保存当前的读写位置，供 fseek() 函数使用

在随机方式存取文件时，由于文件位置频繁的前后移动，程序不容易确定文件的当前位置。使用fseek函数后再调用函数ftell()就能非常容易地确定文件的当前位置。ftell() 经常和 fseek() 一起使用。

在最初的unix实现中，ftell()通过返回距文件开始处的字节数来确定文件的位置。文件的第1个字节到文件开始处的距离为0，以此类推。ANSI C规定，该定义适用于以二进制模式打开的文件，以文本文件打开的文件的情况不同。

下面来分析以下程序示例：

```c
/* reverse.c -- displays a file in reverse order */
#include <stdio.h>
#include <stdlib.h>
#define CNTL_Z '\032'   /* eof marker in DOS text files */
#define SLEN 81
int main(void)
{
    char file[SLEN];
    char ch;
    FILE *fp;
    long count, last;
    
    puts("Enter the name of the file to be processed:");
    scanf("%80s", file);
    if ((fp = fopen(file,"rb")) == NULL)
    {                               /* read-only mode   */
        printf("reverse can't open %s\n", file);
        exit(EXIT_FAILURE);
    }
    
    fseek(fp, 0L, SEEK_END);        /* go to end of file */
    last = ftell(fp);
    for (count = 1L; count <= last; count++)
    {
        fseek(fp, -count, SEEK_END); /* go backward      */
        ch = getc(fp);
		if (ch != CNTL_Z && ch != '\r')  /* MS-DOS files */
            putchar(ch);
    }
    putchar('\n');
    fclose(fp);
    
    return 0;
}
```

下面是该程序对一个文件的输出：

```tex
Enter the name of the file to be processed:
Cluv[用户输入]

.C ni naht ylevol erom margorp a
ees reven llahs I taht kniht I

```

注意，运行程序前先在可执行程序的目录下准备一个叫Cluv的文件，里面存有以下内容，才可能得到上面的输出（笔者是在windows下Cygwin模拟的Linux环境下运行）。

```tex
I think that I shall never see
a program more lovely than in C.
```

该程序使用二进制模式，以便处理MS-DOS文本和UNIX文本。但是，是在使用其他格式的文本文件的环境可能无法正常工作。

首先，分析下面的语句：

​    `fseek(fp, 0L, SEEK_END); `

把当前位置设置为距文件末尾0字节偏移量。也就是说，该语句把当前位置设置在文件结尾。下一条语句：

`last=ftell(fp);`

把文件开始到文件结尾的字节数赋值给last。

然后是一个for循环：

```c
    for (count = 1L; count <= last; count++)
    {
        fseek(fp, -count, SEEK_END); /* go backward      */
        ch = getc(fp);
		if (ch != CNTL_Z && ch != '\r')  /* MS-DOS files */
            putchar(ch);
    }
```

第一轮迭代，把程序定位到文件结尾的第一个字符(即文件的最后一个字符)。然后，长须打印该字符。然后，程序打印该字符。下一轮迭代把程序定位到前一个字符，并打印该字符。重复这一过程直到文件的第一个字符，并打印。

## 二进制模式和文本模式

上面的示例程序在UNIX和MS-DOS环境下都可以运行。UNIX只有一种文件格式，所以不需要进行特殊的转换。但是MS-DOS要格外注意，许多MS-DOS编辑器都用Ctrl+Z标记文本文件的结尾。以文本模式打开这样的文件时，C能识别这个作为文件结尾标记的字符。但是，以二进制模式打开文件时，Ctrl+Z字符被看做文件中的一个字符，而实际的文件结尾符在该字符的后面。文件结尾符可能紧跟Ctrl+Z字符后面，或者文件中可能用空字符填充，使该文件的大小是256的倍数。在DOS环境下不会打印空字符，上面程序就包含了贩子打印Ctrl+Z字符的代码。

二进制模式和文本模式的另一个不同之处是：MS-DOS用\r\n组合表示文本文件换行。以文本模式打开相同的文件时，C程序把`\r\n`“看成”是`\n`。但是，以二进制模式打开该文件时，程序能看见这两个字符。因此，上面的程序还包含了不打印`\r`的代码。通常UNIX文本文件既没有Ctrl+Z，也没有`\r`，所以这部分代码不会影响大部分UNIX文本文件。

ftell函数在文本模式和二进制模式中的工作方式不同。许多系统的文本文件格式与UNIX的模型有很大的不同，导致从文件开始处统计的字节数称为一个毫无意义的值。ANSI C规定，对与文本模式，ftell()返回值可以作为fseek()的第2个参数。对于MS-DOS，ftell()返回值把`\r\n`当做一个字符计数。

## 可移植性

理论上，fseek()和ftell()应该符合UNIX模型，但是，不同系统存在着差异，有时确实无法做到与UNIX模型一致。因此，ANSI 对这些函数降低了要求。下面是一些限制

- 在二进制中，实现不必支持SEEK_END模式。因此无法保证上面的程序的可移植性。移植性更高的方法是逐字节读取整个文件直到文件末尾。C预处理器的条件编译指令提供了一种系统方法处理这种情况。
- 在文本模式中，只有以下调用能保证其相应的行为。

| 函数调用                            | 效果                                       |
| ------------------------------- | ---------------------------------------- |
| `fseek(file, 0L, SEEK_SET)`     | 定位至文件开始处                                 |
| fseek(file, 0L, SEEK_CUR)       | 保持当前位置不动                                 |
| fseek(file, 0L, SEEK_END)       | 定位至文件结尾                                  |
| fseek(file,ftell-pos, SEEK_SET) | 到距文件开始处ftell-pos的位置，ftell-pos是ftell()的返回值 |





-----



参考资料：

[2]  史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

[2] C语言fseek()函数：移动文件流的读写位置。-[来源](http://c.biancheng.net/cpp/html/255.html)

[3] C语言ftell()函数：获取文件读写指针的当前位置。-[来源](http://c.biancheng.net/cpp/html/2519.html)

