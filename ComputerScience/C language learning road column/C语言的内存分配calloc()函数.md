# C语言的内存分配calloc()函数

<center>

<img src="image\生命是一场无法回放的电影.jpg">

图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E7%94%9F%E5%91%BD%E7%9A%84%E6%84%8F%E4%B9%89%E6%A0%BC%E8%A8%80&step_word=&hs=0&pn=1&spn=0&di=136726493200&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=3241430003%2C1065435390&os=3850050937%2C4069785332&simid=4192607803%2C838914305&adpicid=0&lpn=0&ln=1974&fr=&fmq=1496989967511_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fuploads.yuwenmi.com%2Fallimg%2F201702%2F021486022654137215.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3By7ojg4t_z%26e3Bv54AzdH3FstzitAzdH3F4tg2ywgAzdH3Fnaamb8_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)

</center>

C语言的内存分配除了用`malloc()`函数，还可以用`calloc()`函数，典型的用法如下：

```c
long * newmem;
newmem = (long *)calloc(100,sizeof(long));
```

和`malloc()`类似，在ANSI之前，`calloc()`也返回指向`char`的指针；在ANSI之后，返回指向`void`的指针。如果要存储不同的类型，应私用强制类型转换运算符。**`calloc()`函数接受两个无符号整数作为参数(ANSI规定是size_t类型)。** 第一个参数是多续的存储单元的数量，第二个参数是存储单元的大小（以字节为单位）。在该例中，`long`为4个字节，所以前面的代码创建了100个4字节的存储单元，总共400个字节。

用`sizeof(long)`而不是4，提高了代码的可移植性。这样，在其他long不是4字节的系统也能正常工作。

**calloc()函数还有一个特性：它把块中所有为都设置为0（注意，在某些硬件系统中，不是把所有为都设置为0来表示浮点数0）。**

free()函数也可以用于释放calloc()分配的内存。

动态内存分配是许多高级程序设计技巧的关键。有些编译器还提供其他内存管理函数，有些可以移植，有些不可以，这需要注意。



---

参考资料：

史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.