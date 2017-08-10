# #pragma命令详解(二)

转载自：[#pragma命令详解(二)](http://www.cnblogs.com/cchyao/archive/2010/09/25/1834319.html)



**15 inline_recursion**

\#pragma inline_recursion( [{on | off}] )

控制直接或者相互间的递归函数调用式的嵌入扩展。用这个编译指示控制用inline，__inline标记的或在/Ob2选项下能自动嵌入的嵌入函数。使用这个编译指示需要设置编译程序选项/Ob为1或者2。默认的inline_recursion状态是off。这个编译指示在出现该编译指示之后第一个函数调用起作用，并不影响函数的定义。

inline_recursion编译指示控制如何扩展递归函数。如果inline_recursion是off，并且如果一个嵌入函数调用了它自己（直接的或者间接的），函数将仅仅扩展一次。如果inline_recursion是on,函数将扩展多次直到达到inline_depth的值或者容量限制。

**16 intrinsic**

\#pragma intrinsic( function1 [, function2, ...] )

指定对在编译指示参数表中函数调用是内含的。编译程序像嵌入代码一样生成内含函数，而不是函数调用。下面列出了具有内含形式的库函数。一旦遇到intrinsic编译指示，它从第一个包含指定内含函数的函数定义开始起作用。作用持续到源文件尾部或者出现包含相同内含函数的function编译指示。intrinsic编译指示只能用在函数定义外——在全局层次。

下列函数具有内含形式：

| _disable | _enable | _inp   | _inpw  | _lrotl  | _lrotr |
| -------- | ------- | ------ | ------ | ------- | ------ |
| _outp    | _outpw  | _rotl  | _rotr  | _strset | abs    |
| fabs     | labs    | memcmp | memcpy | memset  | strcat |
| strcmp   | strcpy  | strlen |        |         |        |

使用内含函数的程序更快，因为它们没有函数调用的额外代价，然而因为有附加的代码生成，可能比较大。

注意，_alloca和setjmp函数总是内含的，这个行为不受intrinsic编译指示影响。

下列浮点函数没有内含形式。然而它们具有直接将参数通过浮点芯片传送而不是推入程序堆栈的版本。

| acos | asin | cosh | fmod | pow  | sinh |
| ---- | ---- | ---- | ---- | ---- | ---- |
| tanh |      |      |      |      |      |

当你同时指定/Oi和/Og编译程序选项（或者任何包含/Og，/Ox，/O1和/O2的选项）时下列浮点函数具有真正的内含形式。

| atan | exp  | log10 | sqrt | atan2 | log  |
| ---- | ---- | ----- | ---- | ----- | ---- |
| sin  | tan  | cos   |      |       |      |

你可以用编译程序选项/Op或/Za来覆盖真内含浮点选项的生成。在这种情况下，函数会像一般库函数一样被生成，同时直接将参数通过浮点芯片传送而不是推入程序堆栈。

**17 message**

\#pragma message( messagestring )

不中断编译，发送一个字符串文字量到标准输出。message编译指示的典型运用是在编译时显示信息。

下面的代码段用message编译指示在编译过程中显示一条信息：

\#if _M_IX86 == 500

\#pragma message( "Pentium processor build" )

\#endif

messagestring参数可以是一个能够扩展成字符串文字量的宏，并且你能够用字符串文字量和宏的任何组合来构造。例如，下面的语句显示被编译文件的文件名和文件最后一次修改的日期和时间。

\#pragma message( "Compiling " __FILE__ )

\#pragma message( "Last modified on " __TIMESTAMP__ )

**18 once**

\#pragma once

指定在创建过程中该编译指示所在的文件仅仅被编译程序包含（打开）一次。该编译指示的一种常见用法如下：

//header.h

\#pragma once

// Your C or C++ code would follow:

**19 optimize**

仅在专业版和企业版中存在

\#pragma optimize( "[optimization-list]", {on | off} )

代码优化仅有Visual C++专业版和企业版支持。详见Visual C++ Edition。

指定在函数层次执行的优化。optimize编译选项必须在函数外出现，并且在该编译指示出现以后的第一个函数定义开始起作用。on和off参数打开或关闭在optimization-list指定的选项。

optimization-list能够是0或更多个在表2.2中给出的参数：

表 2.2   optimize编译指示的参数

| 参数    | 优化类型             |
| ----- | ---------------- |
| a     | 假定没有别名。          |
| g     | 允许全局优化。          |
| p     | 增强浮点一致性。         |
| s 或 t | 指定更短或者更快的机器代码序列。 |
| w     | 假定在函数调用中没有别名。    |
| y     | 在程序堆栈中生成框架指针。    |

这些和在/O编译程序选项中使用的是相同的字母。例如：

\#pragma optimize( "atp", on )

用空字符串（""）的optimize编译指示是一种特别形式。它要么关闭所有的优化选项，要么恢复它们到原始（或默认）的设定。

\#pragma optimize( "", off )

\#pragma optimize( "", on )

**20 pack**

\#pragma pack( [ n] )

指定结构和联合成员的紧缩对齐。尽管用/Zp选项设定整个翻译单元的结构和联合成员的紧缩对齐，可以用pack编译指示在数据说明层次设定紧缩对齐。从出现该编译指示后的第一个结构或者联合说明开始生效。这个编译指示不影响定义。

当你使用#pragma pack(n)，其中n是1，2，4，8或者16，第一个以后的每个结构成员保存在较小的成员类型或者n字节边界上。如果你使用没有参数的#pragma pack，结构成员将被紧缩到由/Zp指定的值。默认的/Zp紧缩的大小是/Zp8。

编译程序还支持下面的增强语法：

\#pragma pack( [ [ { push | pop}, ] [ identifier, ] ] [ n ] )

该语法允许你将使用不同紧缩编译指示的组件合并到同一个翻译单元内。

每次出现有push参数的pack编译指示将保存当前的紧缩对齐值到一个内部的编译程序堆栈。编译指示的参数列表从左向右读取。如果你使用了push，当前紧缩值被保存。如果你提供了一个n值，这个值将成为新的紧缩值。如果你指定了一个你选定的标示符，这个标示符将和新的紧缩值关联。

每次出现有pop参数的pack编译指示从内部编译程序堆栈顶部取出一个值并将那个值作为新的紧缩对齐。如果你用了pop，而内部编译程序堆栈是空的，对齐值将从命令行得到，同时给出一个警告。如果你用了pop并指定了n的值，那个值将成为新的紧缩值。如果你用了pop并指定了一个标示符，将移去所有保存在堆栈中的的值直到匹配的找到匹配的标示符，和该标示符关联的紧缩值也被从堆栈中移出来成为新的紧缩值。如果没有找到匹配的标示符，将从命令行获取紧缩值并产生一个1级警告。默认的紧缩对齐是8。

pack编译指示的新的增强功能允许你编写头文件保证在使用头文件之前和其后的紧缩值是一样的：

/* File name: include1.h

*/

\#pragma pack( push, enter_include1 )

/* Your include-file code ... */

\#pragma pack( pop, enter_include1 )

/* End of include1.h */

在前面的例子中，进入头文件时将当前紧缩值和标示符enter_include1关联并推入，被记住。在头文件尾部的pack编译选项移去所有在头文件中可能遇到的紧缩值并移去和enter_include1关联的紧缩值。这样头文件保证了在使用头文件之前和其后的紧缩值是一样的。

新功能也允许你在你的代码内用pack编译指示为不同的代码，例如头文件设定不同的紧缩对齐。

\#pragma pack( push, before_include1 )

\#include "include1.h"

\#pragma pack( pop, before_include1 )

在上一个例子中，你的代码受到保护，防止了在include.h中的任何紧缩值的改变。

**21 pointers_to_members**

C++特有

\#pragma pointers_to_members(pointer-declaration, [most-general-representation] )

指定是否能够在相关类定义之前说明一个指向类成员的指针，并且用于控制指针的大小和解释指针的代码。你能够在你的源代码中使用pointers_to_members编译知识来代替/vmx编译程序选项。

pointer-declaration参数指出是否在相关函数定义之前或其后你已经说明了一个指向成员的指针。pointer-declaration参数是下面两个符号之一：

| 参数              | 说明                                       |
| --------------- | ---------------------------------------- |
| full_generality | 生成安全的，但是有时不能优化的代码。如果有一些指向成员的指针在相关类定义之前说明，你要用full_generality。这个参数总是使用由most-general-representation指定的指针表示方式。 |
| best_case       | 对于所有指向成员的指针用最佳的表示方式生成安全的，优化的代码。需要在说明一个指向类成员指针之前定义类。默认是best_case。 |

most-general-representaion参数指出在一个翻译单元中编译程序能够安全引用任何指向类成员指针的最小指针表示方式。这个参数可以是下列之一：

| 参数                  | 说明                                       |
| ------------------- | ---------------------------------------- |
| single_inheritance  | 最普通的表示方式是单继承，指向成员函数。如果用于指向具有多重或者虚拟继承方式类成员的指针，将产生一个错误。 |
| multi_inheritance   | 最普通的表示方式是多重继承，指向成员函数。如果用于指向具有虚拟继承方式类成员的指针，将产生一个错误。 |
| virtual_inheritance | 最普通的表示方式是虚拟继承，指向成员函数。不会产生错误。当使用#pragma pointers_to_members (full_generality)时这是默认的参数。 |

**22 setlocale**

\#pragma setlocale( "locale-string" )

定义用于翻译宽字符常数和字符串文字量时用的地区（国家和语言）。由于用于从多字节字符转换到宽字符的算法根据地区或者由于在运行可执行程序不同的地方进行编译而不同，这个编译指示提供一种在编译时指定目标地区的方式。这保证宽字符字符串将以正确的格式保存。默认的locale-string是“C”。“C”地区将字符串中的每个字符作为wchar_t（即unsigned int）映射其值。

**23 vtordisp**

C++特有

\#pragma vtordisp({on | off} )

允许隐藏的附加vtordisp构造函数/析构函数替换成员。vtordisp编译指示仅能够用于具有虚拟基类的代码。如果派生类从一个虚拟基类重载了一个虚拟函数，并且如果派生类的构造函数或析构函数用指向虚拟基类的指针调用了这个函数，编译程序将根据虚拟基类在类中引入一个附加的隐藏“vtordisp”域。

vtodisp编译选项影响它后面的类布局。/vd0和/vd1选项为整个模块指定了相同的行为。指定off将禁止隐藏的vtordisp成员，指定on（默认）将在它们需要的时候允许vtordisp。仅在不可能出现类的构造函数和析构函数通过this指针调用其指向对象中的虚拟函数时才关闭vtordisp。

\#pragma vtordisp( off )

class GetReal : virtual public { ... };

\#pragma vtordisp( on )

**24 warning**

\#pragma warning( warning-specifier : warning-number-list [,warning-specifier : warning-number-list...] )

\#pragma warning( push[ , n ] )

\#pragma warning( pop )

允许有选择地修改编译程序警告信息的行为。

warning-specifier能够是下列值之一：

| warning-specifier | 含义                |
| ----------------- | ----------------- |
| once              | 只显示指定信息一次。        |
| default           | 对指定信息应用默认的编译程序选项。 |
| 1,2,3,4           | 对指定信息引用给定的警告等级。   |
| disable           | 不显示指定信息。          |
| error             | 对指定信息作为错误显示。      |

warning-number_list能够包含任何警告编号。如下，在一个编译指示中可以指定多个选项：

\#pragma warning( disable : 4507 34; once : 4385; error : 164 )

这等价于：

\#pragma warning( disable : 4507 34 ) // Disable warning messages

​                                             // 4507 and 34.

\#pragma warning( once : 4385 )        // Issue warning 4385

​                                             // only once.

\#pragma warning( error : 164 )        // Report warning 164

​                                             // as an error.

对于那些关于代码生成的，大于4699的警告标号，warning编译指示仅在函数定义外时有效。如果指定的警告编号大于4699并且用于函数内时被忽略。下面例子说明了用warning编译指示禁止、然后恢复有关代码生成警告信息的正确位置：

int a;

\#pragma warning( disable : 4705 )

void func()

{

​    a;

}

\#pragma warning( default : 4705 )

warning编译指示也支持下面语法：

\#pragma warning( push [ ,n ] )

\#pragma warning( pop )

这里n表示警告等级（1到4）。

warning(push)编译指示保存所有警告的当前警告状态。warning(push,n)保存所有警告的当前状态并将全局警告等级设置为n。

warning(pop)弹出最后一次推入堆栈中的警告状态。任何在push和pop之间改变的警告状态将被取消。考虑下面的例子：

\#pragma warning( push )

\#pragma warning( disable : 4705 )

\#pragma warning( disable : 4706 )

\#pragma warning( disable : 4707 )

// Some code

\#pragma warning( pop )

在这些代码的结束，pop恢复了所有警告的状态（包括4705，4706和4707）到代码开始时候的样子。

当你编写头文件时，你能用push和pop来保证任何用户修改的警告状态不会影响正常编译你的头文件。在头文件开始的地方使用push，在结束地方使用pop。例如，假定你有一个不能顺利在4级警告下编译的头文件，下面的代码改变警告等级到3，然后在头文件的结束时恢复到原来的警告等级。

\#pragma warning( push, 3 )

// Declarations/ definitions

\#pragma warning( pop )