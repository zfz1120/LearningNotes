## Windows编程--memset函数

转载自：百度百科[memset](https://baike.baidu.com/item/memset/4747579?fr=aladdin)，博客园[memset函数使用详解](http://www.cnblogs.com/xiaolongchase/archive/2011/10/22/2221326.html)

## memset函数

memset是计算机中C/C++语言函数。将s所指向的某一块内存中的前n个 [字节](https://baike.baidu.com/item/%E5%AD%97%E8%8A%82)的内容全部设置为ch指定的[ASCII](https://baike.baidu.com/item/ASCII)值， 第一个值为指定的内存地址，块的大小由第三个[参数](https://baike.baidu.com/item/%E5%8F%82%E6%95%B0)指定，这个函数通常为新申请的内存做初始化工作， 其返回值为指向s的[指针](https://baike.baidu.com/item/%E6%8C%87%E9%92%88)。

`void *memset(void *s, int ch, size_t n);`

函数解释：将s中当前位置后面的n个字节 （typedef unsigned int size_t ）用 ch 替换并返回 s 。

memset：作用是在一段内存块中填充某个给定的值，它是对较大的[结构体](https://baike.baidu.com/item/%E7%BB%93%E6%9E%84%E4%BD%93)或[数组](https://baike.baidu.com/item/%E6%95%B0%E7%BB%84)进行清零操作的一种最快方法

​	今天做题卡在MEMSET函数的使用上了,本来以为`int a[100]; memset(a, MAX,sizeof(a));`就是将a数组全部赋值为MAX,现在才知道他的填充是以字节为单位,一般用于对字符型变量的初值进行赋值.

​	更详细的解说见百度百科 --> [http://baike.baidu.com/view/982208.htm](http://baike.baidu.com/view/982208.htm) 

1。`void *memset(void *s,int c,size_t n)`

总的作用：将已开辟内存空间 s 的首 n 个字节的值设为值 c。
2。例子

```c++
＃include
void main(){
char *s="Golden Global View";
clrscr();
memset(s,'G',6);
printf("%s",s);
getchar();
return 0;
}　
```

3。memset() 函数常用于内存空间初始化。如：

```c++
char str[100];
memset(str,0,100);
```


4。memset()的深刻内涵：用来对一段内存空间全部设置为某个字符，一般用在对定义的字符串进行初始化为‘ ’或‘/0’；例:char a[100];memset(a, '/0', sizeof(a));
memcpy用来做内存拷贝，你可以拿它拷贝任何数据类型的对象，可以指定拷贝的数据长度；例：char a[100],b[50]; memcpy(b, a, sizeof(b));注意如用sizeof(a)，会造成b的内存地址溢出。
strcpy就只能拷贝字符串了，它遇到'/0'就结束拷贝；例：char a[100],b[50];strcpy(a,b);如用strcpy(b,a)，要注意a中的字符串长度（第一个‘/0’之前）是否超过50位，如超过，则会造成b的内存地址溢出。
5.补充：一点心得
memset可以方便的清空一个结构类型的变量或数组。
如：

```c++
struct sample_struct
{
char csName[16];
int iSeq;
int iType;
};
```


对于变量
`struct sample_strcut stTest;`
一般情况下，清空stTest的方法：

```c++
stTest.csName[0]='/0';
stTest.iSeq=0;
stTest.iType=0;
```

用memset就非常方便：
`memset(&stTest,0,sizeof(struct sample_struct));`
如果是数组：
`struct sample_struct TEST[10];`
则
`memset(TEST,0,sizeof(struct sample_struct)*10);`
6。strcpy
原型：`extern char *strcpy(char *dest,char *src);`
用法：＃i nclude
功能：把src所指由NULL结束的字符串复制到dest所指的数组中。
说明：src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。
返回指向dest的指针。
memcpy
原型：`extern void *memcpy(void *dest, void *src, unsigned int count);`
用法：＃i nclude
功能：由src所指内存区域复制count个字节到dest所指内存区域。
说明：src和dest所指内存区域不能重叠，函数返回指向dest的指针。
memset
原型：`extern void *memset(void *buffer, int c, int count);`
用法：＃i nclude
功能：把buffer所指内存区域的前count个字节设置成字符c。
说明：返回指向buffer的指针。