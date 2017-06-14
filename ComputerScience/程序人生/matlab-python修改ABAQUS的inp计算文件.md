# python修改ABAQUS的inp计算文件

这里的函数可以与上一个博客[Matlab-python-ABAQUS数据交互及联合使用](http://blog.csdn.net/libing403/article/details/71434546)的函数接口相互配合和集成，实现matlab与Abaqus进行联合仿真计算，大体思路如下图所示。

![py_ma_inp.png](image\py_ma_inp.png)

因此这里matlab和python各写一个接口函数，实现对数据的处理。

## matlab函数

```matlab
function modify(Path,InpFile,NewData)
%modify.m
%libing403,2017-05-09
ReqFile=[Path,'\modify.txt'];
fid=fopen(ReqFile,'wt');
%把需要修改的inp文件和新数据文件的文件名、路径写入modify.txt
fprintf(fid,'%s,%s.inp,%s.txt',Path,InpFile,NewData);
fclose(fid);
system('abaqus cae noGUI=inpmodify.py');%调用python脚本修改inp数据
end
```

这里的参数(Path,InpFile,NewData)可以由matlab主程序传递过来，语句

```matlab
system('abaqus cae noGUI=inpmodify.py')
```

实现调用修改inp文件的python脚本，脚本文件名为inpmodify.py。下面给出该脚本的实现。

## python脚本

首先说明要如何修改inp中的具体什么数据。我这里inp文件abaqus-inpfile.inp包含以下一段数据，其中关键字"*Permeability, specific=1.\n"，包括换行符‘\n’。这是指定材料的渗透系数以及比重，关键字后面的28行数据指定了渗透系数随孔隙比的变化，需要替换为新的数据，共有28行数据。而且我准备了新的28数据，保存在NewData.txt文件中。

abaqus-inpfile.inp文件内容

```tex
...  
     101200., 0.149577, ,  19.7647
     28977.5, 0.147995, ,  24.2025
*Permeability, specific=1.
   1.605e-12,   1.
 5.24399e-12,  1.5
 1.21474e-11,   2.
 2.33056e-11,  2.5
 3.96889e-11,   3.
 6.22521e-11,  3.5
  9.1937e-11,   4.
 1.29675e-10,  4.5
 1.76387e-10,   5.
 2.32988e-10,  5.5
 3.00384e-10,   6.
 3.79474e-10,  6.5
 4.71152e-10,   7.
 5.76307e-10,  7.5
 6.95821e-10,   8.
 8.30574e-10,  8.5
 9.81439e-10,   9.
 1.14929e-09,  9.5
 1.33498e-09,  10.
 1.53939e-09, 10.5
 1.76336e-09,  11.
 2.00776e-09, 11.5
 2.27344e-09,  12.
 2.56125e-09, 12.5
 2.87203e-09,  13.
 3.20664e-09, 13.5
  3.5659e-09,  14.
 3.95066e-09, 14.5
*User Defined Field
*Material, name=Material-2
*Elastic
...
```

NewData.txt的数据：

```tex
 1.605e-12,   1.
 1.24399e-12,  1.5
 1.21474e-11,   2.
 1.33056e-11,  2.5
 1.96889e-11,   3.
 1.22521e-11,  3.5
 1.1937e-11,   4.
 1.29675e-10,  4.5
 1.76387e-10,   5.
 1.32988e-10,  5.5
 1.00384e-10,   6.
 1.79474e-10,  6.5
 1.71152e-10,   7.
 1.76307e-10,  7.5
 1.95821e-10,   8.
 1.30574e-10,  8.5
 1.81439e-10,   9.
 1.14929e-09,  9.5
 1.33498e-09,  10.
 1.53939e-09, 10.5
 1.76336e-09,  11.
 1.00776e-09, 11.5
 1.27344e-09,  12.
 1.56125e-09, 12.5
 1.87203e-09,  13.
 1.20664e-09, 13.5
 1.5659e-09,  14.
 1.95066e-09, 14.5
```

根据要求，编写的python脚本如下

```python
#! /user/bin/python
#- -coding: UTF-8-*-
#inpmodify.py
# 本脚本的功能是修改ABAQUS inp文件
#libing403，2017-5-7
import time
#读取inp文件的路径及文件名内容
f=open('modify.txt','r')
req=f.readline()
f.close()
req=req.split(',')
InpFile=req[0]+'/'+req[1]
NewData=req[0]+'/'+req[2]
#读取inp文件内容
fid=open(InpFile,"r")
lines=fid.readlines()
fid.close()
#找出原来的数据行
startstr="*Permeability, specific=1.\n"
startIndex=lines.index(startstr)+1
#28个行数据需要替换
endIndex=startIndex+28
#读入新数据
fid=open(NewData,"r")
newInp=fid.readlines()
fid.close()
print("%s"%newInp)
#替换原来的数据行
i=0
for Index in range(startIndex,endIndex):
    lines[Index]=newInp[i]
    i=i+1
#写入新数据，替换原来的数据
fid=open(InpFile,"w")
fid.writelines(lines)
fid.close()
#写入操作日志
meg="inpmodify message:\n inp file modify successfully\n"
fid=open("pylog.txt","a")
fid.write('%s\n'%meg)
fid.close()
```

## 应用例子

有了上面的matlab函数modify.m和python脚本inpmodify.py，那么就可以在matlab主程序中调用它们来修改inp文件了。下面是一个例子，修改之前准备好的数据。

```matlab
%example.m
%libing403,2017-07-09
clc
%inp文件的路径
Path='F:\security folder\ABAQUS WORKING\inversion_per';
%inp文件名，不需要后缀名inp
InpFile='abaqus-inpfile';
%新数据的文件名
NewData='NewData.txt';%需要后缀名txt
modify(Path,InpFile,NewData);%调用函数修改inp文件
showlogfile('pylog.txt');%显示python脚本运行的输出信息
```

其中showlogfile（）在我的另外一个博客[Matlab目录操作及fgetl函数](http://blog.csdn.net/libing403/article/details/71403025)已有介绍。运行程序后，matlab窗口显示如下消息，表明inp文件修改成功了。

![matlab修改inp文件的输出](image\matlab窗口显示pylog信息.png)

修改的inp文件中，渗透系数换成了新的数据，其他数据保持不变，如下

```tex
...   
   101200., 0.149577, ,  19.7647
     28977.5, 0.147995, ,  24.2025
*Permeability, specific=1.
 1.605e-12,   1.
 1.24399e-12,  1.5
 1.21474e-11,   2.
 1.33056e-11,  2.5
 1.96889e-11,   3.
 1.22521e-11,  3.5
 1.1937e-11,   4.
 1.29675e-10,  4.5
 1.76387e-10,   5.
 1.32988e-10,  5.5
 1.00384e-10,   6.
 1.79474e-10,  6.5
 1.71152e-10,   7.
 1.76307e-10,  7.5
 1.95821e-10,   8.
 1.30574e-10,  8.5
 1.81439e-10,   9.
 1.14929e-09,  9.5
 1.33498e-09,  10.
 1.53939e-09, 10.5
 1.76336e-09,  11.
 1.00776e-09, 11.5
 1.27344e-09,  12.
 1.56125e-09, 12.5
 1.87203e-09,  13.
 1.20664e-09, 13.5
 1.5659e-09,  14.
 1.95066e-09, 14.5
*User Defined Field
*Material, name=Material-2
*Elastic
...
```

## 小结

​      这里的接口函数具有一定的通用性，只需修改相关的参数可以适用于类似的情况。其中inpmodify.py脚本则要根据不同的关键字以及需要替换的数据行进行修改，通用性没那么强。这里的函数以及之前两篇博客（[Matlab目录操作及fgetl函数](http://blog.csdn.net/libing403/article/details/71403025)，[Matlab-python-ABAQUS数据交互及联合使用](http://blog.csdn.net/libing403/article/details/71434546)）的函数，可以用来实现Abaqus与matlab之间的数据交换，可以在matlab方便使用一些优化算法，同时利用ABAQUS的有限元建模和计算的强大功能，实现参数反演估计，结构迭代，优化等研究。

​       当然实现matlab与ABAQUS的数据交互还有很多其他方法。例如一个国外学者George Papazafeiropoulos使用编写了matlab工具箱Abaqus2Matlab，可以读取ABAQUS的各种输出结果，还是很不错的。不过需要花一定时间去掌握如何使用，也有可能不符合自己的期待的功能，好像没有通过matlab进行修改inp文件或者操控ABAQUS的功能。

Abaqus2Matlab下载地址http://cn.mathworks.com/matlabcentral/fileexchange/54919-abaqus2matlab?focused=7197271&tab=example