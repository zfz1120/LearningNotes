#MySQL概述

##基础

MySQL由瑞典MySQL AB开发，目前由Oracle公司收购。开源的关系型数据库管理系统，分为社区版和企业版，没有太大的差异，社区版可以满足绝大多数需求。

##安装和配置MySQL

MSI安装（Windows）或ZIP，从官网下载。https://dev.mysql.com/downloads/file/?id=474803

安装类型：Typical（推荐），Custom，Complete

##MySQL配置：

安装目录下的bin文件夹中（Typical安装时，安装在C盘），运行MySQL 

标准配置Standard Configuration

勾选Install As Windows Service

勾选开机启动

勾选添加bin目录到PATH

设置超级用户密码



bin目录，可执行文件

data目录，存储数据文件

docs，文档

include目录，存储包含的头文件

lib目录，存储库文件

share，错误信息和字符集文件

配置选项

配置文件my.ini

[client]

port=  #端口号

[mysql]

default-character-set=utf8

[mysqld]

port=3306

配置后重新启动才生效。

启动和关闭

服务列表右键--重新启动

系统命令

启动：net start mysql

停止：net stop mysql



MySQL登录与退出

登录MySQL服务端

命令行：mysql  参数

参数：

-D，--database=name，打开指定数据库

--delimiter=name，

-h,--host name

例如：mysql -uroot -p -P3306  -h 127.0.0.1

退出

exit，quit ，\q

修改MySQL提示符

登录时通过参数--prompt  

例如：mysql -uroot --prompt    \h

登录后修改

l例如：prompt  mysql

\D 完整日期

\d 当前数据库

\u 用户名

\h 主机名



、

