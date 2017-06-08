# C语言的restrict类型限定符

<center>

<img src="image\广西大学网络楼.jpg">

*广西大学网络楼-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%B9%BF%E8%A5%BF%E5%A4%A7%E5%AD%A6%E9%A3%8E%E6%99%AF&step_word=&hs=0&pn=92&spn=0&di=119570435050&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=712890207%2C1581876401&os=375803480%2C3794630770&simid=3266833521%2C3882849282&adpicid=0&lpn=0&ln=1966&fr=&fmq=1496915110117_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Ffile.100xuexi.com%2FXXExam%2FMatUpPT%2FImage%2F201407021422177723099.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3B8aajxw4_z%26e3Bv54AzdH3FWjkSrjvFAzdH3FEg65sDjpwts_z%26e3Bwfrx%3Ft1%3D888b9b&gsm=3c&rpstart=0&rpnum=0)*

</center>

## restrict限定符的用法

restrict关键字允许编译器优化某部分代码以更好地支持计算。它只能用于指针，表明该指针是访问该对象唯一且初始的方式。要弄明白为什么这样做有用，先看几个例子。考虑下面的代码：

```c
int ar[10];
int * restrict restar= (int *) malloc(10 * sizeof(int));
int * par= ar;
```

这里，指针restar是访问由malloc()所分配的内存的唯一且初始的方式。因此，可以用restrict关键字限定它。而指针par既不是访问ar数组中数据的初始方式，也不是唯一方式。所以不用把它设置成restrict。

现在考虑下面稍微复杂的例子，其中n是int类型：

```c
for (n=0; n<10; n++)
  {
    par[n]+=5;
    restar[n] +=5;
    ar[n] *=2;
    par[n] +=3;
    restar[n] +=3;
  }
```

由于之前声明了restar是访问它所指向的数据块的唯一且初始的方式，编译器可以把涉及restar的两条语句替换成下面的语句，效果相同：

```c
restar[n] +=8;/*可以进行替换*/
```

但是，如果把与par相关的两条语句替换成下面的语句，将导致计算错误：

```c
par[n] +=8;/*将给出错误的结果*/
```

这是因为for循环在par两次访问相同的数据之间，用ar改变了该数据的值。

在本例中，如果未使用restrict关键字，编译器必须假定最坏的情况（即，两次使用指针之间，其他的标识符可能已经改变了该数据）。如果用了restrict关键字，编译器就可以选择捷径优化计算。

restrict限定符还可以用于函数形参中的指针。这意味着编译器可以假定该函数体内其他标识符不会修改该指针指向的数据，而且编译器可以尝试对其优化，使其不做别的用途。例如，C库有两个函数用于把一个位置上的字节拷贝到另一个位置。在C99中，这两个函数的原型是：

```c
void * memcpy(void * restrict s1, const void * restrict s2, size_t n);
void *memmove(void * s1, const void * s2,size_t n);
```

这两个函数都从位置s2把n个字节拷贝到位置s1。memcpy()函数要求两个位置不重叠，但是memove()没有这样的要求。声明s1和s2为restrict说明这两个指针是访问相应数据的唯一方式，所以它们不能访问相同块的数据。这满足memcpy()函数无重叠的要去。memmove()允许重叠，它在拷贝数据时不得不更小心，以防止在使用数据之前就先覆盖了数据。

## 总结

restrict关键字有两个读者。一个是编译器，该关键字告诉编译器可以自由假定一些优化方案。另一个读者是用户，该关键字告知用户要使用满足restrict要求的参数，总而言之，编译器不会检查用户是否遵循这一限制，但是无是它可能产生严重后果。

-----------

参考资料：

史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.