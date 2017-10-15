# scanf， fopen 等“This function or variable may be unsafe”编译错误

转载自：[Visual Studio 2012 编译错误【error C4996: 'scanf': This function or variable may be unsafe. 】的解决方案](http://www.cnblogs.com/gb2013/archive/2013/03/05/SecurityEnhancementsInTheCRT.html)

在VS 2012 中编译 C 语言项目，如果使用了 scanf 函数，编译时便会提示如下错误：

原因是Visual C++ 2012 使用了更加安全的 run-time library routines 。新的Security CRT functions（就是那些带有“_s”后缀的函数），请参见：

### 《[CRT函数的安全增强的版本](http://msdn.microsoft.com/zh-cn/library/wd3wzwts(v=vs.110).aspx)》

下面给出这个问题的解决方案：

方法一：将原来的旧函数替换成新的 Security CRT functions。

方法二：用以下方法屏蔽这个警告：

​    1. 在预编译头文件stdafx.h里（注意：一定要在没有include任何头文件之前）定义下面的宏：

​       **#define _CRT_SECURE_NO_DEPRECATE**

​    2. 或声明 **#param warning(disable:4996)**

​    3. 更改预处理定义：

​        项目->属性->配置属性->C/C++ -> 预处理器 -> 预处理器定义，增加：

​            **_CRT_SECURE_NO_DEPRECATE**

方法三：方法二没有使用更加安全的 CRT 函数，显然不是一个值得推荐的好方法，但我们又不想一个一个地改函数名，这里还有一个更简便的方法：

在预编译头文件 stdafx.h 里（同样要在没有include任何头文件之前）定义下面的宏：

**#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1**

在链接的时候便会自动将旧函数替换成 Security CRT functions 。

**注意**：这个方法虽然使用了新的函数，但是不能消除警告(原因见红字)，你还得同时使用方法二(-_-)。即实际应在预编译头文件 stdafx.h 里加入下面两句：

**#define _CRT_SECURE_NO_DEPRECATE**

**#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1**

------

**错误原因解释：**

这种微软的警告，主要因为那些C库的函数，很多函数内部是不进行参数检测的（包括越界类的），微软担心使用这些会造成内存异常，所以就改写了同样功能的函数，改写了的函数进行了参数的检测，使用这些新的函数会更安全和便捷。关于这些改写的函数你不用专门去记忆，因为编译器对于每个函数在给出警告时，都会告诉你相应的安全函数，查看警告信息就可以获知，在使用时也再查看一下MSDN详细了解。