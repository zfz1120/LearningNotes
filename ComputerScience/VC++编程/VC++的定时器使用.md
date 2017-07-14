## VC++的定时器使用

转载自https://my.oschina.net/ypimgt/blog/61061

VC++    WM_TIMER   定时器使用方法

​      在编程时，会经常使用到定时器。使用定时器的方法比较简单，通常告诉Windows一个时间间隔，然后WINDOWS以此时间间隔周期性触发程序。通常有两种方法来实现：发送WM_TIMER消息和调用应用程序定义的回调函数。

**1.1 用WM_TIMER来设置定时器**

先请看SetTimer这个API函数的原型

```c++
UINT_PTR SetTimer(
HWND hWnd, // 窗口句柄
UINT_PTR nIDEvent, // 定时器ID，多个定时器时，可以通过该ID判断是哪个定时器
UINT uElapse, // 时间间隔,单位为毫秒
TIMERPROC lpTimerFunc // 回调函数
);
```

**例如 :**

```c++
SetTimer(m_hWnd,1,1000,NULL); //一个1秒触发一次的定时器
```

**在MFC程序中SetTimer被封装在CWnd类中，调用就不用指定窗口句柄了，例如:**

**UINT SetTimer(1,100,NULL);**

**函数反回值就是第一个参数值1，表示此定时器的ID号。**

第二个参数表示要等待100毫秒时间再重新处理一次。第三个参数在这种方法中一般用NULL。

注意：设置第二个参数时要注意，如果设置的等待时间比处理时间短，程序就会出问题了。

**1.2 调用回调函数**

此方法首先写一个如下格式的回调函数

void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime);

然后再用SetTimer(1,100,TimerProc)函数来建一个定时器，第三个参数就是回调函数地址。

二、多个定时器的实现与应用

我们在安装定时器时都为其指定了ID，使用多个定时器时，该ID就发挥作用了。

不使用MFC时，当接收到WM_TIMER消息，WPARAM wParam中的值便是该定时器的ID

使用MFC时就更简单了，我们为其增加WM_TIME的消息处理函数OnTimer即可，请看如下例子 

```c++
void CTimerTestDlg::OnTimer(UINT nIDEvent)
{
switch (nIDEvent)
{
case 24: ///处理ID为24的定时器
 Draw1();
 break;
case 25: ///处理ID为25的定时器
 Draw2();
 break;
}
CDialog::OnTimer(nIDEvent);
}
```

当你用回调函数时，我们可以根据nTimerid的值来判断是哪个定时器，例如:

```c++
void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
{
 switch(nTimerid)
 {
 case 1: ///处理ID为1的定时器
 Do1();
 break;
 case 2: ///处理ID为2的定时器
 Do2();
 break;
 }
}
```

**三、取消定时器**

不再使用定时器后，我们应该调用KillTimer来取消定时，KillTimer的原型如下

BOOL KillTimer(

HWND hWnd, // 窗口句柄

UINT_PTR uIDEvent // ID

);

在MFC程序中我们可以直接调用KillTimer(int nIDEvent)来取消定时器。

如：KillTimer(1);

——————————————————————————————————————————————————

## MFC中定时器的使用

巧妙地使用定时器能达到意想不到的效果，写界面的时候能实现渐变，也能帮助多线程控制等
我们知道，在VC的MFC中，已经为我们封装好了很多全面和强大的函数集，所以在MFC编程时，巧妙地调用MFC函数库可以为我们省去很多麻烦。其中定时器也可以在MFC程序中很好地利用。

在MFC中和定时器相关的有三个函数：
1.设置定时器(定义一个定时器的属性)：
SetTimer( UINT nIDEvent, UINT nElapse, void (CALLBACK EXPORT*lpfnTimer)(HWND,UINT,UINT,DWORD));
2.定时器响应(响应系统定义WM_TIMER消息)：
OnTimer( UINT nIDEvent );
3.释放定时器：
KillTimer( int nIDEvent );
其中：
UINT nIDEvent：定时器的ID，在一个程序中用这个ID来确定是那个定时器发送的消息。
UINT nElapse： 定义刷新时间，即间隔多长时间刷新一次，单位是毫秒。
void (CALLBACK EXPORT* lpfnTimer)( HWND, UINT, UINT, DWORD)：回调函数的参数，实现刷新时所做的操作，一般情况下都设为0。

在这里就用一个简单的例子来说明定时器在MFC中是如何使用的。
**1.建立单文档程序Timer。**
2.在resource.h中定义两个定时器的ID
\#define TIMER1 1
\#define TIMER2 2
3.在CMainFrame的OnCreate函数中定义两个定时器的属性。
SetTimer(TIMER1,3000,0);
SetTimer(TIMER2,5000,0);
4.在类视图中右击CMainFrame属性，在消息响应函数中找到WM_TIMER,然后添加响应函数OnTimer()。
void CMainFrame::OnTimer(UINT nIDEvent)
{
// TODO: Add your message handler code here and/or call default
switch(nIDEvent)
{
case TIMER1:
{
AfxMessageBox("定时器1!");
break;
}
case TIMER2:
{
AfxMessageBox("定时器2!");
break;
}
default:
break;
}
CFrameWnd::OnTimer(nIDEvent);
}

5.在CMainFrame的析构函数中添加释放定时器函数。
KillTimer(TIMER1);
KillTimer(TIMER2);

这样，一个简单的定时器程序就生成了，运行后可以看到，每隔3秒就会弹出一个消息对话框“定时器1”，每隔5秒就会弹出一个消息对话框“定时器2”。

这种情况是在程序运行后定时器就直接启动了，很多时候我们需要的是在响应一次事件或者说点击一个按钮后再去执行定时器，那么这时应该怎么修改呢？也用一个实例来说明吧，因为我觉得可能说一大堆废话也抵不上一个简单而正确的实例更具说服力。

另一个人做的

现在，我生成了一个**MFC多文档应用程序**，我希望在点击菜单条上的某个按钮后再去执行定时器。这时就不是在CMainFrame里面操作了，因为我们是要在对话框上进行定时器的操作，而CView这个类是负责对话框的对应操作，所以要把定时器定义在CView里面。
1.建立多文档程序Timer。
2.在resource.h中定义两个定时器的ID
\#define TIMER1 1
\#define TIMER2 2
3.在CTimerView的OnInitialUpdate函数中定义两个定时器的属性。
SetTimer(TIMER1,3000,0);
SetTimer(TIMER2,5000,0);
4.在类视图中右击CTimerView属性，在消息响应函数中找到WM_TIMER,然后添加响应函数OnTimer()。
void CTimerView::OnTimer(UINT nIDEvent)
{
// TODO: Add your message handler code here and/or call default
//Hwnd为一个变量，初始值为false，点击某个按钮后在其响应函数中将其置为true
switch(nIDEvent && Hwnd){
case TIMER1:
{
AfxMessageBox("定时器1!");
break;
}
case TIMER2:
{
AfxMessageBox("定时器2!");
break;
}
default:
break;
}
CFrameWnd::OnTimer(nIDEvent);
}
5.在CTimerView中添加OnDestroy()函数，在函数中释放定时器。
KillTimer(TIMER1);
KillTimer(TIMER2);
现在，运行程序后，没有马上弹出预定的对话框，而是在我们点击某个按钮或者响应某个事件后对话框才弹出，同样是点击按钮后，每隔3秒弹出对话框“定时器1”，每隔5秒弹出“定时器2”。
其实在不同的类，定时器的用法都是基本一致的，只要找到类的初始函数和释放函数，就能轻松实现定时功能了，就这么简单。

**基于对话框的定时器程序**

1.打开VC，新建一基于对话框的工程，工程名为Test在对话框上添加一按钮，将其ID改为IDC_BUTTON_START，Caption改为Start.　映像该按钮的BN_CLICKED消息，void CTestDlg::OnButtonStart();

2.再在对话框上添加一按钮，ID为ID_BUTTON_STOP,Caption改为Stop,映像消息为void CTestDlg::OnButtonStop();

3.添加一个Lable,ID改为IDC_STATIC_TIME,用于记数，表明定时器函数的执行。

4.映像对话框的WM_TIMER消息，void CTestDlg::OnTimer(UINT nIDEvent);

以上的实现函数如下所示：

void CTestDlg::OnButtonStart()

{

SetTimer(1,1000,NULL);//启动定时器1,定时时间是1秒

}

void CTestDlg::OnButtonStop()

{

KillTimer(1);//关闭定时器1。

}

void CTestDlg::OnTimer(UINT nIDEvent)

{

static int nTimer=0;

CString strTmp="";

strTmp.Format("Timer:%d",nTimer++);

CWnd *pWnd=GetDlgItem(IDC_STATIC_TIME);

pWnd->SetWindowText(strTmp); //在Lable中设置新值，表明定时器已经工作。

CDialog::OnTimer(nIDEvent);

}

回调函数的使用。

如果不想使用窗体的WM_TIMER消息函数处理，可以使用回调函数来取代，读者可以在上面例子的基础上，增加一个回调函数，以证实前面的讨论。

首先，定义一个回调函数，回调函数的定义必须按照如下格式。

void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime );

我的实现函数如下：

void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime )

{

AfxMessageBox("Timer is running!");//定时器时间到，强出一对话框，表明定时器已经运行。

}

将上面的启动函数稍做修改

void CTestDlg::OnButtonStart()

{

//SetTimer(1,1000,NULL);//启动定时器1,定时时间是1秒

SetTimer(1,1000,(TIMERPROC)TimerProc);//用回调函数处理，此时对话框的消息处理函数不再处理。

}