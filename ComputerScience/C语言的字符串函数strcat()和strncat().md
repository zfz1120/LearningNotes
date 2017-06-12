# C语言的字符串函数strcat()和strncat()

<center>

<img src="image\追求梦想我在路上.jpg">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E8%BF%BD%E6%B1%82%E6%A2%A6%E6%83%B3&step_word=&hs=0&pn=13&spn=0&di=100106162090&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=1319554446%2C978586751&os=3961210511%2C4094817469&simid=3339762138%2C437280692&adpicid=0&lpn=0&ln=1978&fr=&fmq=1497226880721_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fs14.sinaimg.cn%2Fmw690%2F005JjIiJgy6N2nqeszP6d%26690&fromurl=ippr_z2C%24qAzdH3FAzdH3Fks52_z%26e3Bftgw_z%26e3Bv54_z%26e3BvgAzdH3FfAzdH3Fks52_8nbu8du18a8adecyd_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

## strcat() 函数简介

strcat() 函数用来连接字符串，其原型为：
​    char *strcat(char *dest, const char *src);

【参数】dest 为目的字符串指针，src 为源字符串指针。

strcat() 会将参数 src 指向的字符串复制到参数 dest 所指的字符串尾部；dest 最后的结束字符 NULL 会被覆盖掉，并在连接后的字符串的尾部再增加一个 NULL。把拼接后形成的字符串作为第一个字符串，第二个字符串保持不变。strcat()返回第一个参数，即拼接第二个字符串后的第一个字符串的地址。

注意：dest 与 src 所指的内存空间不能重叠，且 dest 要有足够的空间来容纳要复制的字符串。

## 示例分析：

```c
/* str_cat.c -- joins two strings */
#include <stdio.h>
#include <string.h>  /* declares the strcat() function */
#define SIZE 80
char * s_gets(char * st, int n);
int main(void)
{
    char flower[SIZE];
    char addon[] = "s smell like old shoes.";
    
    puts("What is your favorite flower?");
    if (s_gets(flower, SIZE))
    {
        strcat(flower, addon);
        puts(flower);
        puts(addon);
    }
    else
        puts("End of file encountered!");
    puts("bye");


    return 0;
}


char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;
    
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else // must have words[i] == '\0'
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}
```

该程序的输出示例如下：

```tex
What is your favorite flower?
wonderflower[用户输入]
wonderflowers smell like old shoes.
s smell like old shoes.
bye
```

s_gets()函数的作用是，使用fgets()读取一整行，如果有换行符，就将其替换掉。

从上面的输出可以看出，flower改变了，而addon保持不变。

## strncat()函数简介



strncat()用于将n个字符追加到字符串的结尾，其原型为：
​    char * strncat(char *dest, const char *src, size_t n);

【参数说明】dest为目标字符串，src为源字符串，n为要追加的字符的数目。

strncat()将会从字符串src的开头拷贝n 个字符到dest字符串尾部，dest要有足够的空间来容纳要拷贝的字符串。如果n大于字符串src的长度，那么仅将src全部追加到dest的尾部。

strncat()会将dest字符串最后的'\0'覆盖掉，字符追加完成后，再追加'\0'。

【返回值】返回字符串dest。

例如，strncat(bugs, addon 13)将把addon字符串内容附加给bugs，在加到第13个字符或遇到空字符时就停止。注意拼接后的字符串长度加1才能够空间存放末尾的空字符。

## 示例分析

```c
/* join_chk.c -- joins two strings, check size first */
#include <stdio.h>
#include <string.h>
#define SIZE 30
#define BUGSIZE 13
char * s_gets(char * st, int n);
int main(void)
{
    char flower[SIZE];
    char addon[] = "s smell like old shoes.";
    char bug[BUGSIZE];
    int available;
    
    puts("What is your favorite flower?");
    s_gets(flower, SIZE);
    if ((strlen(addon) + strlen(flower) + 1) <= SIZE)
        strcat(flower, addon);
    puts(flower);
    puts("What is your favorite bug?");
    s_gets(bug, BUGSIZE);
    available = BUGSIZE - strlen(bug) - 1;
    strncat(bug, addon, available);
    puts(bug);
    
    return 0;
}
char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;
    
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else // must have words[i] == '\0'
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}
```

```tex
What is your favorite flower?
Rose[用户输入]
Roses smell like old shoes.
What is your favorite bug?
Aphid[用户输入]
Aphids smell
```

strcat()和gets()类似，也会导致缓冲区溢出。为什么C11标准不废弃strcat()，只留下strncat()?为何对gets()那么残忍？这因为gets()造成的安全隐患来自使用该程序的人，而strcat()暴露的问题是那些粗心的程序员造成的。无法控制用户进行什么操作，但是可以控制你的程序做什么。C语言相信程序员，因此程序员有责任确保strcat()的使用安全。



---

参考资料:

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

[2] C语言strcat()函数：连接字符串-[来源](http://c.biancheng.net/cpp/html/160.html)

[3] C语言strncat()函数：在字符串的结尾追加n个字符-[来源](http://c.biancheng.net/cpp/html/169.htm) 

