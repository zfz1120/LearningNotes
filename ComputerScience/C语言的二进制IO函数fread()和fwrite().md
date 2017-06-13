# C语言的二进制IO函数fread()和fwrite()

<center>

<img src="image\不读书则愚.jpg"width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%90%8D%E8%A8%80%E9%A3%8E%E6%99%AF%E5%9B%BE&step_word=&hs=0&pn=66&spn=0&di=99563237180&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=2846624170%2C156601477&os=1713395784%2C4163847490&simid=3490476273%2C656273279&adpicid=0&lpn=0&ln=1987&fr=&fmq=1497367833367_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fpic.58pic.com%2F58pic%2F12%2F93%2F19%2F56J58PICA56.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bcbrtv_z%26e3Bv54AzdH3Fiwtkw5AzdH3F8dln8lcm_z%26e3Bip4s&gsm=1e&rpstart=0&rpnum=0)*

</center>

之前的fprintf()、fscanf()、fgets()和fputs()等标准I/O都是面向文本的，用于处理字符和字符串。

例如，下面的代码：

```c
double num=1./3;
fprintf(fp,"%f",num);
```

把num存储为8个字符；0.333333。使用%0.2f转换说明将其存储为4个字符:0.33，用%0.2f转换说明将其存储为14个字符:0.33333333333。改变转换说明将改变存储该值所需的空间数量，也会导致存储不同的值。把num存储为0.33后，读取文件就无法将其恢复为更高的精度。一般而言，fprintf()把数值转换为字符数据，这种转换可能会改变值。

为保证数值存储前后一致，最精确的做法是使用与计算机相同的位组合来存储。因此，double类型的值，应该存储在一个double大小的单元中。**如果以程序所用的表示法把数据储存在文件中，则称为二进制形式储存数据**。不存在从数值形式到字符串的转换过程。对于标准I/O，fread()和fwrite()函数用于二进制形式处理数据(如下图所示)。

实际上所有的数据都是以二进制形式储存的，甚至连字符都以字符码的二进制表示来储存。如果文件中的所有数据都被解释成字符码，则称为**该文件包含文本数据**。如果大部分或所有数据被解释成二进制形式的数值数据，则称**该文件包含二进制数据**(另外，用数据表示机器语言指令的文件都是二进制文件)。

二进制和文本的用法很容易混淆。ANSI C和许多操作系统都同时识别这两种文件格式，能以二进制数据或文本数据形式存储或读取信息。可以用二进制模式打开文本格式的文件，可以把文本储存在二进制形式的文件中。可以调用getc()拷贝包含二进制数据的文件。然而，一般而言，用二进制模式在二进制格式中存储二进制数据。类似地，最常用的还是以文本格式打开文本文件中的文本数据(通常文字处理器生产的文件都是二进制文件，因为这些文件中包含了大量的非文本信息，如字体和格式等)。

<img src="image\二进制输出与文本输出.png">

## fread()和fwrite()函数的用法

头文件：`#include <stdio.h>`

fread()函数用于从文件流中读取数据，其原型为：
​    `size_t  fread(void *buffer, size_t size, size_t count, FILE * stream);`

【参数】buffer为接收数据的地址，size为一个单元的大小，count为单元个数，stream为文件流。

fread()函数每次从stream中最多读取count个单元，每个单元大小为size个字节，将读取的数据放到buffer；文件流的位置指针后移 size * count 字节。

【返回值】返回实际读取的单元个数。如果小于count，则可能文件结束或读取出错；可以用[ferror()](http://c.biancheng.net/cpp/html/2507.html)检测是否读取出错，用[feof()](http://c.biancheng.net/cpp/html/2514.html)函数检测是否到达文件结尾。如果size或count为0，则返回0。

与fread()相对应的函数为[fwrite()](http://c.biancheng.net/cpp/html/2517.html)，fread() 和 fwrite() 一般用于二进制文件的输入输出，ASCII文件还是不要考虑了。

头文件：`#include <stdio.h>`

fwrite()函数以二进制方式向文件流中写入数据，其原型为：
   ` size_t fwrite(void * buffer, size_t size, size_t count, FILE * stream);`

【参数】buffer为数据源地址，size为每个单元的字节数，count为单元个数，stream为文件流指针。

fwrite()函数每次向stream中写入count个单元，每个单元大小为size个字节；文件流的位置指针后移 size * count 字节。

【返回值】返回成功写入的单元个数。如果小于count，则说明发生了错误，文件流错误标志位将被设置，随后可以通过[ferror()](http://c.biancheng.net/cpp/html/2507.html)函数判断。

如果 size 或 count 的值为 0，则返回值为 0，并且文件流的位置指针保持不变。

与fwrite()相对应的函数为[fread()](http://c.biancheng.net/cpp/html/2516.html)，fread() 和 fwrite() 一般用于二进制文件的输入输出。



---

参考文献：

[1] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

[2] C语言fread()函数：从文件流中读取数据.-[来源](http://c.biancheng.net/cpp/html/2516.html)

[3] C语言fwrite()函数：向文件流中写入数据-[来源](http://c.biancheng.net/cpp/html/2517.html)