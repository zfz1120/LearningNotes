# S型速度轨迹在线计算

计算S型速度轨迹的一个简单方法是基于轨迹的离散时间公式。这种方法适合计算需要定义复杂轨迹，由多个S型轨迹段组成的情况，也适合于那些使用离散时间计算轨迹的CNC机器。

首先定义
$$
\begin{cases}
q(t=kT_s)=q_k\\
\dot q(t=kT_s)=\dot q_k\\
\ddot q(t=kT_s)=\ddot q_k\\
q^{(3)}=q_k^{(3)}
\end{cases}
$$
在k个时刻时的位置，速度，加速度和加加速度的值，$T_s$是采样周期。轨迹规划器的结构如下图所示。

![S型轨迹规划器](image\Fig3.20.png)

给定始末位置，速度和加速度以及约束$(v_{max},v_{min},\text a_{max},a_{min},j_{max},j_{min})$,注意，这是约束条件可以不对称，例如$j_{max},j_{min}$的绝对值可以不相等。加加速度曲线按照下面介绍方式计算，然后经过三次积分，分别得到加速度，速度和位置。值得注意的是，这里将使用梯形积分器（积分器的离散时间传递函数是$G_I(z^{-1})=\frac{T_s}{2}\frac{1+z^{-1}}{1-z^{-1}}$.），根据加加速度，加速度，速度和位置的关系，有
$$
\begin{matrix}
\ddot q_k=\ddot q_{k-1}+\frac{T_s}{2}(q^{(3)}_{k-1}+q^{(3)}_k)\\
\dot q_k=\dot q_{k-1}+\frac{T_s}{2}(\ddot q_{k-1}+\ddot q_k)\\
q_k=q_{k-1}+\frac{T_s}{2}(\dot q_{k-1}+\dot q_k)
\end{matrix}
\tag{3.34}
$$
该轨迹规划器的基本思想是依照期望的加速度和加加速度约束执行加速段，然后是匀速段，直到需要减速，以期望的速度，加速度值到达终点位置。因此轨迹的计算分为两段，如下图所示。

1. 加速度曲线使用典型的梯形加速度，紧接着可能是一个匀速段。
2. 在运动中，在每个时刻$kT_s$都检查是否可以从当前速度$\dot q_k$,在$\ddot q_k$和$q^{(3)}_k$的限制下，减速到末速度$v_1$，且到达目标位置$q_1$.

## 第一阶段：加速度段和匀速段

为了从$q_0​$到达$q_1(>q_0)​$，加加速度保持最大值直到$\ddot q_k<\text a_{max}​$。然后加加速度变为零（$q^{(3)}_k=0​$）,所以加速度恒定（$\text a_{max}​$）。最后，为了达到最大速度时加速度减为0，加加速度设置为最小值($q_{k}^{(3)}=j_{min}​$)，这样，最大速度保持到减速阶段开始。从数学角度，该过程可描述为
$$
q^{(3)}_k=
\begin{cases}
j_{max} ,&& \dot q_k-\frac{\ddot q^2_k}{2j_{min}}<v_{max} \ \text{and}\  \ddot q_k<\text a_{max}  \\
0,   && \dot q_k-\frac{\ddot q^2_k}{2j_{min}}<v_{max} \ \text{and}\  \ddot q_k\ge \text a_{max}  \\
j_{min},   && \dot q_k-\frac{\ddot q^2_k}{2j_{min}}\ge v_{max} \ \text{and}\  \ddot q_k>0  \\
0,     && \dot q_k-\frac{\ddot q^2_k}{2j_{min}}\ge v_{max} \ \text{and}\  \ddot q_k\le 0  \\
\end{cases}
$$
上面式子中使用$\dot q_k-\frac{\ddot q^2_k}{2j_{min}}\ge v_{max} ,  \ddot q_k\ge \text a_{max}  , \ddot q_k\le 0$,而不使用$\dot q_k-\frac{\ddot q^2_k}{2j_{min}}= v_{max} ,  \ddot q_k= \text a_{max}  , \ddot q_k= 0$,是因为取等号时，浮点数运算很小的数值计算误差也会影响结果。

## 第二阶段:减速段

在每个采样时间，