# VS调用Matlab Engine方法

对轨迹规划或c/matlab混合编程感兴趣的朋友可以分别关注OTPL开源项目的这两部分代码：https://github.com/libing403/OTPL和https://github.com/libing403/OTPL/tree/master/OTPL/TestDemo/MatlabEngineCode

该项目主要以下面这两本书的理论为基础进行开发：

Trajectory Planning for Automatic Machines and Robots;

The NURBS Book

-----------

Matlab 主要面对科学计算、可视化以及交互式程序设计的高科技计算环境，但由于Matlab开发平台上开发的程序不能脱离Matlab运行环境，因而在处理一些实际应用问题时显得灵活性不足，而VC++则在一定程度上能够弥补这一缺陷。而c语言不方便进行数据可视化处理，使得一些必须用c语言实现的程序难以测试分析其结果。因此，将二者结合共用，各献其长，可以为科研工作和工程开发提供更为强大的技术支持。

##配置VS项目属性

我使用的环境为

x86

Windows 7　

VS2015

MATLAB R2016a（其他版本类似）

在建立的VS项目中进行以下设置

1.配置属性->VC++目录->包含目录

编辑为：Matlab安装路径下 ...\extern\include;

2.配置属性->VC++目录->库目录

编辑为：Matlab安装路径下 ...\extern\lib;

3.配置属性->链接器->输入->附加依赖项

增加：libeng.lib;libmx.lib;libmex.lib;libmat.lib(这里加上程序中需要用到的lib）

## 系统环境变量

PATH里添加D:\MatLab\R2010a\bin\win64; 帮助VS找到MATLAB的提供的动态链接库。

**注册MATLAB服务器**：cmd，在D:\MatLab\R2010a\bin目录下运行

```
matlab \regserver
```

有时候在安装的时候就注册了，这个命令不运行也可以。

##在VS中调用matlab引擎

###包含头文件

```
#include "engine.h"
```

###打开引擎

```
Engine* pEng = NULL;
    if (!(pEng = engOpen(NULL)))
    {
        printf("Open matlab enging fail!");
        getchar();
        return -1;
    }
```

###向matlab工作空间设置/获取数据常用的函数

int engPutVariable(Engine *ep, const char *name, const mxArray *pm)

设置一个变量数组的值

mxArray *engGetVariable(Engine *ep, const char *name)获取一个变量

int engEvalString(Engine* ep, const char* string)执行Matlab表达式

###关闭引擎

```
if(pEng)
    engClose(pEng);
```



##示例

```c
#include "engine.h"
int main()
{
	int ret = 0;
	Engine* eg = NULL;
	if (!(eg = engOpen(NULL)))
	{
		printf("Open matlab enging fail!");
		return 1;
	}
	double xtemp[dataNum] = { 0 };
	double ytemp[dataNum] = { 0 };
	for (int i = 0; i < dataNum; i++)
	{
		xtemp[i] = i * 2.0 * 3.1415926 / 100.0;
		ytemp[i] = sin(xtemp[i]);
	}
	mxArray *X = mxCreateDoubleMatrix(1, dataNum, mxREAL);//创建matlab存储数据的指针
	mxArray *Y = mxCreateDoubleMatrix(1, dataNum, mxREAL);
	
	memcpy(mxGetPr(X), xtemp, dataNum * sizeof(double)); //数据复制
	memcpy(mxGetPr(Y), ytemp, dataNum * sizeof(double));

	if ((ret = engPutVariable(eg, "X", X)) != 0)   //把数据传递到matlab工作空间,并命名为X
		printf("engPutVariable error：%d\n", ret);
	if ((ret = engPutVariable(eg, "Y", Y)) != 0)
		printf("engPutVariable error：%d\n", ret);
	engEvalString(eg, "plot(X,Y)");//运行绘图命令
	getchar();
	if(eg)
		engClose(eg);
	return 0;
}
```

结果如下图所示

![示例](image\matlab引擎绘图示例.jpg)



##编写matlab命令封装函数

从上面的编程可以看出，调用matlab进行绘图过程也显得比较繁琐，例如要创建变量，复制内存数据，运行命令表达式等一系列操作。为了像在matlab中一样调用运行matlab命令的体验，可以把matlab的命令封装的c语言的函数。例如，下面是对plot命令的封装:

```c
int mat_plot(Engine *eg, double *x, double *y, int N, char *LineStyle, double LineWidth, double MarkerSize)
{
	int ret = 0;
	mxArray *X = mxCreateDoubleMatrix(1, N, mxREAL);
	mxArray *Y = mxCreateDoubleMatrix(1, N, mxREAL);
	mxArray *MS = mxCreateDoubleScalar(MarkerSize);
	memcpy(mxGetPr(X), x, N * sizeof(double));
	memcpy(mxGetPr(Y), y, N * sizeof(double));

	if ((ret = engPutVariable(eg, "X", X)) != 0)
		printf("engPutVariable error：%d\n", ret);
	if ((ret = engPutVariable(eg, "Y", Y)) != 0)
		printf("engPutVariable error：%d\n", ret);

	//gennerate the plot command
	char plotCommand[256] = "fig=plot(X,Y,'";
	//set line style and marker
	if (strlen(LineStyle) > 0)
		strncat(plotCommand, LineStyle, strlen(LineStyle));
	else
	{
		strncat(plotCommand, "-", strlen("-"));
	}
	strncat(plotCommand, "',", strlen(LineStyle));

	char temp[20] = "";
	//set line width
	if (LineWidth < 1.0)
		LineWidth = 1.0;
	strncat(plotCommand, "'LineWidth',", strlen("'LineWidth',"));
	memset(temp, 0, sizeof(temp));
	sprintf(temp, "%f,", LineWidth);
	strncat(plotCommand, temp, strlen(temp));

	//set marker size
	strncat(plotCommand, "'MarkerSize',", strlen("'MarkerSize',"));
	sprintf(temp, "%f", MarkerSize);
	strncat(plotCommand, temp, strlen(temp));
	strncat(plotCommand, ");", strlen(temp));

	//plot
	if ((ret = engEvalString(eg, plotCommand)) != 0)
	{
		printf("\nplot Command error：%s\n", plotCommand);
		return ret;
	}
	engEvalString(eg, "set(gcf,'color','w');");
	printf("plot Command ok：%s\n", plotCommand);
	//destroy mxArray,but they are still in matlab workspace
	mxDestroyArray(X);
	mxDestroyArray(Y);
	return 0;
}
```

这样使用起matlab命令就方便多了，例如我要用c语言里运算的数据来画图，直接调用封装的函数就可以了

`mat_plot(eg, xtemp, ytemp, dataNum, "-r", 1, 5);`

上面参数的函数

eg：指向打开的matlab引擎指针

xtemp：x坐标数据

ytemp：y轴坐标数据

dataNum：数据个数

“-r”:线型，颜色（还可以设置标记例如“--r*”）

1：线宽

5：标记大小

这样就不用关心数据是怎样传递数据到matlab和怎样运行画图命令的。封装函数写得好些，就可以像matlab里面使用更像，例如直接设置线型，线宽。

但是matlab的命令非常庞大，仅凭一人之力难以做到一个好用的，功能齐全接口函数库。因此，有兴趣的朋友可以为此项目贡献力量。该项目存放在github：https://github.com/libing403/OTPL/tree/master/OTPL/TestDemo/MatlabEngineCode

要引用该接口函数，只需包含[MatlabEnginePlot.c](https://github.com/libing403/OTPL/blob/master/OTPL/TestDemo/MatlabEngineCode/MatlabEnginePlot.c)和[MatlabEnginePlot.h](https://github.com/libing403/OTPL/blob/master/OTPL/TestDemo/MatlabEngineCode/MatlabEnginePlot.h)这两个文件即可

如下图所示

![调用文件](image/调用matlab引擎的文件.jpg)

大家注意到，这个matlab命令函数封装函数库接口只是OTPL（Open Trajectory Planning Library）开源项目的一部分代码，主要用于测试轨迹规划的c算法库。

##小结
以前对c算法进行测试时，需要把c产生的数据导数到matlab，再进行绘图，看效果。这样既要写c语言程序，还得专门写matlab程序进行测试，而且要绘制动态图形就特别麻烦。现在这样通过直接在c/c++调用matlab引擎进行数据可视化处理，可以在C语言环境里，调用matlab几乎所有命令。要是把matlab命令封装好，就跟在matlab里画图一样方便，可以极大提高开发效率。