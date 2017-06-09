# C语言的内存分配malloc()和free()

<center>

<img src="image\超越自我追求卓越.jpg">

</center>

## 引言

静态数据在程序载入内存时分配，而且自动变量的数据在程序执行块时分配，并在程序离开该块时销毁。另外，C语言可以在程序运行时分配更多的内存。比如说，你做一个通讯录，但是你不能确定到底有多少人需要存储，因此你就不能确定具体需要多少内存空间，因此你可以使用动态内存分配来解决这个问题，即有一个数据需要存储的时候再分配内存给它，这样就需要使用到malloc()函数了。**该函数接受一个参数：所需内存的字节数。** 

## malloc()和free()

malloc()函数会找到合适的空闲内存块，这样的内存时匿名的。也就是说malloc()分配内存，但是不会为其赋名。因为char表示一个字节，malloc()的返回类型通常被定义为指向char的指针。然而，从ANSI C标准开始，C使用一个新的数据类型：指向void的指针。该类型相当于一个“通用指针”。malloc()函数可以用于返回指向数组的指针、指向结构的指针等，所以通常该函数的返回值会被强制转换为匹配的类型。在ANSI C中，应该坚持使用强制类型转换，提高代码的可读性。然而，把指向void的指针赋给任意类型的指针完全不用考虑类型匹配问题。**如果malloc()分配内存失败，将返回空指针。**

例子：

```c
double * ptd;
ptd= (double *) malloc(30 * sizeof(double));
```

以上代码为30个double类型的值请求内存空间，并设置ptd指向该位置。注意，指针被声明为指向一个double类型，而不是指向内含30个double类型值的块。数组名是该数组首元素的地址。因此，如果让ptd指向这块的首元素，就可以像使用数组名一样使用它。

因此，我们有3种方法创建数组的方法：

- 声明数组时，用常量表达式表示数组的维度，用静态内存或自动内存创建这种数组。
- 声明变长数组(c99新增的特性)时，用变量表达式表示数组的维度。具有这种特性的数组只能在自动内存中创建。
- 声明一个指针，调用malloc()，将其返回值赋给指针，使用指针访问数组的元素。该指针可以是静态的或自动的。

使用第二和第三种方法，可以创建动态数组。这种数组和普通数组不同，可以在程序运行时选择数组的大小和分配内存。

通常malloc()要和free()配套使用。free()函数的参数是之前malloc()返回的地址，该函数释放malloc()分配的内存。因此，动态分配内存的存储期是从调用malloc()分配内存到调用free()释放内存为止。**malloc()和free()的原型都在stdlib.h头文件中。

## 实例

使用malloc()，程序可以在运行时才确定数组的大小。如下面的例子，它把内存块的地址赋给指针ptd，然后便可以使用数组名的方式使用ptd。另外，如果内存分配失败，可以调用exit()函数结束程序，其原型在stdlib.h中。EXIT_FAILURE的值也被定义在stdlib.h中。标准提供了两个返回值以保证在多有的操作系统中都能正常工作EXIT_SUCCESS(或者，此相当于0)表示普通程序的结束，EXIT_FAILURE表示程序异常终止。一些操作系统（unix，linux和windows）还接受一些表示其他运行错误的整数值。

```c
/* dyn_arr.c -- dynamically allocated array */
#include <stdio.h>
#include <stdlib.h> /* for malloc(), free() */

int main(void)
{
    double * ptd;
    int max;
    int number;
    int i = 0;
    
    puts("What is the maximum number of type double entries?");
    if (scanf("%d", &max) != 1)
    {
        puts("Number not correctly entered -- bye.");
        exit(EXIT_FAILURE);
    }
  ptd = (double *) malloc(max * sizeof (double));
    if (ptd == NULL)
    {
        puts("Memory allocation failed. Goodbye.");
        exit(EXIT_FAILURE);
    }
    /* ptd now points to an array of max elements */
    puts("Enter the values (q to quit):");
    while (i < max && scanf("%lf", &ptd[i]) == 1)
        ++i;
    printf("Here are your %d entries:\n", number = i);
    for (i = 0; i < number; i++)
    {
        printf("%7.2f ", ptd[i]);
        if (i % 7 == 6)
            putchar('\n');
    }
    if (i % 7 != 0)
        putchar('\n');
    puts("Done.");
    free(ptd);
    
    return 0;
}
```

-------

下面是程序的运行示例。

```c
What is the maximum number of type double entries?
5
Enter the values (q to quit):
20 30 35 25 40 80
Here are your 5 entries:
  20.00   30.00   35.00   25.00   40.00
Done.
```



程序通过交互的方式让用户先确定数组的大小，我们是指数组的大小为5。虽然我们输入了6个数，但程序也只处理前5个数。



该程序通过下面的代码获取数组的大小：

```c
    if (scanf("%d", &max) != 1)
    {
        puts("Number not correctly entered -- bye.");
        exit(EXIT_FAILURE);
    }
```

接下来，分配足够的内存空间以存储用户要存入的所有数，然后把动态分配的内存地址赋值给指针ptd：

```c
  ptd = (double *) malloc(max * sizeof (double));
```

在C中，不一定要用强制类型转换（double *），但是在C++中必须使用。所以，使用强制类型转换更容易把C程序转换为C++程序。

malloc()可能分配不到所需的内存，这种情况下，该函数返回空指针，程序结束：

```c
  ptd = (double *) malloc(max * sizeof (double));
    if (ptd == NULL)
    {
        puts("Memory allocation failed. Goodbye.");
        exit(EXIT_FAILURE);
    }
```

如果程序成功分配内存，便可以把ptd视为一个有max个元素的数组名。

一些操作系统在程序结束时会自动释放动态分配的内存，但是有些系统不会。为了保险起见，记得使用free()函数释放内存，不要依赖操作系统来清理。

## free()的重要性

静态内存的数量在编译时是固定的，在程序运行期间也不会改变。自动变量使用的内存数量在程序执行期间自动增加或减少。但是动态分配的内存数量只会增加，除非用free()进行释放。假如在一个函数中用malloc()分配了内存，**但是没有用free()释放内存**。当函数结束时，作为自动变量的指针（常常会是这样）也会消失。但它指向的数据的内存仍然存在。由于指针已被销毁，所以无法访问这块内存，它也不能被重复使用，因为代码中没用调用free()释放这块内存。更坏的情况是，如果该函数在执行循环调用时，该函数会不断分配内存，而不会释放内存，有可能在循环结束前就消耗尽机器的内存了。这类问题称为**内存泄漏(memory leak)**。 因此，记得在函数末尾处调用free()函数可避免这类问题发生。



----

参考资料：

史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.