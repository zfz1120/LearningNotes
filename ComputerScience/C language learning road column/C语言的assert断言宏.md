# C语言的assert断言宏

<center>

<img src="image\锲而不舍金石可镂.jpg" >

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E5%8A%B1%E5%BF%97%E5%8F%A4%E8%AF%97&step_word=&hs=0&pn=46&spn=0&di=204560259200&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=2807626270%2C474016693&os=1689687971%2C3519569021&simid=4178345405%2C598310225&adpicid=0&lpn=0&ln=1971&fr=&fmq=1497547572950_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fwww.xhxsw88.cn%2Fuploads%2Fallimg%2F140709%2F227-140F9193Q5595.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bxixfobb_z%26e3BvgAzdH3Fstzit4tg2ywgAzdH3Fdbmmc_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

assert宏的原型定义在`<assert.h>`中，其作用是如果它的条件返回错误，则终止程序执行，原型定义：
`#include <assert.h>`
void assert( int expression );

​      assert的作用是现计算表达式 expression ，如果其值为假（即为0），那么它先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行。

如果assert()终止了程序，它首先会显示失败的测试、包含测试的文件名和行号。

示例：

```c
/* assert.c -- use assert() */
#include <stdio.h>
#include <math.h>
#include <assert.h>
int main()
{
    double x, y, z;
    
    puts("Enter a pair of numbers (0 0 to quit): ");
    while (scanf("%lf%lf", &x, &y) == 2
           && (x != 0 || y != 0))
    {
        z = x * x - y * y;  /* should be + */
        assert(z >= 0);
        printf("answer is %f\n", sqrt(z));
        puts("Next pair of numbers: ");
    }
    puts("Done");
    
    return 0;
}
```

下面是该程序的运行示例：

```tex
Enter a pair of numbers (0 0 to quit):
4 3    [用户输入]
answer is 2.645751
Next pair of numbers:
5 3    [用户输入]
answer is 4.000000
Next pair of numbers:
3 5    [用户输入]
assertion "z >= 0" failed: file "assert.c", line 14, function: main
```

该程序在求平方根之前，该程序断言z是否大于0或等于0。程序还错误地减去一个值而不是加上一个值，故意让z得不到合适的值。

具体的错误提示音编译器而异。这条消息指明的是没有满足z>=0的条件。

用if语句也能完成类似的任务：

```c
if (z<0)
  {
    puts("z less than 0");
    abort();
  }
```

但是使用asset()有几个好处：它不仅能自动标识文件和出问题的行号，还有一种无需修改代码就能开启或关闭assert()的机制。在调试结束后，可以通过在包含`#include <assert.h>`的语句之前插入` #define NDEBUG `来禁用assert调用，示例代码如下：

```c
#include <stdio.h>
#define NDEBUG
#include <assert.h>
```

重新编译程序，这样编译器就会禁用文件中的所有assert()语句。如果程序又出现问题，可以移除这条`#define NDEBUG `指令，或者把它注释掉，然后重新编译，这样就重新启用了assert()语句了。

使用assert的**缺点是，频繁的调用会极大的影响程序的性能，增加额外的开销。**

**一些建议：**

- 使用断言捕捉不应该发生的非法情况。不要混淆非法情况与错误情况之间的区别，后者是必然存在的并且是一定要作出处理的。
- 在函数的入口处，使用断言检查参数的有效性（合法性）。
- 在编写函数时，要进行反复的考查，并且自问：“我打算做哪些假定？”一旦确定了的假定，就要使用断言对假定进行检查。
- 一般教科书都鼓励程序员们进行防错设计，但要记住这种编程风格可能会隐瞒错误。当进行防错设计时，如果“不可能发生”的事情的确发生了，则要使用断言进行报警。

---

参考资料：

[1]《关于C语言的assert（断言）》--[CSDN博客](http://blog.csdn.net/engrossment/article/details/8118234)

[2] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.