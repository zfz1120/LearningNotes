# C语言的fopen()函数

</center>

<img src="image\逝者如斯夫不舍昼夜.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%8F%A4%E4%BB%A3%E5%90%8D%E8%A8%80&step_word=&hs=0&pn=43&spn=0&di=74374024670&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=3530093812%2C164428501&os=2387686965%2C984368008&simid=0%2C0&adpicid=0&lpn=0&ln=1949&fr=&fmq=1497243663101_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fimg.ishuo.cn%2Fdoc%2F1610%2F883-16101QJ247.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Ftfi75_z%26e3BvgAzdH3Ff7k3jvpAzdH3Fkevj27_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

fopen()的声明在头文件：#include <stdio.h>

fopen()是一个常用的函数，用来以指定的方式打开文件，其原型为：
​    FILE * fopen(const char * path, const char * mode);

【参数】path为包含了路径的文件名，mode为文件打开方式（模式）。

<center>

表1 fopen()的模式字符串

</center>



| 打开方式                                     | 说明                                       |
| ---------------------------------------- | ---------------------------------------- |
| "r"                                      | 以读模式打开文件                                 |
| "w"                                      | 以写模式打开，把现有文件的长度截为0，如果文件不存在，则创建一个新文件      |
| "a"                                      | 以写模式打开文件，在现有文件末尾添加内容，如果文件不存在，则创建一个新文件    |
| "r+"                                     | 以更新模式打开文件，允许读和写。                         |
| "w+"                                     | 以更新模式打开文件，允许读和写。如果文件存在则将其长度截为0；如果文件不存在，则创建一个新文件。 |
| "a+"                                     | 以更新模式打开文件，允许读和写，在现有文件的末尾添加内容，如果文件不存在则创建一个新文件；可以读整个文件，但是只能从末尾添加内容 |
| "rb", "wb", “ab", ab+", “a+b”, "wb+", "w+b", "ab+", "a+b" | 与上一个模式类似，但是以二进制模式而不是文本莫斯打开文件             |
| "wx", "wbx", "w+x", "wb+x"或"w+bx"        | (C11)类似非x模式，但是是如果文件已存在或以独占模式打开文件时，则打开文件失败。 |

像UNIX和linux这样只有一种文件类型的系统，带b字母的模式和不带b字母的模式相同。新的C11新增了x字母，与以前的写模式相比具有更多特性。第一，如果以传统的一种写模式打开一个现有文件，fopen()会把文件截为0，这样就丢失了该文件的内容。但是使用x字母的写模式，即使fopen()操作失败，源文件的内容也不会被删除。第二，如果环境允许，x模式的独占特性使得其他程序或线程无法访问正在被打开的文件。

特别注意，**如果使用人也一种"w"模式（不带x字母）打开一个现有文件，该文件的内容会被删除，以便程序在一个空白文件中操作。然而，如果使用带x字母的任何一种模式，将无法打开一个现有的文件。**

示例:

```c
/* count.c -- using standard I/O */
#include <stdio.h>
#include <stdlib.h> // exit() prototype

int main(int argc, char *argv[])
{
    int ch;         // place to store each character as read
    FILE *fp;       // "file pointer"
    unsigned long count = 0;
    if (argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("Can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    while ((ch = getc(fp)) != EOF)
    {
        putc(ch,stdout);  // same as putchar(ch);
        count++;
    }
    fclose(fp);
    printf("File %s has %lu characters\n", argv[1], count);
    
    return 0;
}
```

该程序使用fopen()函数打开文件。程序成功打开文件后，fopen()将返回文件指针，其他I/O函数可以使用这个指针指定该文件。文件指针的类型指向FILE的指针，FILE是一个定义在stdio.h中的派生类型。文件指针fp并不指向实际的文件，它指向一个包含文件信息的数据对象，其中包含操作文件IO函数所用的缓冲区信息。因为标准库中的IO函数使用缓冲区，所以它们不仅要知道缓冲区的位置，还要知道缓冲区被填充的程度以及操作哪一个文件。标准IO函数根据这些信息在必要时决定再次填充或清空缓冲区。fp指向的数据对象包含了这些信息（该数据对象是一个C结构）。

---

参考资料：

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.