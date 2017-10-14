# matlab记录窗口输出信息

1.把输入写入指定目录，之后会一直记录窗口输出信息，直到你关闭diary；

```matlab
diary('testlog.txt');
diary on;
```

2.关闭日志记录

```matlab
diary off;
```

3.删除日志

```matlab
diary off;%先关闭
delete('testlog.txt');
```

