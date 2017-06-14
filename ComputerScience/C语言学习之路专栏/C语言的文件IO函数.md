# C语言的文件IO函数

<center>

<img src="image\若前行就离开停留的地方.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E7%A7%AF%E7%B4%AF%E7%9A%84%E5%90%8D%E8%A8%80&step_word=&hs=0&pn=91&spn=0&di=23902620610&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=625341128%2C2723326764&os=3510212159%2C2997362117&simid=4163893891%2C724591213&adpicid=0&lpn=0&ln=1953&fr=&fmq=1497251287007_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fuploads.xuexila.com%2Fallimg%2F1601%2F676-160123111942312.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bx7jxtsw_z%26e3Bv54AzdH3Ff7vvjffAzdH3Fs52t5gAzdH3F9nldn8_z%26e3Bip4s&gsm=3c&rpstart=0&rpnum=0)*

</center>

## 引言

C语言文件I/O函数主要指fprintf()、fscanf()、fgets()和fputs()。它们既可以实现向gets()、puts()、getc()和putc()函数样从键盘和屏幕进行输入输出，也可以对文件进行输入输出。

## fprintf()和fscanf()函数

头文件：`#include <stdio.h>`

定义函数：`int fprintf(FILE * stream, const char * format, ...);`

**函数说明：fprintf()会根据参数format 字符串来转换并格式化数据, 然后将结果输出到参数stream 指定的文件中, 直到出现字符串结束('\0')为止。**

返回值：关于参数format 字符串的格式请参考printf()。 成功则返回实际输出的字符数， 失败则返回-1, 错误原因存于errno 中。

示例：

```c
/* addaword.c -- uses fprintf(), fscanf(), and rewind() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 41

int main(void)
{
    FILE *fp;
    char words[MAX];
    
    if ((fp = fopen("wordy", "a+")) == NULL)
    {
        fprintf(stdout,"Can't open \"wordy\" file.\n");
        exit(EXIT_FAILURE);
    }
    
    puts("Enter words to add to the file; press the #");
    puts("key at the beginning of a line to terminate.");
    while ((fscanf(stdin,"%40s", words) == 1)  && (words[0] != '#'))
        fprintf(fp, "%s\n", words);
    
    puts("File contents:");
    rewind(fp);           /* go back to beginning of file */
    while (fscanf(fp,"%s",words) == 1)
        puts(words);
    puts("Done!");
    if (fclose(fp) != 0)
        fprintf(stderr,"Error closing file\n");
    
    return 0;
}
```

该程序可以在文件中添加单词。使用"a+"模式，程序可以对文件进行读写操作。首次使用该程序，它将创建wordy文件，以便把单词存入其中。随后再使用该程序，可以在wordy文件后面添加单词。虽然"a+"模式只允许在文件末尾添加内容，但是该文件模式可以读整个文件。rewind()函数让程序回到文件开始处，方便while循环打印整个文件的内容。注意，rewind()接受一个文件指针作为参数。

下面是在Cygwin在windows下模拟的linux环境下运行示例(可执行程序名字为a.exe)：

```tex
$ ./a.exe[第一次运行]
Enter words to add to the file; press the #
key at the beginning of a line to terminate.
The fabulous programmer
#
File contents:
The
fabulous
programmer
Done!
$ ./a.exe[第二次运行]
Enter words to add to the file; press the #
key at the beginning of a line to terminate.
enchanted the
large
#
File contents:
The
fabulous
programmer
enchanted
the
large
Done!
```

## fgets()和fputs()函数

这两个函数的分析可以参考前面的博客《[C语言的字符串输入fgets()函数](http://blog.csdn.net/libing403/article/details/73012280)》和《[C语言的字符串输出fputs()函数](http://blog.csdn.net/libing403/article/details/73083411)》。

---

参考资料：

[1]  史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

[2] C语言fprintf()函数：输出函数(格式化输出数据至文件-[来源](http://c.biancheng.net/cpp/html/291.html)

