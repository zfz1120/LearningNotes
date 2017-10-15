# matlab的c程序接口mexFunction函数剖析

转载自：[mexFunction函数](http://blog.sina.com.cn/s/blog_8c84cf510100xqi2.html)

在使用MATLAB编译C/C++代码时，C/C++代码中要使用一个mexFunction函数，那么这个函数是如何定义，在编译时又是如何实现的呢？下面我将使用实例进行说明。

   如一个简单的函数：

```c
double add(double x, double y)
{
    return x + y;
 }

```

```c
 //mexFunction的定义为：
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
 {
   
  }
```

可以看到，mexFunction是没返回值的，它不是通过返回值把结果传回Matlab的，而是通过对参数plhs的赋值。mexFunction的四个参数皆是说明Matlab调用MEX文件时的具体信息，如这样调用函数时：

\>> b = 1.1; c = 2.2;

\>> a = add(b, c)

mexFunction四个参数的意思为：

nlhs = 1，说明调用语句左手面（lhs－left hand side）有一个变量，即a。

nrhs = 2，说明调用语句右手面（rhs－right hand side）有两个自变量，即b和c。

plhs是一个数组，其内容为指针，该指针指向数据类型mxArray。因为现在左手面只有一个变量，即该数组只有一个指针，plhs[0]指向的结果会赋值给a。

prhs和plhs类似,因为右手面有两个自变量，即该数组有两个指针，prhs[0]指向了b，prhs[1]指向了c。要注意prhs是const的指针数组，即不能改变其指向内容。

因为Matlab最基本的单元为array，无论是什么类型也好，如有double array、 cell array、 struct array……所以a,b,c都是array，b = 1.1便是一个1x1的double array。而在C语言中，Matlab的array使用mxArray类型来表示。所以就不难明白为什么plhs和prhs都是指向mxArray类型的指针数组。

 完整的add.c如下：

```c
include "mex.h"//使用MEX文件必须包含的头文件
//执行具体工作的C函
double add(double x, double y)
{
    return x + y;
}

// MEX文件接口函数
void mexFunction(int nlhs,mxArray *plhs[], int nrhs,const mxArray *prhs[])
{
    double *a;
    double b, c;
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    a = mxGetPr(plhs[0]);
    b = *(mxGetPr(prhs[0]));
    c = *(mxGetPr(prhs[1]));
    *a = add(b, c);
}
```

 mexFunction的内容是什么意思呢？我们知道，如果这样调用函数时：

\>> output = add(1.1, 2.2);

在未涉及具体的计算时，output的值是未知的，是未赋值的。所以在具体的程序中，我们建立一个1x1的实double矩阵（使用 mxCreateDoubleMatrix函数，其返回指向刚建立的mxArray的指针），然后令plhs[0]指向它。接着令指针a指向plhs [0]所指向的mxArray的第一个元素（使用mxGetPr函数，返回指向mxArray的首元素的指针）。同样地，我们把prhs[0]和prhs [1]所指向的元素（即1.1和2.2）取出来赋给b和c。于是我们可以把b和c作自变量传给函数add，得出给果赋给指针a所指向的mxArray中的元素。因为a是指向plhs[0]所指向的mxArray的元素，所以最后作输出时，plhs[0]所指向的mxArray赋值给output，则 output便是已计算好的结果了。

实际上mexFunction是没有这么简单的，我们要对用户的输入自变量的个数和类型进行测试，以确保输入正确。如在add函数的例子中，用户输入char array便是一种错误了。

从上面的讲述中我们总结出，MEX文件实现了一种接口，把C语言中的计算结果适当地返回给Matlab罢了。当我们已经有用C编写的大型程序时，大可不必在 Matlab里重写，只写个接口，做成MEX文件就成了。另外，在Matlab程序中的部份计算瓶颈（如循环），可通过MEX文件用C语言实现，以提高计算速度。

一个简单的MEX文件例子：用m文件建立一个1000×1000的Hilbert矩阵。

```matlab
% mextest.m

tic

m=1000;

n=1000;

a=zeros(m,n);

for i=1:1000

     for j=1:1000

         a(i,j)=1/(i+j);

     end

end

toc
```

 在matlab中新建一个Matlab_1.cpp 文件并输入以下程序：

```c
include "mex.h"

void hilb(double *y,int n)

{

    int i,j;

    for(i=0;i<n;i++)

        for(j=0;j<n;j++)

            (y+j+in)=1/((double)i+(double)j+1);

}

 

 

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])

{

    double x,*y;

    int n;

 

    if (nrhs!=1)

        mexErrMsgTxt("One inputs required.");

    if (nlhs != 1)

        mexErrMsgTxt("One output required.");

    if (!mxIsDouble(prhs[0])||mxGetN(prhs[0])*mxGetM(prhs[0])!=1)

        mexErrMsgTxt("Input must be scalars.");

    x=mxGetScalar(prhs[0]);

    plhs[0]=mxCreateDoubleMatrix(x,x,mxREAL);

    n=mxGetM(plhs[0]);

    y=mxGetPr(plhs[0]);

    hilb(y,n);

}
```





 该程序是一个C语言程序，它也实现了建立Hilbert矩阵的功能。在MATLAB命令窗口输入以下命令：`mex Matlab_1.cpp`，即可编译成功。进入该文件夹，会发现多了一个文件：Matlab_1.mexw32，其中Matlab_1.mexw32即是MEX文件。运行下面程序：

```matlab
tic
a=Matlab_1(1000);
toc
```

由上面实验看出，同样功能的MEX文件比m文件快得多。

​       MEX文件的组成与参数

MEX文件的源代码一般由两部分组成：

(1)计算过程。该过程包含了MEX文件实现计算功能的代码，是标准的C语言子程序。

(2)入口过程。该过程提供计算过程与MATLAB之间的接口，以入口函数mxFunction实现。在该过程中，通常所做的工作是检测输入、输出参数个数和类型的正确性，然后利用mx-函数得到MATLAB传递过来的变量(比如矩阵的维数、向量的地址等)，传递给计算过程。

**MEX文件的计算过程和入口过程也可以合并在一起**。但不管那种情况，都要包含#include "mex.h"，以保证入口点和接口过程的正确声明。**注意，入口过程的名称必须是mexFunction，并且包含四个参数，**即：

`void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])`

其中，参数nlhs和nrhs表示MATLAB在调用该MEX文件时等式左端和右端变量的个数，例如在MATLAB命令窗口中输入以下命令：

`[a,b,c]=Matlab_1(d,e,f,g)`

则nlhs为3，nrhs为4。

MATLAB在调用MEX文件时，输入和输出参数保存在两个`mxArray*`类型的指针数组中，分别为`prhs[]`和`plhs[]`。`prhs[0]`表示第一个输入参数，`prhs[1]`表示第二个输入参数，…，以此类推。如上例中，`d→prhs[0]，e→prhs[1]，f→prhs[2]，f→prhs[3]`。同时注意，这些参数的类型都是`mxArray *`。

**接口过程要把参数传递给计算过程**，还需要从prhs中读出矩阵的信息，这就要用到下面的mx-函数和mex-函数。