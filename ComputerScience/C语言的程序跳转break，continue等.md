# C语言的程序跳转break，continue等

<center>

<img src="image\生命的意义在于你的态度.jpg">

图片来源-[百度图片](https://image.baidu.com/search/detail?ct=503316480&z=0&ipn=d&word=%E7%94%9F%E5%91%BD%E7%9A%84%E6%84%8F%E4%B9%89&step_word=&hs=0&pn=30&spn=0&di=109845431740&pi=0&rn=1&tn=baiduimagedetail&is=0%2C0&istype=2&ie=utf-8&oe=utf-8&in=&cl=2&lm=-1&st=-1&cs=2606392069%2C4021082059&os=572238929%2C533491974&simid=4210096969%2C630552120&adpicid=0&lpn=0&ln=1839&fr=&fmq=1496987136062_R&fm=result&ic=0&s=undefined&se=&sme=&tab=0&width=&height=&face=undefined&ist=&jit=&cg=&bdtype=0&oriquery=&objurl=http%3A%2F%2Fwww.zhaichao100.com%2Fuploads%2Fd%2F1447920768s.jpg&fromurl=ippr_z2C%24qAzdH3FAzdH3Fooo_z%26e3Bziwtviw58aa_z%26e3Bv54AzdH3F4jtojg9aaztAzdH3Ftfsip_z%26e3Bip4s&gsm=0&rpstart=0&rpnum=0)

</center>

## 引言

一般而言，程序进入循环后，在下一次循环测试之前会执行完循环体中的所有语句。continue和break语句可以根据循环体的测试结果忽略一部分循环体内容，甚至结束循环。下面介绍break、continue和goto语句的用法。

## break语句

这3中语句都能从程序流的一处跳至另一处。所有的循环和switch语句都可以使用break语句。它使程序控制跳出当前循环或switch语句的剩余部分，并继续执行更在循环或switch后面的语句。

示例：

```c
while ((ch = getchar() != EOF))
  {
    putchar(ch);
    if (ch == ' ')   //测试是否为空格
      break;//跳出当前的循环
    chcount++;
  }
```

以上程序段打印用户输入的内容并统计非空格字符。

## continue语句

所有的循环体都可以使用continue语句，但是switch语句不行。continue语句使程序控制跳出循环的剩余部分。对于while或for循环，程序执行到continue语句后会开始进入下一轮迭代。对于do while循环，对出口条件求值后，如有必要会进入下一轮迭代。

示例：

```c
while ((ch = getchar() != EOF))
  {
    putchar(ch);
    if (ch == ' ')
      continue;//跳至测试条件
    putchar(ch);
    chcount++;
  }
```

以上程序段打印用户输入的内容并统计非空格字符。

## goto语句

goto语句使程序控制跳转至相应标签语句。冒号用于分隔标签和标签语句。标签名遵守变量名命名规则。标签语句可以出现在goto语句的前面或后面。

形式：

```c
goto label;
.
.
.
label: statement
```

示例：

```c
top: ch= getchar();
.
.
.
if(ch != 'y')
 goto top;
```



就简单地这么说一下好了，希望对你有用！



-----

参考资料：

史蒂芬・普拉达. C Primer Plus (第6版) 中文版[M]. 人民邮电出版社, 2016.