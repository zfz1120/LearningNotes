# VS工程升级后错误error RC2104:undefined keyword or key name解决方法

问题：

VS建立的工程用新版本打开升级后，不能打开资源视图，出现错误提示error RC2104:undefined keyword or key name  WS_EX_NOINHERILAYOUT

原因：

如果升级VS工程，发现编辑了`*.rc`后，出现编译错误，error RC2104:undefined keyword or key name，基本上是由于升级时，把`*.rc`中的`#include <windows.h>`去掉了，加了一个resouce.h。

解决方法：

在`*.rc`中将`#include <windows.h>`加上就可以了。