# Matlab目录操作及fgetl函数

## 获取当前目录

pwd命令

```
a=pwd();
```

## 进入指定目录

```matlab
a='F:\code';
cd(a);
```

或者

```matlab
cd 'F:\code'
```

## matlab如何读取文本文件并逐行显示

以下是自己写的一个函数，在窗口输出显示指定文件中的内容

```matlab
%显示日志文件（所有文本文件）的内容
function showlogfile(logfile)
fid=fopen(logfile,'r');
if fid==-1
    fprintf('erro:\n%s can not open\n',logfile);
end
fprintf('\n---------------%s---------------- \n',logfile);
tline=fgetl(fid);
while ischar(tline)
    disp(tline);
    tline=fgetl(fid);
end
fclose(fid);
end
```

现在我有一个文件pylog.txt，内容如下：

```tex
------------------------------------------------------------------
2017-05-07 19:39:46
read Node PLATEN-1.5322 RF3 from 
F:\security folder\ABAQUS WORKING\inversion_per/unixial-inversion-per.odb
open odb successfully
get nodes sets successfully
get data  successfully
inp file modify successfully
```

运行函数

```matlab
showlogfile('pylog.txt')
```

则在窗口输出文件里的内容。

为什么要这么做呢？如果用普通的textscan，textread或者importdata读入文件内容，会把文件里的字符当做一个或多个字符串，输出的会是很长的一行字符，很难像原来文件那样换行输出。