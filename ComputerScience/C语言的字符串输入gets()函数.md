# C语言的字符串输入gets()函数

<center>

<img src="image\岁月匆匆人生如梦.jpg">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E6%AF%95%E7%AB%9F%E6%88%91%E4%BB%AC%E5%BA%A6%E8%BF%87%E4%BA%86%E7%B2%BE%E5%BD%A9%E7%9A%84%E4%BA%BA%E7%94%9F&step_word=&hs=0&pn=25&spn=0&di=5250429800&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=2894155057%2C1907719709&os=2436148760%2C1553426305&simid=4261341206%2C860342305&adpicid=0&lpn=0&ln=1967&fr=&fmq=1497081791564_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fs4.sinaimg.cn%2Fbmiddle%2F6de92e19g7556c2d5e763%26690&fromurl=ippr_z2C%24qAzdH3FAzdH3Fks52_z%26e3Bftgw_z%26e3BvgAzdH3F1r55sAzdH3Fks52AzdH3FfAzdH3Fks52_m1jldj8la8aa4hdh_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

## 字符串简介

字符串(character string)是一个或多个字符的序列。如下所示：

```c
"Zing went the strings of my heart!"
```

双引号不是字符串的一部分。双引号告知编译器它括起来的是字符串。C语言没有专门用语存储字符串的变量类型，字符串都被存储在char类型的数组中。字符串常量`"x"`和字符常量`'x'`不同，区别之一在于`'x'`是基本类型（char），而`"x"`是派生类型（char数组）；区别之二是`"x"`实际上由两个字符串组成:`'x'`和空字符`\0`。

## 字符串输入函数gets()

 在c语言中读取字符串有多种方法，比如scanf() 配合%s使用，但是这种方法只能获取一个单词，即遇到空格等空字符就会返回。如果要读取一行字符串，比如：

```tex
I love you!
```

这种情况，scanf()就无能为力了。这时我们最先想到的是用gets()读取.

gets()函数从标准输入（键盘）读入一行数据，所谓读取一行，就是遇到换行符就返回。gets()函数并不读取换行符`'\n'`，它会吧换行符替换成空字符`'\0'`，作为c语言字符串结束的标志。

gets()函数经常和puts()函数配对使用，puts()函数用于显示字符串，并自动在字符串后面添加一个换行标志`'\n'`。

## gets()的缺陷

gets()函数存在一个严重的缺陷，这个缺陷就是：它不会检查数组是否能够装得下输入行。

示例分析：

```c
/*  getsputs.c  -- using gets() and puts() */
#include <stdio.h>
#define STLEN 81
int main(void)
{
    char words[STLEN];
     
    puts("Enter a string, please.");
    gets(words);  // typical use
    printf("Your string twice:\n");
    printf("%s\n", words);
    puts(words);
    puts("Done.");
    
    return 0;
}
```

下面是某些编译器(至少是旧式编译器)中的运行示例：

```tex
Enter a string, please.
I want to learn about string theory![用户输入]
Your string twice:
I want to learn about string theory!
I want to learn about string theory!
Done.
```

下面是在另一个编译器中的输出示例：

```tex
Enter a string, please.
warning:this program uses gets(),which is unsafe.
I want to learn about string theory![用户输入]
Your string twice:
I want to learn about string theory!
I want to learn about string theory!
Done.
```

编译器在输出中插入了一行警告信息。这是怎么回事？问题出在gets()唯一的参数是words，它无法检查是否装得下输入行。数组名会转换成该数组首元素的地址，因此gets()函数只知道数组的开始处，并不知道数组中有多少个元素。

如果输入的字符串过长，会导致**缓冲区溢出(buffer overflow)**，即多余的字符超出了指定的目标空间。gets()函数就会访问未被分配的内存空间，如果这些内存未被使用，不会立即出现问题；如果这片空间已经存有数据，就会擦除掉程序中的其他数据，会导致程序中止。

正式由于gets()函数的这个缺陷，在C99标准中，已经不再建议使用gets()函数，而在C11中更是直接抛弃了这个函数。然而在实际应用中，编译器为了兼容以前的代码，大部分都继续支持gets()函数。

gets()被抛弃，那我们用什么来代替它的功能呢？

C11标准新增了gets_s()函数可以代替gets()函数，但是，该函数是stdio.h输入输出函数系类中的可选扩展，因此，即使编译器支持C11标准，也有可能不支持gets_s()函数。

其实我们可以用c语言中的fgets()函数来代替gets()

接下来的博客会会继续分析其他字符串输入函数。



----

参考资料：

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

[2] 详解C语言gets()函数与它的替代者fgets()函数-http://www.jb51.net/article/93972.htm