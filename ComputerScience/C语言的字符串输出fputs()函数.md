# C语言的字符串输出fputs()函数

<center>

<img src="image\外星探险车.jpg" width="500">

图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E4%BF%9D%E6%8C%81%E5%A5%BD%E5%A5%87%E5%BF%83&step_word=&hs=0&pn=16&spn=0&di=92464598490&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=3924459764%2C4076406821&os=711907378%2C3060571201&simid=3419896386%2C216596881&adpicid=0&lpn=0&ln=1973&fr=&fmq=1497169580356_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fmeterial.gmmc.com.cn%3A8080%2FNews%2F2015%2F0831%2F01%2F01.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3B244v_z%26e3Bv54_z%26e3BvgAzdH3FGQSLHLBEHRDAzdH3FgjofAzdH3FFA08mbAA-maBn-9B8a-bEA0-C9lB8bmEEnCB&gsm=0&rpstart=0&rpnum=0)

</center>

fputs()函数是puts()函数针对文件定制的版本，它们的区别如下：

- fputs()函数的第2个参数指明要写入数据的文件。如果要打印在显示器上，可以用定义在stdio.h中的stdout(标准输出)作为参数。
- 与puts()不同，fputs()不会再输出的末尾添加换行符。

注意，gets()丢弃输入中的换行符，但是puts()在输出中添加换行符。另一方面，fgets()保留输入中的换行符，fputs()不在输出中添加换行符，因此，puts()应与gets()配对使用，fputs()应与fgets()配对使用。

这里提到已被废弃的gets()，不是鼓励大家使用它，而是为了让读者了解它的用法。如果今后遇到包含该函数的代码，不至于看不懂。

关于fputs()函数的应用示例，可以参考前面的博客-《[C语言的字符串输入fgets()函数](http://blog.csdn.net/libing403/article/details/73012280) 》。



---

参考资料：

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.