# VC++编程-windows编程的概念

### 创建Windows应用程序的方法

Visual C++2008有3中基本的创建交互式Windows应用程序的方法。

* 使用WindowsAPI
* 使用Microsoft Foundation Classes——即大家熟知的MFC，这是一组封装了Windows API的C++类
* 使用Windows Forms：这是一种基于窗体的开发机制，用于创建在CLR中执行的应用程序

这3中方法形成了从最高的编程密集度到最低编程密集度的进步。**使用Windows Forms 是目前最快，最简单的生成应用程序的机制。**使用MFC需要超过Windows Forms的编程工作量，但对于创建GUI的方式拥有更多控制权，而且最终得到的程序将能够在本地PC上执行。

## 窗口的元素

窗口的元素如下图所示

<center>

![窗口的元素](image\窗口的基本元素.png)

</center>

## Windows应用程序的特点

Windows应用程序是在Windows操作系统的控制下运行的，他们不能直接处理硬件，与外部的所有同性都必须通过Windows进行。Winsows程序是事件驱动的。Windows操作应用程序中的事件指用户单击鼠标、按下某个按键或定时器归零等这样的一些时间，操作系统将每个时间记录在一条消息中，并将该消息放入目标程序的消息队列中。WndProc()函数或WindowProc()专门处理这些消息，Windows是通过我们提供的函数指针访问该函数。因此给程序发消息归结为为Windows调用我们提供的通常名为WindowProc()的函数，并借助它传递必要的数据。

任何Windows应用程序与Windows本身之间的所有通信，都要使用Windows应用程序编程接口——亦称作Windows API，由多达数百个函数组成。MFC对这些API进行了封装。另外，针对CLR开发的应用程序，可以使用Windows Forms，其中创建GUI的代码都是自动生成的。

**windows数据类型**

Windows 定义了许多用来在Windows API中指定函数的函数形参类型和返回值类型的数据类型。这些特有的类型传播到了MFC定义的函数中。这些Windows类型的每一种映射为某种C++类型，但映射有可能改变。一些常见的数据类型如下

<center>

![windows特有的数据类型](image\windows特有的数据类型.png)

</center>

**Windows程序的结构**

最简单的仅使用Windows API的Windows程序而言，需要编写两个函数，一个是WinMain()函数，程序的执行从这里开始。一个是WindowProc()函数，该函数是有Windows调用，用来处理应用程序的消息。如下图所示

<center>

![windows应用程序结构](image\windows程序结构.png)

</center>

WinMain()函数等价于控制台程序中的main()函数。其原型如下

```c++
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                   );
```

这些参数的具体含义可以参考MSDN库中的说明。

Windows程序中的WinMain()函数需要做一下4件事情

- 告诉Windows该程序需要的窗口种类
- 创建程序窗口
- 初始化程序窗口
- 获取属于该程序程序的Windows消息

WindowProc()函数的原型如下

```c++
LRESULT CALLBACK WindowProc(HWND hWnd,UINT message,
                           WPARAM wParam,LPARAM lParam);
```

参数含义如下表

<center>

![WindowProc参数含义.png](image\WindowProc参数含义.png)

</center>

**Windows程序的组织**

windows程序的两个基本组件：提供初始化和设置功能的WinMain()函数以及处理Windows消息的WindowProc()函数，两者之间的关系如下图

<center>

![windows程序的组织](image\windows程序的组织.png)

</center>

## 小结

本文介绍了Windows应用程序的关键概念，具体的细节可以参考windows官网的资料。后面继续学习windows MFC编程的相关知识。

----

参考资料

[1] IvorHorton, 霍顿, 姜玲玲,等. Visual C++ 2008入门经典[J]. 2009.