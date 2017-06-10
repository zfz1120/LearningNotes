# C语言的单字符IO之getchar()和putchar()

## 引言

getchar()和putchar()每次只处理一个字符。你可能认为这种方法很低级，与我们的阅读方式相差甚远。但是，这种方法很适合计算机，而且这是绝大多数文本处理程序所用的核心方法。

## 示例

```c
/* echo.c -- repeats input */
#include <stdio.h>
int main(void)
{
    char ch;
    
    while ((ch = getchar()) != '#')
        putchar(ch);
    
    return 0;
}
```

该程序获取键盘输入的字符，并把这些字符发送到屏幕上。程序使用while循环，当读到`#`字符是停止。