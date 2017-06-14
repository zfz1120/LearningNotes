# 嵌入式实时操作系统rtems的特点及研究现状

<center>

<img src="image/广西大学图书馆.jpg" width="500">

广西大学图书馆-[百度图片](http://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%B9%BF%E8%A5%BF%E5%A4%A7%E5%AD%A6%E5%9B%BE%E4%B9%A6%E9%A6%86&step_word=&hs=2&pn=5&spn=0&di=158716482210&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=641542887%2C1669061435&os=171474598%2C2511470263&simid=3455888123%2C394794456&adpicid=0&lpn=0&ln=1917&fr=&fmq=1496895916983_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fimg1.youzy.cn%2Fcontent%2Fmedia%2Fthumbs%2Fp00031970_763.jpeg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3By57zy_z%26e3BvgAzdH3FC5ssj2jAzdH3F800cAzdH3Fi54j_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)

</center>

## RTEMS简介[^1]

![rtemslogo](image/rtemslogo.png)

RTEMS是一个开源的无版税实时嵌入操作系统RTOS。它最早用于美国国防系统，早期的名称为实时导弹系统(Real Time Executive for Missile Systems，后来改名为实时军用系统(Real Time Executive for Military Systems，现在由OAR公司负责版本的升级与维护。目前无论是航空航天、军工，还是民用领域RTEMS都有着极为广泛的应用。同大多数嵌入式操作系统一样，RTEMS采用微内核设计思想，将内核主要功能集成在一个小的执行体中，附加的功能在包裹内核层的外层实现，应用可以根据实际系统配置，裁剪、链接相应的资源。另外RTEMS提供了大量的资源管理接口，很大程度上加速了应用程序开发。RTEMS提供简单和灵活的实时多处理器功能。RTEMS的内核既适用于紧藕合，又适用于松藕合目标系统硬件的配置。此外，RTEMS还支持由同构和异构混合的处理器组成的系统。虽然RTEMS提出了对多处理器进行支持的设计思路并对多处理器支持层的接口进行了定义，但是具体到某个系统，因为涉及到系统结构的不同，多处理器通信层的实现需要根据实际的硬件结构进行设计。在对支持多核的操作系统的研究和设计中，多核的任务分配是首要解决的问题，是提高系统性能的重要途径。国内外很多组织都对其进行了深入的探讨。

## rtems系统特点[^2]

从[体系结构](http://baike.baidu.com/item/%E4%BD%93%E7%B3%BB%E7%BB%93%E6%9E%84)上来看，RTEMS是[微内核](http://baike.baidu.com/item/%E5%BE%AE%E5%86%85%E6%A0%B8)[抢占式](http://baike.baidu.com/item/%E6%8A%A2%E5%8D%A0%E5%BC%8F)的实时系统，他具有下面的优点：

◆优秀的实时性能

◆支持硬实时和软实时（可抢占内核）

◆支持优先级[继承](http://baike.baidu.com/item/%E7%BB%A7%E6%89%BF)，防止优先级反转

◆支持单调周期调度

◆支持优先级高度协议

◆非常的稳定

◆运行速度快

◆支持多种CPU，无论是[ARM](http://baike.baidu.com/item/ARM/7518299)， MIPS，PowerPC，i386还是DSP，AVR，Zilog，都可以找到对应的BSP。

◆高度可剪裁内核（目标系统小只有30KB；大可上百兆）1,2,3

◆占用系统资源小，在32位系统中最小的[内核](http://baike.baidu.com/item/%E5%86%85%E6%A0%B8)只有30Kb左右1,2

◆支持多处理器（不同于SMP，RTEMS中多个处理器是协作关系）

◆提供POSIX API，Linux/UNIX下的程序可以方便移植

◆提供完整的BSD的TCP/IP协议栈以及[FTP](http://baike.baidu.com/item/FTP/13839)、WebServer、NFS等服务

◆使用面向对象思想设计，可以大大缩短开发周期

◆核心代码使用C/C++写作，可移植性好

◆支持ISO/ANSI C库

◆支持ISO/ANSI C++库以及STL库

◆支持精简的可重入glibc库

◆支持[图形用户界面](http://baike.baidu.com/item/%E5%9B%BE%E5%BD%A2%E7%94%A8%E6%88%B7%E7%95%8C%E9%9D%A2)（Microwindows/Nano-X）

◆支持文件系统（FAT，IMFS等）

◆支持多种调试模式（包括GDB，DDD，串口调试，以太网调试）

◆支持32位处理器，Tiny RTEMS项目将对8位和16位处理器进行支持2

◆支持JAVA虚拟机

（注1：最小[内核](http://baike.baidu.com/item/%E5%86%85%E6%A0%B8)指的是只包含BSP、任务调度、[内存模块](http://baike.baidu.com/item/%E5%86%85%E5%AD%98%E6%A8%A1%E5%9D%97)这些功能的内核。它的大小和CPU指令集、外设多少、[二进制代码](http://baike.baidu.com/item/%E4%BA%8C%E8%BF%9B%E5%88%B6%E4%BB%A3%E7%A0%81)格式等相关。CPU是ARM7时，产生的ELF格式标准ARM目标可以减少到46kb。通常来说如果只需要最主要的功能，未压缩目标目标可以控制在60kb([内核](http://baike.baidu.com/item/%E5%86%85%E6%A0%B8)+BSP+简单应用)，这比起Linux2.4 压缩后还有700K的庞大体积来说,更适合成本体积敏感的应用）

（注2：现在也有hacker主持Tiny RTEMS项目，该项目中，未压缩的最小的RTEMS bin镜像([内核](http://baike.baidu.com/item/%E5%86%85%E6%A0%B8)+BSP)只有20kb。该项目将RTEMS id变成了16bit了，此外该项目将BSD TCP/IP换成了LWIP。这样RTEMS变成了能给8bit和16bit用户使用的小型RTOS，COOL!!。）

（注3：如果只是RTEMS可管理的[存储空间](http://baike.baidu.com/item/%E5%AD%98%E5%82%A8%E7%A9%BA%E9%97%B4)，rtems.com公布的应用中，基于RTEMS的飞行记录仪提供多达8G的存储空间。）

RTEMS在性能上丝毫不输于VxWorks，它和VxWorks以及RtLinux的性能比较可以参考[《RTEMS简介》](http://www.360doc.com/content/10/0916/11/1862483_54060879.shtml)。他在全球有不少的用户，尤其是在通信、航空航天、工业控制、军事等领域有着非常广泛的应用，在系统实现上，RTEMS和VxWorks以及NucleusPlus的实现基本相同。

## 常见的RTOS比较[^3]

2003年加拿大航天局经过研究 , 从 48种 RTOS中挑出的几种根据实际综合性能测试结果排的名次：

<center>

<img src="image\rtos测试排名1.png">

<img src="image\rtos测试排名2.png">

四种rtos的特点比较：

<img src="image\四种嵌入式操作系统比较.png">

</center>

## RTEMS研究现状[^4]

目前RTEMS系统的发展很迅速，在全世界的使用量也越来越多。这主要是由于RTEMS不但开源免版税，而且具有功能强大、模块化设计、开放源码、支持多种硬件平台、函数接口遵循POSIX实时扩展的工业标准和国际标准等优点，并且它还是第一个完全面向对象的RTOS。这也使基于RTEMS的应用程序开发速度相对较快，开发费用相对较低。下面是近年来RTEMS系统的国内外研究现状。

2006年5月，捷克Czech Technical University in Prague Faculty of Electrical Engineering大学的Martin Molnar等人提出在RTEMS系统中利用EDF调度策略替换标准RTEMS系统的调度算法的一种解决方案，该方案提出并实现了利用红黑树数据结构中的每个节点来表示EDF就绪队列任务。这种结构具有线性时间复杂度，在最坏情况下，处理就绪队列的时间复杂度是O(log2 n)。

2006年，国防科学技术大学航天与材料工程学院的谭琦等人对RTEMS任务的通信和同步机制进行了详细的剖析，并对RTEMS消息机制与传统消息机制的差异进行了对比。以形式化的语言定义了RTEMS消息机制，并且创建了其消息通信模型，借助树形结构详细剖析了消息创建的指令。

  2009年，中国科学院软件研究所的阎森等人以RTEMS为原型提出并实现了RTEMS实时进程，该设计将RTEMS操作系统内核与应用程序隔离，使二者运行在不同的特权级别下，应用程序的错误不会导致操作系统崩溃，从而提高了整个系统的可靠性;同时对内核内存管理和地址映射机制进优化，保证了原有系统的性能。

在国外，美国对于RTEMS的研究起步是最早的，诞生在20世纪80年代，早期被称为实时导弹控制系统(Real Time Executive for Missile Systems)曾经被用于美国的“爱国者”导弹系统。后来由于其用途越来越广泛将其名称改为实时军用系统(Real Time Executive for Military Systems , RTEMS ) 。 RTEMS系统在1999年的时候开放源码。从那个时候开始，无论公司或者个人都可以利用其进行开发，不必像使用类似于VxWorks,  WinCE和} C/O S等需要考虑版税问题;也不用像使用Linux系列的系统一样需要遵守GNL〕规范，并不要求将自己修改和添加的源代码公诸于众，可以设计一些保密性比较强的产品，因此它是非常适合开发商业和国防应用。因此它曾被移殖到多种不同类型的处理器平台，比如有ARM, PowerPC, i386等。 RTEMS被设计为支持多种开放的API如uITRON和POSIX，也被一些EPICS站点所使用，在全球包括比较著名的朗讯、Motorola等公司对其已经有较多的研究，现在由OAR  Corporation公司负责管理RTEMS项目的维护与版本升级工作。

在国内，近年来以RTEMS为基础的嵌入式RTOS的发展比较活跃，比如中科院软件研究所将其移植到自主研发的高铁上，中国航天院利用其实现一些实时系统软件的开发，另外在军事、通信、航空、航天等高精尖技术及实时性要求极高的领域中基本上都有所涉及。此外中国科学院研究生院的学位论文《实时操作系统RTEMS及其相关控制技术的研究》中了就RTEMS的相关控制技术进行了详细的介绍，我国的一些大学目前也对 RTEMS进行了诸多的研究，如:哈尔滨工业大学、清华大学、北京航空航天大学、国防科学技术大学和西安电子科技大学等，另外国内还有不少公司或明或暗的将RTEMS系统改成自主创新的实时系统。

 总的来看，目前RTEMS在通信、航空航天、工业控制、军事等领域都有着非常广泛的研究和应用，但是国内对RTEMS操作系统的研究水平与国外相比差距还比较大，而且国内的RTEMS市场占有率还很低。另外虽然RTEMS在系统实现上和VxWorks以及NucleusPlus等的实现基本相似，但出于保密的要求，不少RTEMS的应用工程师无法将其利用RTEMS编写的BSP和应用公布出来，导致RTEMS相关的可用资源远远不够。

[^1]: 牛莹姣. 支持多核处理器的RTEMS嵌入式操作系统的研究[D].哈尔滨工程大学,2013.
[^2]: 百度百科-[RTEMS](http://baike.baidu.com/link?url=UxQswz6qG8rS1mak9maHlf4U8Bg4x-yudVPe30dKqKu911UC2rEk4__gdN_ZL7mBgHAUs2RHTZYgfxsX8VQk-K)
[^3]: 孙鲁毅. 四种流行的嵌入式实时操作系统的比较研究——VxWorks,QNX,ucLinux,RTEMS[J]. 计算机应用与软件,2007,(08):196-197.
[^4]: 刘建东. 基于RTEMS的任务调度与通信机制的研究[D].哈尔滨工程大学,2013.