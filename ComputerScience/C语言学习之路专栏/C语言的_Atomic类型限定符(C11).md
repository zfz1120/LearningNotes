# C语言的_Atomic类型限定符(C11)

<center>

<img src="image\广西大学碧云湖.jpg">

*广西大学碧云湖-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%B9%BF%E8%A5%BF%E5%A4%A7%E5%AD%A6%E9%A3%8E%E6%99%AF&step_word=&hs=0&pn=99&spn=0&di=193719053990&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=1552645649%2C4016331428&os=464323196%2C3162441272&simid=4198666936%2C376259391&adpicid=0&lpn=0&ln=1716&fr=&fmq=1496917549739_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fstatic2.photo.sina.com.cn%2Fbmiddle%2F4a92da92g5dae513c18e1&fromurl=ippr_z2C%24qAzdH3FAzdH3Fks52_z%26e3Bftgw_z%26e3Bv54_z%26e3BvgAzdH3FfAzdH3Fks52_9wld1wlda8aakwdx_z%26e3Bip4s&gsm=3c&rpstart=0&rpnum=0)*

</center>

并发程序设计把程序执行分成可以同时执行的多个线程。这程序设计带来了新的挑战，包括如何管理访问相同数据的不同线程。C11通过包含可选的头文件stdatomic.h和threads.h，提供了一些可选的（不是必须实现的）管理方法。值得注意的是，要通过各种红函数类访问原子类型。当一个线程对一个原子类型的对象执行原子操作时，其他线程不能访问该对象。

所谓原子操作，就是该操作绝不会在执行完毕前被任何其他任务或事件打断，也就说，它的最小的执行单位，不可能有比它更小的执行单位，因此这里的原子实际是使用了物理学里的物质微粒的概念。

所以这里说到的原子操作，基本都包含我们三个方面所关心的语义：操作本身是不可分割的(Atomicity)，一个线程对某个数据的操作何时对另外一个线程可见(Visibility)，执行的顺序是否可以被重排(Ordering)。

这有点类似互斥对象对共享资源的访问的保护，但是原子操作更加接近底层，因而效率更高。

例如下面的代码：

```c
int hogs;//普通声明
hogs= 12; //普通赋值
```

可以替换成：

```c
_Atomic int hogs; //hogs是一个原子类型的变量
atomic_store(&hogs,12); //stdatomic.h中的宏
```

这里，在hogs中存储12是一个原子过程，其他线程不能访问hogs。

编写这种代码的前提是，编译器要支持这一新特性。

-----

参考资料：

1.史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

2.[atomic_inc 原子操作](http://blog.chinaunix.net/uid-10747583-id-2920900.html) 

3.[C++11 并发指南(atomic 类型详解四 C 风格原子操作介绍)](http://blog.csdn.net/flyingleo1981/article/details/14227241)