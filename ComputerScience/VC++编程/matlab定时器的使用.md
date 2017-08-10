# matlab定时器的使用

转载自博客[matlab定时器的使用（来自网络）](http://blog.sina.com.cn/s/blog_7dc6e9750100wci5.html)

---------------------------------------------------------------

matlab中使用定时器（timer）基本格式为
t = timer('PropertyName1', PropertyValue1, 'PropertyName2', PropertyValue2,...);
start(t);

最简单的定时器一般指定以下属性：
TimerFcn ——指定定时器被触发时要执行的函数或语句
Period ——指定定时器的触发时间，单位为秒
ExecutionMode ——指定定时器的触发方式（触发一次，还是循环触发……），该属性有四个可选值，具体见matlab帮助
TasksToExecute ——指定定时器最多被触发的次数，该属性默认为inf，如果希望不停的循环执行，可以不指定该属性
tag ——一个字符串，可以任意指定，一般用于标志某个特定的定时器，以方便在程序中别的地方查找该定时器

在matlab命令窗口中输入下面语句，则将输出1到10，每隔1秒输出一次
x=1;
t = timer('TimerFcn','disp(x);x=x+1;', 'Period', 1, 'ExecutionMode', 'fixedSpacing', 'TasksToExecute', 10);
start(t);

 

与定时器相关的其他操作
delete(timer)    %删除
disp(timer)      %显示
get(timer)       %获取属性
isvalid(timer)   %检查有效性
set(timer)       %设置属性
start            %开始
startat          %开始（可以指定开始时的某些参数）
stop             %停止
timerfind        %查找某个定时器
timerfindall     %也是查找
wait             %等待直到定时器被停止



 eg.删除所有的timer 

 ts=timerfind; 

  if length(ts)>0 

​    stop(ts); 

​    delete(ts); 

  end 