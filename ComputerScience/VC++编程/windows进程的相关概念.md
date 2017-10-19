# windows进程的相关概念

## 什么是进程

进程通常被定义为一个正在运行的程序的实例，它由两个部分组成： 

* 一个是操作系统用来管理进程的内核对象。内核对象也是系统用来存放关于进程的统计信息的地方。


* 另一个是地址空间，它包含所有可执行模块或 D L L模块的代码和数据。它还包含动态内存分配的空间。如线程堆栈和堆分配空间。 

进程是不活泼的。若要使进程完成某项操作，它必须拥有一个在它的环境中运行的线程，该线程负责执行包含在进程的地址空间中的代码。 

操作系统就要为每个线程安排一定的 C P U时间。它通过以一种循环方式为线程提供时间片 。当创建一个进程时，系统会自动创建它的第一个线程，称为主线程。然后，该线程可以创建其他的线程，而这些线程又能创建更多的线程。 

## 进程的实例句柄

加载到进程地址空间的每个可执行文件或 D L L文件均被赋予一个独一无二的实例句柄。可执行文件的实例作为( w ) Wi n M a i n的第一个参数h i n s t E x e来传递。对于加载资源的函数调用来说，通常都需要该句柄的值。 例如，若要从可执行文件的映象来加载图标资源，需要调用下面这个
函数： 

```c++
HICOM LoadIcon(
	HINSTANCE hinst,
	PCTSTR pszIcon);
```

## 进程的命令行 

当一个新进程创建时，它要传递一个命令行。 该命令行几乎永远不会是空的，至少用于创建新进程的可执行文件的名字是命令行上的第一个标记。 

## 进程的环境变量

每个进程都有一个与它相关的环境块。环境块是进程的地址空间中分配的一个内存块。每个环境块都包含一组字符串。 通常，子进程可以继承一组与父进程相同的环境变量。但是，父进程能够控制子进程继承什么环境变量 。所谓继承，指的是子进程获得它自己的父进程的环境块拷贝，子进程与父进程并不共享相同的环境块。这意味着子进程能够添加、删除或修改它的环境块中的变量，而这个变化在父进程的环境块中却得不到反映。

## 进程的当前驱动器和目录 

 当不提供全路径名时， Wi n d o w s的各个函数就会在当前驱动器的当前目录中查找文件和目 录。系统将对进程的当前驱动器和目录保持跟踪，但是它不跟踪每个驱动器的当前目录。不过，有些操作系统支持对多个驱动器的当前目录的处理。这种支持是通过进程的环境字符串来提供的。 

## 系统版本 

应用程序常常需要确定用户运行的是哪个 Wi n d o w s版本，windows提供了相关函数获取系统版本，例如GetVersionEx、Ve r i f y Ve r s i o n I n f o 。

## CreateProcess函数 

可以用C r e a t e P r o c e s s函数创建一个进程： 

```c++
BOOL CreateProcess
(
    LPCTSTR lpApplicationName,        
    LPTSTR lpCommandLine,        
    LPSECURITY_ATTRIBUTES lpProcessAttributes。
    LPSECURITY_ATTRIBUTES lpThreadAttributes,        
    BOOL bInheritHandles,        
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,        
    LPCTSTR lpCurrentDirectory,        
    LPSTARTUPINFO lpStartupInfo,        
    LPPROCESS_INFORMATION lpProcessInformation 
);
```

## 终止进程的运行

若要终止进程的运行，可以使用下面四种方法：

* 主线程的进入点函数返回（最好使用这个方法）。
* 进程中的一个线程调用`ExitProcess`函数（应该避免使用这种方法）。
* 另一个进程中的线程调用`TerminateProcess`函数（应该避免使用这种方法）。
* 进程中的所有线程自行终止运行（这种情况几乎从未发生）。 



-------

参考文献：

JeffreyRichter, ChristopheNasarre, 里克特,等. Windows核心编程[M]. 人民邮电出版社, 2008.