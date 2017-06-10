# C语言的单字符IO之getchar()和putchar()

<center>

<img src="image\世界上最快乐的事情-为理想而奋斗.jpg">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E8%BF%BD%E6%B1%82%E6%A2%A6%E6%83%B3&step_word=&hs=0&pn=2&spn=0&di=131400609010&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=3286105078%2C2178813062&os=2853443179%2C2251729226&simid=3519456875%2C270312725&adpicid=0&lpn=0&ln=1931&fr=&fmq=1497074787143_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fuploads.xuexila.com%2Fallimg%2F1607%2F748-160F1102236.png&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bx7jxtsw_z%26e3Bv54AzdH3F37ztAzdH3Fzijg2gjgstwg2AzdH3Flll080_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

## 引言

getchar()和putchar()每次只处理一个字符。你可能认为这种方法很低级，与我们的阅读方式相差甚远。但是，这种方法很适合计算机，而且这是绝大多数文本处理程序所用的核心方法。

## 示例分析

```c
/* echo.c -- repeats input */
#include <stdio.h>
int main(void)
{
    char ch;
    
    while ((ch = getchar()) != '#')
        putchar(ch);
    
    return 0;
}
```

该程序获取键盘输入的字符，并把这些字符发送到屏幕上。程序使用while循环，当读到`#`字符是停止。

自从ANSI C标准发布以后，c就把stdio.h头文件与使用getchar()和putchar()相关联，因此程序中要包含这个头文件（其实，getchar()和putchar()都不是真正的函数，它们被定义为供预处理器使用的宏）。运行程序后，与用户的交互如下：

```tex
Hello,there. I would[用户输入]
Hello,there. I would
like a #3 bag of potatoes.[用户输入]
like a
```

为什么输入的字符能直接在屏幕上显示？如果用一个特殊字符（如，`#`）来结束输入，就无法在文本中使用这个字符，是否有更好的方法输入？要回答这些问题，首先要了解C程序如何处理键盘输入，尤其是缓冲和标准输入文件的概念。

## 缓冲区

如果在一些老式系统运行上面的程序，你输入的文本时可能显示如下

```tex
HHeelllloo,,tthheerree..  II  wwoouulldd
lliikkee  aa  #
```

像这样回显用户输入的字符后立即打印重复打印该字符属于**无缓冲（或直接）输入**，即正在等待的程序可立即使用输入的字符。对于该例，大部分系统用户按下Enter键之前不会重复打印刚输入的字符，这种输入形式属于**缓冲输入**。用户输入的字符被收集并存储在一个被称为缓冲区的临时存储区，按下ENTER键后，程序才可使用用户输入的字符。如下图所示，

<center> 

<img src="image\缓冲输入与无缓冲输入.jpg" width="600">

*无缓冲输入与缓冲输入-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=c%E8%AF%AD%E8%A8%80%E7%BC%93%E5%86%B2%E5%8C%BA&step_word=&hs=0&pn=6&spn=0&di=54203898870&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=2977977399%2C1079527774&os=652229332%2C3919087931&simid=3428592226%2C328931452&adpicid=0&lpn=0&ln=1435&fr=&fmq=1497072835520_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fimages.cnitblog.com%2Fi%2F550026%2F201406%2F102336220615420.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Biw525g237_z%26e3BgjpAzdH3Fw6pAzdH3Fdml9898&gsm=0&rpstart=0&rpnum=0)*

</center>

为什么要有缓冲区？首先，把若干字符作为一个块进行传输比逐个发送这些字符节约时间。其次，如果用户打错字符，可以直接通过键盘修正错误。当最后按下ENTER键时，传输的是正确的输入。

缓冲输入有这么多好处，为什么还要使用无缓冲输入呢？因为一些交互式程序需要无缓冲输入。例如，在游戏中，你希望按下一个键就执行相应的指令。当你玩LOL的时候不会希望每次放技能都要按下ENTER，你的英雄才动作吧！！！因此缓冲输入与无缓冲输出都有用武之地。

缓冲分两类：**完全缓冲I/O和行缓冲I/O。**完全缓冲输入指的是当缓冲区填被满时才刷新缓冲区（内容被发送至目的地），通常出现在文件输入中。缓冲区的大小取决于系统，常见的大小是512字节和4096字节。行缓冲I/O指的是在出现换行符时刷新缓冲区，键盘输入通常是行缓冲输入，所以按下ENTER键后才刷新缓冲区。

那么使用缓冲输入还是无缓冲输入？ANSI C和后续的C标准都规定输入是缓冲的，不过最初K&R把这个决定权交给了编译器的编写者。

ANSI 没有提供调用无缓冲输入的标准方式，这意味着是否能进行无缓冲输入取决于计算机系统。



---

参考资料：

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.