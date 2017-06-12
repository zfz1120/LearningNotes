## C语言的字符串函数strcmp()和strcnmp()

<center>
<img src="image\上善若水.jpg" width="500">

*图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E4%B8%8A%E5%96%84%E8%8B%A5%E6%B0%B4%20%E6%B0%B4%E5%96%84%E5%88%A9%E4%B8%87%E7%89%A9%E8%80%8C%E4%B8%8D%E4%BA%89&step_word=&hs=0&pn=0&spn=0&di=197195125380&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=0&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=undefined&cs=3014436928%2C408636082&os=2774492824%2C3633186762&simid=4270932706%2C846333430&adpicid=0&lpn=0&ln=1952&fr=&fmq=1497231032461_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fimg319.ph.126.net%2F8bw1P6ifPhco4NR_0fxQag%3D%3D%2F3827496733311898932.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fks52_z%26e3B8mn_z%26e3Bv54AzdH3Ffvstktg288da%408dmAzdH3Fks52AzdH3FfpwptvAzdH3F8db0baaldda8abd0b9n9c00aAzdH3F&gsm=0&rpstart=0&rpnum=0)*

</center>

## strcmp()函数简介

strcmp() 用来比较字符串（区分大小写），其原型为：
​    int strcmp(const char *s1, const char *s2);

【参数】s1, s2 为需要比较的两个字符串。

字符串大小的比较是以ASCII 码表上的顺序来决定，此顺序亦为字符的值。strcmp()首先将s1 第一个字符值减去s2 第一个字符值，若差值为0 则再继续比较下个字符，若差值不为0 则将差值返回。但是并不是所有系统都返回差值，有的系统只返回0,1和-1三个值。

【返回值】若参数s1 和s2 字符串相同则返回0。s1 若大于s2 则返回大于0 的值。s1 若小于s2 则返回小于0 的值。

注意，strcmp()可以比较所有的字符，不只是字母。

注意：strcmp() 以二进制的方式进行比较，不会考虑多字节或宽字节字符；如果考虑到本地化的需求，请使用 [strcoll()](http://c.biancheng.net/cpp/html/163.html) 函数。

## strcmp的返回值

在有的系统中，按ASCII表中，如果第一个字符串在第二个字符串前面，则返回负数；如果两个字符串相同则返回0；如果第一个字符串在第二个字符串后面，返回正数。

注意，不同的系统返回值有可能不一样，取决于系统的实现。有的系统分别返回-1,0,1。在另外的一些系统中，有可能值返回ASCII的差值。

示例：

```c
/* compback.c -- strcmp returns */
#include <stdio.h>
#include <string.h>
int main(void)
{
    
    printf("strcmp(\"A\", \"A\") is ");
    printf("%d\n", strcmp("A", "A"));
    
    printf("strcmp(\"A\", \"B\") is ");
    printf("%d\n", strcmp("A", "B"));
    
    printf("strcmp(\"B\", \"A\") is ");
    printf("%d\n", strcmp("B", "A"));
    
    printf("strcmp(\"C\", \"A\") is ");
    printf("%d\n", strcmp("C", "A"));
    
    printf("strcmp(\"Z\", \"a\") is ");
    printf("%d\n", strcmp("Z", "a"));
    
    printf("strcmp(\"apples\", \"apple\") is ");
    printf("%d\n", strcmp("apples", "apple"));
    
    return 0;
}
```

例如上面程序在我的系统中输出如下：

```tex
strcmp("A", "A") is 0
strcmp("A", "B") is -1
strcmp("B", "A") is 1
strcmp("C", "A") is 1
strcmp("Z", "a") is -1
strcmp("apples", "apple") is 1
```

在另外一些系统实现中，返回两个字符的差值:

```tex
strcmp("A", "A") is 0
strcmp("A", "B") is -1
strcmp("B", "A") is 1
strcmp("C", "A") is 2
strcmp("Z", "a") is -7
strcmp("apples", "apple") is 115
```

大多数情况下，strcmp()返回的具体值并不重要，我们通常只在意该值是0还是非0(即比较的两个字符串是否相等)。或者案子福排序字符串，在这种情况下，需要知道比较的结果为正、为负还是为0.

## strncmp()函数简介

strncmp() 用来比较两个字符串的前n个字符，区分大小写，其原型为：
​    int strncmp ( const char * str1, const char * str2, size_t n );

【参数】str1, str2 为需要比较的两个字符串，n为要比较的字符的数目。

字符串大小的比较是以ASCII 码表上的顺序来决定，此顺序亦为字符的值。strncmp()首先将s1 第一个字符值减去s2 第一个字符值，若差值为0 则再继续比较下个字符，直到字符结束标志'\0'，若差值不为0，则将差值返回。例如字符串"Ac"和"ba"比较则会返回字符"A"(65)和'b'(98)的差值(-33)。

注意：要比较的字符包括字符串结束标志'\0'，而且一旦遇到'\0'就结束比较，无论n是多少，不再继续比较后边的字符。

【返回值】若str1与str2的前n个字符相同，则返回0；若s1大于s2，则返回大于0的值；若s1 若小于s2，则返回小于0的值。

注意：如果两个字符不同，GCC返回该字符对应的ASCII码的差值，VC返回-1或1。但是让人为难的是，[strnicmp()](http://c.biancheng.net/cpp/html/2718.html)、[strcmp()](http://c.biancheng.net/cpp/html/162.html)、[stricmp()](http://c.biancheng.net/cpp/html/2713.html)在GCC和VC下都返回-1或1，而不是ASCII的差值。

示例：

例如，要查找以"astro"开头的字符串，可以限定函数只查找这5个字符。

```c
/* starsrch.c -- use strncmp() */
#include <stdio.h>
#include <string.h>
#define LISTSIZE 6
int main()
{
    const char * list[LISTSIZE] =
    {
        "astronomy", "astounding",
        "astrophysics", "ostracize",
        "asterism", "astrophobia"
    };
    int count = 0;
    int i;
    
    for (i = 0; i < LISTSIZE; i++)
        if (strncmp(list[i],"astro", 5) == 0)
        {
            printf("Found: %s\n", list[i]);
            count++;
        }
    printf("The list contained %d words beginning"
           " with astro.\n", count);
    
    return 0;
}
```

下面是该程序的输出

```tex
Found: astronomy
Found: astrophysics
Found: astrophobia
The list contained 3 words beginning with astro.
```



---

参考资料：

[1]  史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.

[2] C语言strcmp()函数：比较字符串（区分大小写）-[来源](http://c.biancheng.net/cpp/html/162.html)

[3] C语言strncmp()函数：比较字符串的前n个字符（区分大小写）-[来源](http://c.biancheng.net/cpp/html/2717.html)