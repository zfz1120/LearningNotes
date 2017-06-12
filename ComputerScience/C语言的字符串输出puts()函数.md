# C语言的字符串输出puts()函数

<center>

<img src="image\保持好奇心努力前行.jpg">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E4%BF%9D%E6%8C%81%E5%A5%BD%E5%A5%87%E5%BF%83&step_word=&hs=0&pn=1&spn=0&di=30942920140&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=4140942727%2C253301267&os=258903026%2C1051164876&simid=3564746899%2C327977403&adpicid=0&lpn=0&ln=1973&fr=&fmq=1497169580356_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fimg.zcool.cn%2Fcommunity%2F013738554408b70000019ae9f1019c.jpg%40900w_1l_2o_100sh.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bzv55s_z%26e3Bv54_z%26e3BvgAzdH3Fo56hAzdH3FZNDhnNz2xN2%3D%3D_z%26e3Bip4s%3FfotpviPw2j%3D5g&gsm=0&rpstart=0&rpnum=0)*

</center>

puts()函数很容易用，只需把字符串地址作作为参数传递给它就可以了。

puts()函数有两个特点:

- puts()在显示字符串时会自动在其末尾添加一个换行符。
- puts()遇到空字符时就停止输出，所以必须确保有空字符。

下面两个示例分别说明puts()的两个特点。

示例1：

```c
/* put_out.c -- using puts() */
#include <stdio.h>
#define DEF "I am a #defined string."
int main(void)
{
    char str1[80] = "An array was initialized to me.";
    const char * str2 = "A pointer was initialized to me.";
    
    puts("I'm an argument to puts().");
    puts(DEF);
    puts(str1);
    puts(str2);
    puts(&str1[5]);
    puts(str2+4);
    
    return 0;
}
```

该程序的输出如下：

```tex
I'm an argument to puts().
I am a #defined string.
An array was initialized to me.
A pointer was initialized to me.
ray was initialized to me.
inter was initialized to me.
```

如上所示，每个字符串独占一行，因为puts()在显示字符串时会自动在其末尾添加一个换行符。

示例2：

```c
/* nono.c -- no! */
#include <stdio.h>
int main(void)
{
    char side_a[] = "Side A";
    char dont[] = {'W', 'O', 'W', '!' };
    char side_b[] = "Side B";
    
    puts(dont);   /* dont is not a string */
    
    return 0;
}
```

下面是该程序的一个示例，可能每次运行结果都不一样，不同的编译器输出的内容有可能不同：

```
WOW!Side A
```

puts()如何知道在何处停止？该函数遇到空字符时就停止输出。由于dont缺少一个表示结束的空字符，所以它不是一个字符串，因此puts()不知道何处停止。它会一直打印dont后面内存中的内容，直到发现一个空字符为止。为了让puts()能尽快读到空字符，我们把dont放在side_a和side_b之间，上面是该程序的一个运行示例，不同的编译器输出的内容有可能不同

通常内存中有许多空字符，如果幸运的话，puts()很快就会发现一个。但是这样做是不靠谱的！



---

参考资料：

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016. 