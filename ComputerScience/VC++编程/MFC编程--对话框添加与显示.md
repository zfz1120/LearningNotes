# MFC编程--对话框添加与显示

上一篇博客已经介绍了如何在对话框上添加和显示菜单栏，这里介绍在单击菜单栏是弹出一个对话框的实现。例如本例要实现单击菜单的BasicMove时，弹出一个对话框。

![菜单栏BasicMove.png](image\菜单栏BasicMove.png)

**(1)新建一个对话框资源**

在切换到"资源视图"，右击Dialog-->插入Dialog，这样就新建了一个对话框。然后右击新建的对话框-->添加类，为类添加一个名字。我这里添加类的名字为BasicMove（名称可自己定义）。然后在类视图就可以看到新增的类。

![新增的类名](image\新增的类名.png)

**(2)显示对话框**

首先为菜单项添加一个事件处理程序，切换当菜单栏的资源视图，右击菜单项BasicMove-->添加事件处理程序-->消息类型COMMAD-->类型列表选择CtestDLGlg。注意类型列表中，testDLG工程项目的名称，其中“C”和“lg”是你所建立工程名的前缀和后缀。如下图所示。

![添加菜单项的事件处理程序.png](image\添加菜单项的事件处理程序.png)

单击对话框的“添加编辑”之后会自动跳转到实现代码的文件，并自动生成下面的函数框架。

```c++
void CtestDLGDlg::OnPositionBasicmove()
{
	// TODO: 在此添加命令处理程序代码
}
```

如下所示，在事件处理函数中添加两行代码。

```c++
void CtestDLGDlg::OnPositionBasicmove()
{
	// TODO: 在此添加命令处理程序代码
	BasicMove aDlg; //BasicMove类在BasicMove.h头文件中声明
	aDlg.DoModal(); //实现对话框的显示
}
```

最后还要在该文件的头部添加自己新建的那个窗口类的头文件名。在刚才第（1）步中已经为对话框添加了一个名字为BasicMove的类，创建那个类的时候，就会自动生成一个名为BasicMove.h的头文件，该头文件中包含了对BasicMove的类的声明。这些都是visual C++自动完成的。在上面的实现代码中，使用到了BasicMove类，因此要在该文件中（上述实现对话框显示的文件）的开头包含BasicMove.h的头文件。

```c++
// testDLGDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "testDLG.h"
#include "testDLGDlg.h"
#include "BasicMove.h"   //添加的头文件
```

