# C语言的命令行参数

<center>

<img src="image\追求卓越成功就会.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E8%BF%BD%E6%B1%82%E5%8D%93%E8%B6%8A%20%E6%88%90%E5%8A%9F%E5%B0%B1%E4%BC%9A%E5%9C%A8%E4%B8%8D%E7%BB%8F%E6%84%8F%E9%97%B4%E8%BF%BD%E4%B8%8A%E4%BD%A0&step_word=&hs=0&pn=0&spn=0&di=199091543970&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=4264245545%2C2304686236&os=1151173486%2C1319766404&simid=0%2C0&adpicid=0&lpn=0&ln=1980&fr=&fmq=1497630242793_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fimg4q.duitang.com%2Fuploads%2Fitem%2F201306%2F05%2F20130605224934_N2W2P.thumb.700_0.jpeg&fromurl=ippr_z2C%24qAzdH3FAzdH3F4_z%26e3B17tpwg2_z%26e3Bv54AzdH3Frj5rsjAzdH3F4ks52AzdH3F888l0mmnbAzdH3F1jpwtsAzdH3F%3Fr6j%3D888l0mmnb&gsm=0&rpstart=0&rpnum=0)*

</center>

在图形界面普及前都是用命令行界面。命令行(command line)是在命令行环境中，用户为运行程序输入命令的行。命令行函数(command-line argument)是同一行的附加项。如下例是unix环境下的命令行：

```shell
$ fuss -r Ginger
```

fuss就是命令行，后面的是命令行参数。例如在windows中常用的查看ip地址的命令

```shell
C> ipconfig /all
```

ipconfig是命令行，后面的是参数。

**一个C程序可以读取并使用这些附加项。**

示例：

```c
/* repeat.c -- main() with arguments */
#include <stdio.h>
int main(int argc, char *argv[])
{
    int count;
    
    printf("The command line has %d arguments:\n", argc - 1);
    for (count = 1; count < argc; count++)
        printf("%d: %s\n", count, argv[count]);
    printf("\n");
    
    return 0;
}
```

把该程序编译为可执行程序repeat。下面是通过命令行运行该程序后的输出：

```shell
$ ./repeat.exe  Resistance is futile
The command line has 3 arguments:
1: Resistance
2: is
3: futile
```

我这里的运行环境是windows下Cygwin模拟的命令终端的运行结果。其他环境输出结果是一样的。

**运行原理：**

C编译器允许main()函数没有参数或两个参数（一些实现允许main()有更多参数，属于对标准的拓展）。main()有两个参数，第一个参数是命令行中的字符串。过去，这个int类型的参数被称为argc（表示参数计数（argument count））。系统用空格表示一个字符串的结束和下一个字符串的开始。

上面的程序的命令行有4个字符串，第1个是命令名。后面3个是命令行参数，供repeat使用。main()的第2个参数，是指向指针的指针，称为argv（表示参数值（argument value）），他存储了指向这4个字符串的地址。如下

argv[0] 指向 repeat（大部分系统而言）

argv[1]指向 Resistance

argv[2]指向 is

argv[3]指向 futile

main()中的形参形式与其他带形参的函数相同，argv也可以这样声明

`int main(int arc, char **argv);`

另外，许多环境（包括UNIX和DOS）都允许用双引号把多个单词括起来形成一个参数。例如：

`repeart  "I am hungry"  now`

这行命令把 "I am hungry"赋值给argv[1]，把"now"赋给argv[2]。



----

参考文献：

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

