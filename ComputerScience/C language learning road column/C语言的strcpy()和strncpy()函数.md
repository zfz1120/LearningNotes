# C语言的strcpy()和strncpy()函数

<center>

<img src="image\长风破浪会有时.jpg"width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E9%95%BF%E9%A3%8E%E7%A0%B4%E6%B5%AA%E4%BC%9A%E6%9C%89%E6%97%B6&step_word=&hs=0&pn=3&spn=0&di=167468385260&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=591986581%2C2455687456&os=2190941045%2C4176694097&simid=3443128132%2C407618496&adpicid=0&lpn=0&ln=1966&fr=&fmq=1497543891556_R&fm=rs2&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=%E9%95%BF%E9%A3%8E%E7%A0%B4%E6%B5%AA%E4%BC%9A%E6%9C%89%E6%97%B6%20%E7%9B%B4%E6%8C%82%E4%BA%91%E5%B8%86%E6%B5%8E%E6%B2%A7%E6%B5%B7&objurl=http%3A%2F%2Fpic2.ooopic.com%2F13%2F81%2F46%2F77b1OOOPICce.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fojtst_z%26e3B555rtv_z%26e3Bv54AzdH3Fojtst_8nb89m00_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)*

</center>

## strcpy()函数

strcpy() 函数用来复制字符串，其原型为：
​    `char *strcpy(char *dest, const char *src);`

【参数】dest 为目标字符串指针，src 为源字符串指针。

注意：src 和 dest 所指的内存区域不能重叠，且 dest 必须有足够的空间放置 src 所包含的字符串（包含结束符NULL）。

【返回值】成功执行后返回目标数组指针 dest。

strcpy() 把src所指的由NULL结束的字符串复制到dest 所指的数组中，返回指向 dest 字符串的起始地址。

注意：如果参数 dest 所指的内存空间不够大，可能会造成缓冲溢出(buffer Overflow)的错误情况，在编写程序时请特别留意，或者用strncpy()来取代。

示例：

```c
/* copy1.c -- strcpy() demo */
#include <stdio.h>
#include <string.h>  // declares strcpy()
#define SIZE 40
#define LIM 5
char * s_gets(char * st, int n);

int main(void)
{
    char qwords[LIM][SIZE];
    char temp[SIZE];
    int i = 0;
    
    printf("Enter %d words beginning with q:\n", LIM);
    while (i < LIM && s_gets(temp, SIZE))
    {
        if (temp[0] != 'q')
            printf("%s doesn't begin with q!\n", temp);
        else
        {
            strcpy(qwords[i], temp);
            i++;
        }
    }
    puts("Here are the words accepted:");
    for (i = 0; i < LIM; i++)
        puts(qwords[i]);
    
    return 0;
}

char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;
    
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else // must have words[i] == '\0'
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}
```

该程序要求用户输入以q开头的单词，该程序把输入拷贝至一个临时数组中，如果第一个字母是q，程序调用strcpy()把整个字符串从临时数组拷贝至目标数组中。strcpy()函数相当于字符串赋值运算符。

该程序的运行示例如下：

```tex
Enter 5 words beginning with q:
quackery  [用户输入]
quasar    [用户输入]
quilt     [用户输入]
quotient  [用户输入]
no more   [用户输入]
no more doesn't begin with q!
quiz      [用户输入]
Here are the words accepted:
quackery
quasar
quilt
quotient
quiz
```

strcpy的其他属性：

- strcpy()的返回类型是char *，该函数返回的是第1个参数的值，即一个字符的地址
- 第一个参数不必指向数组的开始，这个属性可用于拷贝数组的一部分。
- strcpy()把源字符串中的空字符也拷贝在内。

## strncpy()函数

strncpy()用来复制字符串的前n个字符，其原型为：
​    char * strncpy(char *dest, const char *src, size_t n);

【参数说明】dest 为目标字符串指针，src 为源字符串指针。

strncpy()会将字符串src前n个字符拷贝到字符串dest。

不像strcpy()，strncpy()不会向dest追加结束标记'\0'，这就引发了很多不合常理的问题。

注意：src 和 dest 所指的内存区域不能重叠，且 dest 必须有足够的空间放置n个字符。

【返回值】返回字符串dest。



---

参考资料：

[1] C语言strcpy()函数：字符串复制.--[来源](http://c.biancheng.net/cpp/html/2540.html)

[2] C语言strncpy()函数：复制字符串的前n个字符.--[来源](http://c.biancheng.net/cpp/html/170.html)

[3] 史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.