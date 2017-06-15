# C语言的volatile类型限定符

<center>

<img src="image\机器人总动员-月亮之下.jpg" width="500">

*机器人总动员-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E6%9C%BA%E5%99%A8%E4%BA%BA%E6%80%BB%E5%8A%A8%E5%91%98&step_word=&hs=0&pn=1&spn=0&di=25229611331&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=641586133%2C4114993128&os=4257627041%2C3638710175&simid=4110150071%2C733438896&adpicid=0&lpn=0&ln=1854&fr=&fmq=1496908724546_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fattachments.gfan.com%2Fforum%2Fattachments2%2Fday_110806%2F110806103366b9b8e275860bbc.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fkkf_z%26e3B2uwg_z%26e3Bv54AzdH3Fwg165t1-dd0lbda-8-8_z%26e3Bip4s%3Fs1x753q2hsozu74y&gsm=0&rpstart=0&rpnum=0)*

</center>

## volatile限定符的用法

volatile限定符告诉计算机，代理（而不是变量的所在的程序）可以改变该变量的值。通常，它被用于硬件地址以及在其他程序或同时运行的线程中共享数据。例如，一个地址上可能存储着当前的时钟时间，无论程序做什么，地址上的值都随时间的变化而变化。或者一个地址用于接收另一台计算机传入的信息。

```c
volatile int locl; /*locl是一个易变的位置*/
volatile int *ploc; /*ploc是一个指向易变的位置的指针*/
```

以上代码吧locl声明为volatile变量，把ploc声明为指向volatile变量的指针。

读者可能认为volatile是一个可有可无的概念，为什么还要增加这个关键字？原因是它涉及编译器的优化。假设有以下的代码：

```c
val1= x;
/*一些不使用x的代码*/
val2= x;
```

智能的（进行优化的）编译器会注意到以上代码使用了两次x，单并未改变它的值。于是编译器把x的值临时存储在寄存器中，然后val2需要使用x时，才从寄存器中（而不是从原始的内存位置上）读取x的值，以节约时间。这个过程被称为高速缓存（caching）。通常，高速缓存是个不错的优化方案，但是如果一些其他的dialing在以上两条语句之间改变了x的值，就不能这样优化了。如果没有volatile关键字，编译器就不知道这种事情是否会发生。因此，为了安全起见，编译器不进行高速缓存。这是在ANSI之前的事情。现在，如果声明中没有volatile关键字，编译器会假定变量的值在使用过程中不会被其他代理改变，然后再尝试优化代码。

可以同时使用const和volatile限定一个值。例如，通常用const把硬件时钟设置为程序不能更改的变量，但是可以通过代理改变，这时用volatile。只能在声明中同时使用这两个限定符，它们的顺序不分先后如下代码：

```c
volatile const int loc;
const volatile int *ploc;
```

## 总结

因此，可以用一句话总结，volatile关键字的作用就是告诉编译器，这是一个易变的值，不要进行高速缓存这样的优化。

------

参考资料：

史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.