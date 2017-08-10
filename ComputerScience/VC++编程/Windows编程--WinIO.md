# WinIO


## 函数名： Sleep

功 能： 执行[挂起](https://baike.baidu.com/item/%E6%8C%82%E8%B5%B7)一段时间

用 法： `void Sleep(DWORD dwMilliseconds);`

在VC中使用带上头文件

`#include <windows.h>`

（ Sleep函数存放头文件：WinBase.h）

在gcc[编译器](https://baike.baidu.com/item/%E7%BC%96%E8%AF%91%E5%99%A8)中，使用的头文件因gcc版本的不同而不同

`#include <unistd.h>`

Sleep()单位为毫秒，sleep()单位为秒（如果需要更精确可以用**usleep单位为微秒**）

返回值

若进程/线程挂起到参数所指定的时间则返回0，若有信号中断则返回剩余秒数。

在VC中Sleep中的第一个英文[字符](https://baike.baidu.com/item/%E5%AD%97%E7%AC%A6)为大写的"S"

在标准C中是sleep, 不要大写.. 下面使用大写的来说明,, 具体用什么看你用什么[编译器](https://baike.baidu.com/item/%E7%BC%96%E8%AF%91%E5%99%A8). 简单的说[VC](https://baike.baidu.com/item/VC/7792954)用Sleep, 别的一律使用sleep.

Sleep函数的一般形式:

Sleep(unsigned long);

其中，Sleep()里面的单位，是以毫秒为单位，所以如果想让函数滞留1秒的话，应该是Sleep(1000);

在Linux下，sleep中的“s”不大写

sleep()单位为秒，usleep()里面的单位是微秒。在[内核](https://baike.baidu.com/item/%E5%86%85%E6%A0%B8)中，sleep的实现是由pause函数和alarm函数两个实现的。

特别注意在Codeblocks环境下是无法使用sleep函数的，因为在windows上Codeblocks采用mingw(Gnu在Window环境下的编译器，可以充分使用WindowsApi)作为编译器，而在stdlib.h中sleep的说明如下：

```c++
_CRTIMP void cdecl MINGW_NOTHROW _sleep (unsigned long) __MINGW_ATTRIB_DEPRECATED;
```

可以认为mingw舍弃了sleep函数，建议用Sleep实现sleep。



## WinIO函数库

WinIO程序库允许在32位的Windows应用程序中直接对I/O端口和物理内存进行存取操作。通过使用一种内核模式的设备驱动器和其它几种底层编程技巧，它绕过了Windows系统的保护机制。

## 工作原理

WinNT/2000/XP下，WinIO函数库只允许被具有管理者权限的应用程序调用。如果使用者不是以管理者的身份进入的，则WinIO.DLL不能够被安装，也不能激活WinIO[驱动器](https://baike.baidu.com/item/%E9%A9%B1%E5%8A%A8%E5%99%A8)。通过在管理者权限下安装驱动器软件就可以克服这种限制。然而，在这种情况下，ShutdownWinIo函数不能在应用程序结束之前被调用，因为该函数将WinIO[驱动程序](https://baike.baidu.com/item/%E9%A9%B1%E5%8A%A8%E7%A8%8B%E5%BA%8F)从[系统注册表](https://baike.baidu.com/item/%E7%B3%BB%E7%BB%9F%E6%B3%A8%E5%86%8C%E8%A1%A8)中删除。

## 函数详解

该函数库提供8个函数功能调用：

bool _stdcall InitializeWinIo();

本函数初始化WioIO函数库。

必须在调用所有其它功能函数之前调用本函数。

如果[函数调用](https://baike.baidu.com/item/%E5%87%BD%E6%95%B0%E8%B0%83%E7%94%A8)成功，返回值为非零值。

如果调用失败，则返回值为0。

void _stdcall ShutdownWinIo();

本函数在内存中清除WinIO库

本函数必须在中止应用函数之前或者不再需要WinIO库时调用，

bool _stdcall GetPortVal(WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize);

使用此函数从一个输入或输出端口读取一个字节/字/双字数据。

参数：

wPortAddr – 输入输出端口地址

pdwPortVal – 指向双字变量的[指针](https://baike.baidu.com/item/%E6%8C%87%E9%92%88)，接收从端口得到的数据。

bSize – 需要读的字节数，可以是1 (BYTE), 2 (WORD) or 4 (DWORD).

如果调用成功，则返回非零值。

如果[函数调用](https://baike.baidu.com/item/%E5%87%BD%E6%95%B0%E8%B0%83%E7%94%A8)失败，则函数返回值为零。

bool _stdcall SetPortVal(WORD wPortAddr, DWORD dwPortVal, BYTE bSize);

使用本函数将一个字节/字/双字的数据写入输入或输出接口。

参数：

wPortAddr – 输入输出口地址

dwPortVal – 要写入口的数据

bSize – 要写的数据个数，可以是 1 (BYTE), 2 (WORD) or 4 (DWORD).

如果调用成功，则返回非零值。

如果[函数调用](https://baike.baidu.com/item/%E5%87%BD%E6%95%B0%E8%B0%83%E7%94%A8)失败，则函数返回值为零。

PBYTE _stdcall MapPhysToLin(PBYTE pbPhysAddr, DWORD dwPhysSize, HANDLE *pPhysicalMemoryHandle)

使用此函数将[物理内存](https://baike.baidu.com/item/%E7%89%A9%E7%90%86%E5%86%85%E5%AD%98)的一部分映射到一个32位应用程序的线性地址空间。

下面是一个例子：

PBYTE pbLinAddr;

HANDLE PhysicalMemoryHandle;

pbLinAddr = MapPhysToLin(0xA0000, 65536, &PhysicalMemoryHandle);

该函数将把物理地址范围为0xA0000 - 0xAFFFF的[地址空间](https://baike.baidu.com/item/%E5%9C%B0%E5%9D%80%E7%A9%BA%E9%97%B4)映射到与应用程序对应的[线性地址](https://baike.baidu.com/item/%E7%BA%BF%E6%80%A7%E5%9C%B0%E5%9D%80)空间。 返回值为一个与物理地址0xA0000相关的线性地址。如果出现错误，则返回值为NULL。

参数：

pbPhysAddr – 指向物理地址的[指针](https://baike.baidu.com/item/%E6%8C%87%E9%92%88)

dwPhysSize – 需要映射的字节数

pPhysicalMemoryHandle – 变量指针，如果调用成功，负责接收[物理内存](https://baike.baidu.com/item/%E7%89%A9%E7%90%86%E5%86%85%E5%AD%98)句柄。随后本句柄在调用UnmapPhysicalMemory函数时作为其第一个参数。

bool _stdcall UnmapPhysicalMemory(HANDLE PhysicalMemoryHandle, PBYTE

pbLinAddr)

使用本函数解除原先使用MapPhysToLin函数映射的一段线性物理内存区域，该区域被映射到应用程序所属的线性地址空间。

Windows 9x 应用程序不需要调用此函数。

参数：

PhysicalMemoryHandle – 物理内存区域所属的句柄，此参数由对MapPhysToLin函数的调用返回。

pbLinAddr – MapPhysToLin[函数调用](https://baike.baidu.com/item/%E5%87%BD%E6%95%B0%E8%B0%83%E7%94%A8)返回的线性地址。

bool _stdcall GetPhysLong(PBYTE pbPhysAddr, PDWORD pdwPhysVal);

从指定的[物理地址](https://baike.baidu.com/item/%E7%89%A9%E7%90%86%E5%9C%B0%E5%9D%80)读取一个双字数据。

参数：

pbPhysAddr – 指向物理地址的指针。

pdwPhysVal – 指向一个双字变量的[指针](https://baike.baidu.com/item/%E6%8C%87%E9%92%88)，接收从[物理内存](https://baike.baidu.com/item/%E7%89%A9%E7%90%86%E5%86%85%E5%AD%98)中传来的数据。

如果此[函数调用](https://baike.baidu.com/item/%E5%87%BD%E6%95%B0%E8%B0%83%E7%94%A8)成功，返回一个非零值。

如果函数调用失败，则返回一个零值。

bool _stdcall SetPhysLong(PBYTE pbPhysAddr, DWORD dwPhysVal);

将一个双字型数据写入指定的[物理地址](https://baike.baidu.com/item/%E7%89%A9%E7%90%86%E5%9C%B0%E5%9D%80)。

参数：

pbPhysAddr – 指向物理地址的指针。

pdwPhysVal – 指定待写入物理内存地址出的双字型数据。

如果此函数调用成功，返回一个非零值。

如果函数调用失败，则返回一个零值。