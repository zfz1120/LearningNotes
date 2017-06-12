# C语言的getc()和putc()函数

<center>

<img src="image\科学上没有平坦的大道.jpg">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E7%A7%91%E5%AD%A6%E5%90%8D%E8%A8%80&step_word=&hs=0&pn=6&spn=0&di=75968833380&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=3837380884%2C376382761&os=1523463490%2C1552000945&simid=3348108508%2C133155159&adpicid=0&lpn=0&ln=1961&fr=&fmq=1497246464853_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fp.ananas.chaoxing.com%2Fstar%2F1024_0%2F1384495290156frlky.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3F455v_z%26e3Bviw5xtg2_z%26e3Bv54AzdH3Fv576fjAzdH3Fcamba8_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

getc()和putc()函数与getchar()和putchar()函数类似。不同的是，要告诉getc()和putc()函数使用哪一个文件。

下面这条语句的意思是"从标准输入中获取一个字符"：

`ch=putchar();`

然而，下面这条语句的意思是“从fp指定的文件中获取一个字符”：

`ch=putc(fp);`

类似地，下面语句的意思是"把字符ch放入FILE指针fpout指定的文件中"：

`putc(ch,fpout);`

实际上，putchar()函数一般通过putc()来定义，getchar()也通过使用标准输入的getc()来定义。



----

参考资料：

[1]  史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.