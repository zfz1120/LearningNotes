# C语言的const类型限定符

<center>

<img src="image/广西大学校门.jpg">

*广西大学校门-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%B9%BF%E8%A5%BF%E5%A4%A7%E5%AD%A6%E6%A0%A1%E9%97%A8&step_word=&hs=0&pn=7&spn=0&di=155683128150&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=184790369%2C3337503179&os=2128067756%2C906389670&simid=3315635542%2C329130040&adpicid=0&lpn=0&ln=1794&fr=&fmq=1496896260494_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fs15.sinaimg.cn%2Fmiddle%2F6b4a0867gafd1b385f7ae%26690&fromurl=ippr_z2C%24qAzdH3FAzdH3Fks52_z%26e3Bftgw_z%26e3Bv54_z%26e3BvgAzdH3FfAzdH3Fks52_mk9wabm0a8aapofk_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

## 类型限定符的变化

我们通常用类型和存储类别来描述一个变量。C90还增加了两个属性：恒常性（constancy）和易变性（volatility）。这两个属性分别用关键字const和volatile来声明，以这两关键字创建的类型是**限定类型**。C99标准新增了第3个限定符：restrict，用于提高编译器优化。C11新增了第四个限定符：_Atomic。C11提供了一个可选库，由stdatomic.h管理，以支持并发程序设计，而且 _Atomic是可选支持项。C99为类型限定符增加了一个新属性：它们现在是幂等的（idempotent），其实意思就是可以在一条声明中多次使用同一个限定符，多余的限定符将被忽略：

```c
const const const int n= 6;//与const int n= 6;相同
```

## const类型限定符

以const关键字声明的对象，其值不能通过赋值或递增、递减来修改。在ANSI兼容的编译器中，以下代码：

```c
const int nochange; //限定nochange的值不能被修改
nochange= 12;       //不允许
```

以上代码，编译器会报错。但是，可以初始化const变量。因此下面的代码没有问题：

```c
const int nochange= 12; //没有问题
```

该声明让nochange成为只读变量。初始化后，就不能改变它的值。

### const修饰指针和形参

```c
const float * p1; /*p1指向一个float类型的const值，指针pf指向的值不能被改变，但是p1指针本身的值可以改变y.另外，与float const * p1;相同*/

float * const p2; /*p2是一个const指针，指针p2本身的值不能更改，但它所指向的值可以改变*/

float const * const p3;/*表明p2既不能指向别处，它所指向的值也不能改变*/
```

如注释，把const放在类型之后、*之前，说明指针不能用于改变它多指向的值。简而言之，**const 放在\*的左侧任意位置，限定了指针指向的数据不能改变；const放在\*的右侧，限定了指针本身不能改变。**

const的常见用法是声明函数形参的指针。下面保证了数组不会被改变

```c
void display(const int array[],int limit); /*const int array[]与const int *array相同*/

void simple(const char * s); /*声明表明形式参数s被传递给simple()函数的值初始化后，simple()不能改变s指向的值*/

void supple(int * const pi); /*与void supple(int pi[const]);等价。这两个声明都表示supple()函数不会改变形参pi*/
```

## 对全局数据使用const

使用全局数据是一种冒险的方法，因为这样暴露了数据，程序的任何部分都能更改数据。如果把数据设置为const，就可避免这样的危险，因此，用const声明全局数据很合理。可以创建const变量、const数组和const结构。

然而，在文件间共享const数据要小心。可以采取两个策略：

第一，遵循外部变量的常用规则，在一个文件中使用定义式声明，在其他文件使用引用式声明（用extern关键字）。

另一种方案，把const变量放在一个头文件中，然后在其他文件中包含该头文件。这种放方案必须在头文件中使用关键字static声明全局const变量。如果去掉static，那么在file1.c和file2.c中包含constant.h将会导致每个文件中都有一个相同标识符的定义式声明，C标准不允许这样做（然而，有些编译器允许这样做）。实际上，这种方案相当于给每个文件都提供了一个单独的数据副本（注意，以static声明的文件作用域变量具有内部链接属性）。由于每个副本只对该文件可见，所以无法用这些数据和其他文件通信。不会没关系，它们都是完全相同的（每个文件都包含了相同的头文件）的const数据（声明时使用了const关键字），因此这不是问题。

头文件的好处是，方便你偷懒，不用惦记着在一个文件中使用定义式声明，在其他文件中使用引用式声明。所有文件都只需包含同一个头文件。但是它的缺点是，数据是重复的。对于简单的数据而言，这没有问题，但是如果const数据包含庞大的数组，就不能视而不见了。

## 总结

因此，可以用一句话总结，const限定符的作用就是把声明为const的数据（变量、指针、数组、结构等）保护起来，它们具有只读属性的，不能被改变。

接下来的博客将继续分析volatile、restrict和_Atomic类型限定符。

---------------------

参考资料：

史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.