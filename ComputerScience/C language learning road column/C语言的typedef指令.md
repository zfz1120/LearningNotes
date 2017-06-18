# C语言的typedef指令

<center>

<img src="image\物竞天择适者生存.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E7%89%A9%E7%AB%9E%E5%A4%A9%E6%8B%A9%E9%80%82%E8%80%85%E7%94%9F%E5%AD%98&step_word=&hs=0&pn=89&spn=0&di=151531669850&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=3368940755%2C2864154163&os=2522544383%2C3296092505&simid=3428991960%2C501954818&adpicid=0&lpn=0&ln=1940&fr=&fmq=1497719784695_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fs11.sinaimg.cn%2Fmw690%2F004hNYc6gy6GLN06On0ca%26690&fromurl=ippr_z2C%24qAzdH3FAzdH3Fks52_z%26e3Bftgw_z%26e3Bv54_z%26e3BvgAzdH3FfAzdH3Fks52_jw8ka8jma8a8r6so_z%26e3Bip4s&gsm=1e&rpstart=0&rpnum=0)*

</center>

typedef工具是一个高级数据特性，利用typedef可以为某一类型自定义名称。它与`#define`有3个不同点：

（1）与`#define`不同，typedef创建的符号名只受限于类型，不能用于值。

（2）typedef由编译器解释，不是预处理器。

（3）在其受限范围内，typedef比`#define`更灵活。

## 工作原理

**使用typedef时要记住，typedef并没有创建任何新类型，它只是为某个已存在的类型增加一个方便使用的标签。**

示例：假设要用BYTE表示1字节的数组。

```c
typedef unsigned char BYTE;
```

随后就可以用BYTE来定义变量：

```c
BYTE X,Y[10],*Z;
```

上面一行代码就相当于

```c
unsigned char X,Y[10],*Z;
```

**可见，typedef相当于给一个已有的类型起了一个新的名字，然后可以像使用旧类型名一样使用新的类型名来声明变量。**这是否多此一举呢？其实不是。

首先，合理使用typedef可以增加程序的可读性，前面的示例中用BYTE代替unsigned char表明你打算用BYTE类型的变量表示数字，而不是字符码。

其次，**typedef可以提高程序的可移植性。**我们知道sizeof运算符的返回值是size_t类型，time()函数返回的类型：time_t类型。这是一个无符号数，但它不是一个新类型。这就用到了C语言的typedef机制，允许程序员为现有类型创建别名。C头文件系统使用typedef把size_t作为unsigned int或unsigned long的别名。这样，使用size_t类型时，编译器会根据不同的系统替换标准类型。对于time_t类似，只要包含time.h头文件，程序就能访问合适的定义。

## 与`#define`的比较

typdef的一些特性与define的功能重合。例如

```c
#define BYTE unsigned char
```

这是预处理器用BYTE替换unsigned char。

**但也有`#define`没有的功能**，例如：

```
typedef char * STRING;
```

编译器把STRING解释为一个类型的表示符，该类型指向char。因此

```C
STRING name, sign;
```

相当于

```c
char * name , * sign;	
```

但是，如果这样假设：

```c
#define STRING char *
```

然后，下面的声明：

```c
STRING name, sign;
```

将被翻译成：

```c
char * name, sign;
```

这导致name才是指针。

## 发挥typedef的好处

除了刚才上面提到的可读性和可移植性的好处外，在一些场合还可以发挥typedef的更多好处。

使用typedef的第一个原因：**为经常出现的类型创建一个方便、易识别的类型名。**

例如，typedef用来命名一个结构类型，可以省略结构的标签：

```c
typedef struct {double x; double y;} rect;
```

那么可以这样使用rect类型名：

```c
rect r1={3.0, 6.0};
rect r2;
```

以上代码被翻译成

```c
struct {double x; double y;} r1={3.0, 6.0};
struct {double x; double y;} r2; 
```

使用typedef的第二个原因是：**typedef常用于给复杂的类型命名。**例如，下面的声明：

```c
typedef char (* FRPTC()) [5];
```

把FRPTC声明为一个函数类型，该函数返回一个指针，该指针内含5个char类型元素的数组。

**使用typedef时要记住，typedef并没有创建任何新类型，它只是为某个已存在的类型增加一个方便使用的标签。**

通过结构、联合和typedef，C提供了有效处理数据的工具和处理可移植数据的工具。

****

参考文献：

史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.