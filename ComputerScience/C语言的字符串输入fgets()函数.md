# C语言的字符串输入fgets()函数

<center>

<img src="image\追寻梦想的脚步.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E8%BF%BD%E6%B1%82%E6%A2%A6%E6%83%B3&step_word=&hs=0&pn=1&spn=0&di=15460138650&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=1184591316%2C562079715&os=1234365539%2C437519987&simid=3520337685%2C226506682&adpicid=0&lpn=0&ln=1931&fr=&fmq=1497092067188_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fs6.sinaimg.cn%2Fmiddle%2F9af5d35bxb7de282e3e35%26690&fromurl=ippr_z2C%24qAzdH3FAzdH3Fks52_z%26e3Bftgw_z%26e3Bv54_z%26e3BvgAzdH3FfAzdH3Fks52_lwuc1ncka8aaosql_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

## fgets()函数简介

读字符串函数fgets函数的功能是从指定的文件中读一个字符串到字符数组中，函数调用的形式为： fgets(字符数组名，n，文件指针)，要从键盘输入时文件指针的参数为：stdin ； 其中的n是一个正整数。表示从文件中读出的字符串不超过 n-1个字符。在读入的最后一个字符后加上串结束标志`'/0'`。

## 示例分析

fgets()函数通过2个参数限制读入的字符数来解决溢出的问题。该函数专门设计用于处理文件输入，所以一般情况下可能不太好用。fgets()和gets()的区别如下：

- fgets()函数的第2个参数指明了读入字符的最大数量。如果该参数的值是n，那么fgets()将读入n-1个字符，或者读到遇到第一个换行符为止。
- 如果fgets()读到一个换行符，会把它存储在字符串中。这点与gets()不同，gets()会丢弃换行符。
- fgets()函数的第三个参数指明要读入的文件。如果读入从键盘输入的数据，则以stdin(标准输入)作为参数，该标识定义在stdio.h中。

因为fgets()函数把换行符放在字符串的末尾(假设输入行不溢出)，通常要与fputs()函数（与puts()类似）配对使用，除非该函数不在字符串末尾添加换行符。fgets()函数的第2个采纳数指明它要写入的文件，如果要显示在计算机显示器上，应使用stdout(标准输出)作为该参数。

下面是一个示例：

```c
/*  fgets1.c  -- using fgets() and fputs() */
#include <stdio.h>
#define STLEN 14
int main(void)
{
    char words[STLEN];
    
    puts("Enter a string, please.");
    fgets(words, STLEN, stdin);
    printf("Your string twice (puts(), then fputs()):\n");
    puts(words);
    fputs(words, stdout);
    puts("Enter another string, please.");
    fgets(words, STLEN, stdin);
    printf("Your string twice (puts(), then fputs()):\n");
    puts(words);
    fputs(words, stdout);
    puts("Done.");
    
    return 0;
}
```

下面是该程序的输出示例:

```tex
Enter a string, please.
apple pie[用户输入]
Your string twice (puts(), then fputs()):
apple pie

apple pie
Enter another string, please.
strawberry shortcake[用户输入]
Your string twice (puts(), then fputs()):
strawberry sh
strawberry shDone.
```

第一行输入，当puts()显示该字符串时又在末尾添加了换行符。因此，`apple pie`后面有一行空行。因为fputs()不在末尾添加换行符，所以未打印出空行。

第二行输入，`strawberry shortcake`，超出了大小的限制。所以fgets()只读入13个字符，并把`strawberry sh\0`存储在数组中。再次注意，puts()函数会在带输出的字符串后面添加一个换行符，而fputs()不会这样做。

如果函数fgets()读到文件结尾，它将返回一个**空指针（null pointer）**。空指针，在代码中可以用0代替，不过在C语言中用宏NULL来代替更常见。

## 进一步理解

看下面示例：

```c
/*  fgets2.c  -- using fgets() and fputs() */
#include <stdio.h>
#define STLEN 10
int main(void)
{
    char words[STLEN];
    
    puts("Enter strings (empty line to quit):");
    while (fgets(words, STLEN, stdin) != NULL && words[0] != '\n')
        fputs(words, stdout);
    puts("Done.");
    
    return 0;
}
```

下面是该程序的输出示例：

```tex
Enter strings (empty line to quit):
By the way, the gets() function
By the way, the gets() function
also returns a null pointer if it
also returns a null pointer if it
encounters end-of-file.
encounters end-of-file.

Done.
```

奇怪，该程序似乎在处理过长的输入时完全没问题。解释如下，

程序中的fgets()一次性读入9个字符。所以一开始它只读入`"By the wa"`，并存储为`By the wa\0`；接着fputs()打印该字符串，**而且未换行**。然后while循环进入下一轮迭代，fgets()从剩余的输入中读入数据，即读入`y, the ge`并存储为`y, the ge\0`；接着fputs()在刚才打印字符串**这一行**接着打印第2次读入的字符串。然后while进入下一轮迭代，fgets()继续读取输入，fgets()打印字符串。直到读到换行符。

系统使用缓冲的I/O。这意味着用户按下ENTER键之前，输入都被存储在临时存储区（即，缓冲区），按下ENTER键就在输入中增加一个换行符，并把整行输入发给fgets()。对于输出，fputs()把字符串发送给另一个缓冲区，但发送换行符时，缓冲区中的内容被发送至屏幕。



----

参考资料：

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016. 