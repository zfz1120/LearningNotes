# C语言的存储类别

<center>

<img src="image\广西大学荷花池.jpg" >

广西大学荷花池-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%B9%BF%E8%A5%BF%E5%A4%A7%E5%AD%A6%E8%8D%B7%E8%8A%B1%E6%B1%A0&step_word=&hs=2&pn=7&spn=0&di=220758516000&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=1035393403%2C689422438&os=2542806182%2C3699003977&simid=3413686139%2C247717549&adpicid=0&lpn=0&ln=176&fr=&fmq=1496893238217_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fwww.gxlxs2008.net%2FEditor1%2Fuploadfile%2F20160617171105199.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3B2xsxfdaab_z%26e3BgjpAzdH3Fw6ptvsjfAzdH3F9n80_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)

</center>

## 关键字

auto、extern、static、register、_Thread_local （C11）

## 一般注解

变量的存储类别取决于它的作用域、链接和存储器。存储类别由声明变量的位置和与之关联的关键字决定。定义在所有函数外部的便来那个具有文件作用域、外部链接、静态存储器。声明在函数中的变量是自动变量，付费该变量前面使用了其他关键字。它们具有块作用域、无链接、自动存储期。以static关键字声明在函数中的变量具有块作用域、无链接、静态存储期。以static关键字声明在函数外部的变量具有文件作用域、内部链接、静态存储期。

C11新增了一个存储说明符：_Thread_local。以该关键字声明的对象具有线程存储期，意思是在线程中声明的对象在该线程运行期间一直存在，且在线程开始时被初始化。因此，这种对象属于线程私有。

## 属性

下面表格总结了这些存储类别的属性：

| 存储类别    | 存储期  | 作用域  | 链接   | 如何声明                              |
| ------- | ---- | ---- | ---- | --------------------------------- |
| 自动      | 自动   | 块    | 无    | 在块中                               |
| 寄存器     | 自动   | 块    | 无    | 在块中，用关键字register                  |
| 静态、外部链接 | 静态   | 文件   | 外部   | 在所有函数外部                           |
| 静态、内部链接 | 静态   | 文件   | 内部   | 在所有函数外部，使用关键字static               |
| 静态、无链接  | 静态   | 块    | 无    | 在块中，使用关键字static                   |
| 线程、外部链接 | 线程   | 文件   | 外部   | 在所有块外部，使用关键字_Thread_local         |
| 线程、内部链接 | 线程   | 文件   | 内部   | 在所有块的外部，使用关键字static和_Thread_local |
| 线程、无链接  | 线程   | 块    | 无    | 在快中，使用关键字static和_Thread_local     |

注意，关键字extern只能用来再次声明在别处已定义过的变量。在函数外部定义变量，该变量具有外部链接属性。

出了以上介绍的存储类别，C语言还提供了动态分配内存。这种内存通过调用malloc()函数系列中的一个函数来分配。这种函数返回一个用于访问内存的指针。调用free()函数或者结束程序可以释放动态分配的内存。任何可以访问指向该内存指针的函数均可以访问这块内存。例如，一个函数可以 把这个指针的值返回给另一个函数，那么另一个函数也可以访问该指针指向的内存。