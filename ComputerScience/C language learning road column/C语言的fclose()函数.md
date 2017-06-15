# C语言的fclose()函数

<center>

<img src="image\傻逼似的坚持.jpg">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%91%BD%E8%BF%90%E7%9A%84%E6%A0%BC%E8%A8%80&step_word=&hs=0&pn=2&spn=0&di=31746260810&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=3170992509%2C733633694&os=1836302041%2C690267241&simid=3383561552%2C517246764&adpicid=0&lpn=0&ln=1984&fr=&fmq=1497247887248_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fwww.mingyanb.com%2FupFiles%2FinfoImg%2F2016020555055005.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bz75ojgziwt_z%26e3Bv54AzdH3Fyw5-8mb0l99_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

头文件：`#include <stdio.h>`

定义函数：`int fclose(FILE * stream);`

**函数说明：fclose()用来关闭先前fopen()打开的文件。此动作会让缓冲区内的数据写入文件中, 并释放系统所提供的文件资源。必要时刷新缓冲区。**

对于比较正式的程序，应该检查是否成功关闭文件。如果成功关闭，fclose()函数返回0，否则返回EOF：

```c
if (fclose(fp) != 0)
  printf("Error in closing file %s\n",argv[1]);
```

如果磁盘已满、移动硬盘被移除或出现I/O错误，都会导致调用fclose()函数失败。

**错误代码：EBADF 表示参数stream 非已打开的文件。**

示例请参考前面的博客《 [C语言的fopen()函数](http://blog.csdn.net/libing403/article/details/73136244)》。



---

参考资料：

[1]  史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

[2] C语言fclose()函数：关闭打开的文件-[来源](http://c.biancheng.net/cpp/html/243.html)