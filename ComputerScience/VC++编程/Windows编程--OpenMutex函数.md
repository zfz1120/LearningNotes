# Windows编程--互斥量Mutex操作函数

转载自百度百科：[CreateMutex](https://baike.baidu.com/item/CreateMutex/9584433?fr=aladdin)，[OpenMutex](https://baike.baidu.com/item/OpenMutex/4952430?fr=aladdin)

常用操作mutex的函数有：ReleaseMutex / OpenMutex / WaitForSingleObject / WaitForMultipleObjects。

## CreateMutex函数

CreateMutex作用是找出当前系统是否已经存在指定进程的实例。如果没有则[创建](https://baike.baidu.com/item/%E5%88%9B%E5%BB%BA)一个[互斥体](https://baike.baidu.com/item/%E4%BA%92%E6%96%A5%E4%BD%93)。

CreateMutex()函数可用来创建一个有名或无名的[互斥量](https://baike.baidu.com/item/%E4%BA%92%E6%96%A5%E9%87%8F)对象，其函数原型为：

### VB声明

```vb
Declare Function CreateMutex Lib "kernel32" Alias "CreateMutexA" (lpMutexAttributes As SECURITY_ATTRIBUTES, ByVal bInitialOwner As Long, ByVal lpName As String) As Long
```

### VC声明

```c++
HANDLE CreateMutex(
LPSECURITY_ATTRIBUTESlpMutexAttributes, // 指向安全属性的指针
BOOLbInitialOwner, // 初始化互斥对象的所有者
LPCTSTRlpName // 指向互斥对象名的指针
);
```

### 返回值

Long，如执行成功，就返回互斥体对象的句柄；零表示出错。会设置GetLastError。如果返回的是一个有效句柄，但指定的名字已经存在，GetLastError也会设为ERROR_ALREADY_EXISTS，bInitialOwner的值将会被忽略。如果调用者限制了权限，GetLastError将会返回ERROR_ACCESS_DENIED，这个时候应该使用OpenMutex函数。

### 参数表

参数 类型及说明

lpMutexAttributes SECURITY_ATTRIBUTES，指定一个SECURITY_ATTRIBUTES结构，或传递零值（将参数声明为ByVal As Long，并传递零值），表示使用不允许继承的默认描述符

bInitialOwner BOOL，如创建进程希望立即拥有[互斥体](https://baike.baidu.com/item/%E4%BA%92%E6%96%A5%E4%BD%93)，则设为TRUE。一个互斥体同时只能由一个线程拥有

lpName String，指定互斥体对象的名字。用vbNullString创建一个[未命名](https://baike.baidu.com/item/%E6%9C%AA%E5%91%BD%E5%90%8D)的互斥体对象。如已经存在拥有这个名字的一个事件，则打开现有的已命名互斥体。这个名字可能不与现有的事件、信号机、可等待计时器或文件映射相符

## OpenMutex函数

OpenMutex函数为现有的一个已命名[互斥体](https://baike.baidu.com/item/%E4%BA%92%E6%96%A5%E4%BD%93)对象创建一个新句柄。

函数功能：

函数原型：

```c++
HANDLE OpenMutex(
DWORD dwDesiredAccess, // access
BOOL bInheritHandle, // inheritance option
LPCTSTR lpName // object name
);
```

参数：

**dwDesiredAccess：**

MUTEX_ALL_ACCESS 请求对互斥体的完全访问

MUTEX_MODIFY_STATE 允许使用 ReleaseMutex 函数

SYNCHRONIZE 允许互斥体对象同步使用

**bInheritHandle** : 如希望子进程能够继承句柄，则为TRUE

l**pName** ：要打开对象的名字

返回值：如执行成功，返回对象的句柄；零表示失败。若想获得更多错误信息，请调用GetLastError函数。

备注：一旦不再需要，注意一定要用 CloseHandle 关闭[互斥体](https://baike.baidu.com/item/%E4%BA%92%E6%96%A5%E4%BD%93)句柄。如对象的所有句柄都已关闭，那么对象也会删除

速查：**Windows NT/2000/XP**：3.1以上版本；**Windows 95/98/Me**：95以上版本：

头文件：Windows.h ;库文件：Kernel32.lib。

DLL：Kernel32.dll.

## ReleaseMutex函数

ReleaseMutex是一种线性指令，具有释放线程拥有的互斥体的控制权。

### 说明

ReleaseMutex函数的功能是释放互斥对象的控制权

### 函数原型

BOOL WINAPI ReleaseMutex(

HANDLE hMutex

);

### 返回值

BOOL，TRUE表示成功，FALSE表示失败。

### 参数表

hMutex：HANDLE，制定一个[互斥体](https://baike.baidu.com/item/%E4%BA%92%E6%96%A5%E4%BD%93)的句柄。

### 注释

一个线程释放了互斥对象的控制权后，如果其他进程在等待互斥对象置位，则等待的线程可以得到该互斥对象，等待函数返回，互斥对象被新的线程所拥有。