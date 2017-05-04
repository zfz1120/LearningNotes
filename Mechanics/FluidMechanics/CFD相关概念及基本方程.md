# 计算流体力学概述[^1]

----

[TOC]

## 1.1计算流体力学

计算流体力学（ Computational Fluid Dynamics，简称 CFD）是以计算机作为模拟手段，
运用一定的计算技术寻求流体力学各种复杂问题的离散化数值解的计算方法。

计算流体力学可以看作是对基本守恒方程（质量守恒方程、动量守恒方程、能量守恒方程）控制下的流动过程进行数值模拟。通过这种数值模拟，可以得到极其复杂问题的流场内的各个位置上的基本物理量（如速度、压力、温度、浓度等）分布，以及这些物理量随时间
的变化情况。

计算流体力学、理论流体力学、实验流体力学是流体力学研究工作的三种主要手段。理论分析具有普遍性，各种影响因素清晰可见、为实验和计算研究提供依据。对于非线性情况，只有少数问题能给出解析解。实验研究仍是研究工作的基石，数值研究的许多方面都密切依赖于实验研究提供数据；计算结果需由实验验证；观察实验现象分析实验数据以建立计算模型等等。数值模拟是特殊意义下的实验，也称数值实验，它比起实验研究，经济效益极为显著。三种手段既互相独立又相辅相成。

对于相当多的流体计算问题，实际上我们需要知道的是一个耦合力学系统的响应特性－流固耦合体系特性，尽管这是一个更为复杂的计算体系。流固耦合（ Fluid-Structure Interaction，简称 FSI）计算方法的开发和应用是目前工程计算流体力学发展的重点领域，也是计算流体力学指导工程设计的直接途径。

## 1.2 基本概念

流体是气体和液体的总称。在人们的生活和生产活动中随时随地都可遇到流体，大气和水是最常见的两种流体。

### 1.2.1 理想流体和粘性流体

流体在静止时虽不能承受切向力，但在运动时，任意相邻两层流体之间却是有相互抵抗作用力的，这种相互抵抗的作用力称为剪切力，流体所具有的这种抵抗两层流体相对滑动速度的性质称为流体的粘性。粘性是流体的固有属性之一，不论流体处于静止还是流动，都具有粘性。它是流体状态（压力、温度、组成）的函数。气体的粘性随温度的升高而增大，液体的粘性随温度的升高而减小。

自然界中存在的流体都具有粘性，具有粘性的流体统称为粘性流体。完全没有粘性的流体称为理想流体。自然界中并不存在真正的理想流体，它只是为便于处理某些流动问题所做的假设而已。

### 1.2.2 牛顿流体和非牛顿流体

牛顿内摩擦定律：
$$
\tau=\mu \lim_{\Delta n \to 0} \frac {\Delta u}{\Delta n}=\mu \frac {\partial u}{\partial n}  \tag{1}
$$
其中$\tau$表示流体内摩擦应力，$\Delta n$为法线方向的距离增量；$\Delta u$为对应于$\Delta n$的流体速度增量。

牛顿内摩擦定律表示流体内摩擦应力和单位距离上的两层流体间的相对速度成正比。比例系数$\mu$ 称为流体的动力粘度，简称粘度。

牛顿流体：是指$\mu​$为常数的流体，即遵循牛顿内摩擦定律的流体称为牛顿流体。
非牛顿流体：不符合上述条件的均称为非牛顿流体。
所有气体和大多数低分子量液体均属牛顿型流体，如水、空气等；而某些高分子溶液、
油漆、血液等则属于非牛顿流体。

### 1.2.3可压缩流体和不可压缩流体

根据密度$\rho$ 是否为常数，流体分为可压缩流体（ compressible）与不可压缩流体(incompressible)两大类。在温度不变的情况下，当密度 $\rho$ 为常数时，流体为不可压缩流体，否则为可压缩流体。空气为可压缩流体，水为不可压缩流体。水的可压缩性是很小的，压强每增加一个大气压，其体积变化不到万分之一。工程中常用的其它工作液体，如液压油，机械油等，其体积模量数值也都很大，在一般工程计算中，可以忽略其可压缩性，将其看作是不可压缩流体。在研究气流场的时候，当流速较低(<0.3 马赫)时可以认为是不可压缩流体；当流速较高时需要考虑压强对气体密度的影响，甚至温度、压强对体积和密度的影响都必须考虑。

### 1.2.4  定常非定场流动

根据流体（某一位置）的物理量（如速度、压力、温度等）是否随时间变化，将流动分为定常（ steady）与非定常（ unsteady）两大类。当流动的物理量不随时间变化，即$\frac{\partial ()}{\partial t}=0$时，为定常流动，又称稳态流动；当流动的物理量随时间变化，即$\frac{\partial ()}{\partial t} \neq 0$时，为非定常流动，又称非稳态流动或瞬态流动。

### 1.2.5 层流和湍流

自然界中的流体流动状态主要分为两种形式－层流和湍流。在平行管的流动试验中，从流动质点的运动状态看，当仅发生层流时，流体质点互不干扰，流体流动呈线性或层状，且平行于管道轴线；当湍流（又称紊流）发生后，质点运动杂乱无章，除了平行于管道轴线的运动以外，还存在着剧烈的横向运动。

层流和湍流是两种不同性质的流态。层流时，流体流速较低，质点受粘性制约，不能随
意运动，粘性力起主导作用；湍流时，液体流速较高，粘性的制约作用减弱，惯性力起主导
作用。 液体流动时，究竟是层流还是湍流，通常要用雷诺数来判定。

雷诺数（Reynolds）是表征流体流动特性的一个重要参数。它是由管内的平均流速 $u$、液体的运动粘度$\nu$、管径 $d$三个参数决定的，即 $Re=\frac{ud}{\nu}$ 。又有运动粘度$\nu$与动力粘度$\mu$ 的关系，$\nu=\frac {\mu}{\rho}$ ，$\rho$为密度，所以雷诺数又可以表示为$Re=\frac {\rho ud}{\mu}$ 。从层流向湍流过渡发生在雷诺数约等于 2300，即临界雷诺数的时候。当流体的实际流动时的雷诺数小于临界雷诺
数时为层流，反之则为湍流。
对于非圆截面管道来说，做简单等效，可用 R 代替上式中的$d$ ， R 为通流截面的水力
半径。它等于液流的有效截面积 A 和它的湿周$x $（通流截面上与液体接触的固体壁面的周长）
之比，即$R=\frac{A}{x}$ 。

ADINA 计算结果中给出的雷诺数是单元雷诺数的概念，公式中长度$d$表示的是单元的长度。不同位置上的雷诺数与当地的流速，单元长度相关，所以雷诺数也不同。

## 1.3 流体力学方程组

流体流动满足三个基本方程：

（1）质量守恒方程。

它反映的是物质不生不灭这一最自然的物理定律。它用以描述流体密度$\rho$的变化规律。它不需要补充任何其他关系式，也就是说，质量守恒方程是物质不生不灭的最直观的体现，方程的形式十分简单。质量守恒方程也称连续性方程。

（2）动量守恒方程

它反映的是牛顿定律，即物体在力的作用下做加速运动。具体说，物质体所受的合力等于其质量与加速度的积，也可以理解为流体微团所受的力等于其动量变化率。因此，只要能求出合力，便可以得到动量守恒方程。合力包括体积力$\rho f$和面积力 $P_n$。体积力可以是多相物质的相互作用力、远程力（如重力与电磁力）和惯性力。面积力主要是压力和粘性应力。

（3）能量守恒方程。

能量守恒属于经典的热力学定律。流体微团单位质量的能量即总能 E 包括内能 e 与动能$\frac {1}{2}V^2$。合力所做的功、热传导、（由化学反应等引起的）生成热都引起总能的变化。

### 1.3.1 流场物理量的表示

流体速度$\mathbf{u}={(u_1,u_2,u_3)}$，$u_1,u_2,u_3$分别表示$x,y,z$方向上的速度分量。$\rho$是密度，$p$是压强，$T$是热力学温度。

若有过点$\mathbf {X}=(x_1,x_2,x_3)$的面积微元$dS$，单位法向量为$\mathbf{n}$。

在[$t,t+dt$]内沿$\mathbf{n}$流过$dS$的流体体积为$\mathbf{u}\cdot \mathbf {n}dSdt$

在[$t,t+dt$]内沿$\mathbf{n}$流过$dS$的流体质量为$\rho \mathbf{u} \cdot \mathbf{n}dSdt$

在[$t,t+dt$]内沿$\mathbf{n}$流过$dS$的流体动量为$\rho \mathbf{u(u\cdot u)}dSdt=\rho \mathbf{(u\times u)n}dSdt$

其中$\mathbf{u \times u}=\left (  \begin{matrix}u_1^2  & u_1u_2  &u_1u_3 \\ u_2u_1 &u_2^2 &u_2u_3 \\ u_3u_1 &u_3u_2 &u_3^2 \end{matrix}\right )$

面积微元$dS$受到$\mathbf{n}$正向一侧的流体压力为$-p\mathbf{n}dS$（压力方向与法向方向相反）

热力学中，有状态方程
$$
p=f(\rho,T)        \tag{1.1}
$$
若$p=\rho RT$，则为理想气体。

用$e$来表示单位质量流体的内能，单位体积中流体的能量为$\rho e+\frac{1}{2}\rho \mathbf{u^2}$，（$\mathbf{u^2}=u_1^2+u_2^2+u_3^2$）

在[$t,t+dt$]内沿$\mathbf{n}$流过$dS$的流体能量为$(\rho e+\frac{1}{2}\rho u^2)\mathbf{u \cdot n}dSdt$

### 1.3.2 理想流体力学方程组

（1）质量守恒方程

质量守恒定律表述为L单位时间内流体微元中质量的增量，等于同一时间间隔内流入该微元的净质量，即
$$
\begin{equation}
\int _{\Omega } \rho(t_2,\mathbf{X})dx-\int _{\Omega} \rho(t_1,\mathbf{X})dx=
-\int _{t_1}^{t_2}\int _{\Gamma}\rho \mathbf{u}\cdot \mathbf{n}dSdt       \tag{1.2}
\end{equation}
$$
$\Gamma$为区域$\Omega$的边界。

质量守恒方程的微分形式为
$$
\frac{\partial p}{\partial t}+div(\rho \mathbf{u})=0 \tag{1.3}
$$
$div$表示散度，$div \mathbf{u}=\frac{\partial u_1}{\partial x_1}+\frac{\partial u_2}{\partial x_2}+ \frac {\partial u_3}{\partial x_3}$。质量守恒方程又称为连续性方程。

（2）动量守恒方程

动量守恒定律表述为：单位时间内流体微元中动量的增量，等于同一时间间隔内流入该微元的动量与外力冲量的和，外力包括作用在边界$\Gamma$上的表面力和作用在区域$\Omega$上的体积力$\mathbf{ F}=(F_1,F_2,F_3)$。
$$
\int _{\Omega}\rho \mathbf{u}(t_2,\mathbf{X})dx-\int _{\Omega} \rho \mathbf{u}(t_2,\mathbf{X})dx=
-\int _{t_1}^{t_2}\int _{\Gamma}\rho(\mathbf{u}\times \mathbf{u})\cdot \mathbf{n}dSdt
-\int _{t_1}^{t_2}\int _{\Gamma}p\mathbf{n}dSdt
+\int _{t_1}^{t_2}\int _{\Omega}\rho\mathbf{F}dxdt    \tag{1.4}
$$
动量守恒方程的微分形式为：
$$
\frac{\partial}{\partial t}(\rho \mathbf{u})+div(\rho \mathbf{u\times\mathbf{u}}+p\mathbf{I})=\rho \mathbf{F}    \tag{1.5}
$$
写成分量形式，并利用连续性方程化简得：
$$
\frac{\partial u_i}{\partial t}+\sum _{k=1}^{3}u_k \frac {\partial u_i}{\partial x_k}+\frac{1}{\rho}\frac{\partial p}{\partial x_i}=F_i,i=1,2,3                 \tag{1.6}
$$
或者写成
$$
\frac{d\mathbf{u}}{dt}+\frac{1}{\rho}gradp=\mathbf{F}     \tag{1.7}
$$
其中，$\frac{d}{dt}=\frac{\partial}{\partial t}+\sum_{k=1}^{3}u_k\frac{\partial}{\partial x_k}$，表示固定流体质点对$t$的导数。

（3）能量守恒方程

能量手很定律描述为：单位时间内流体委员中能量的增量，等于同一时间间隔内流入该微元的能量与外力做功的和。
$$
\int _{\Omega}(\rho e+\frac{1}{2}\rho \mathbf{u}^2)(t_2,\mathbf{X})dx-\int _{\Omega}(\rho e+\frac{1}{2} {\rho \mathbf{u}^2})(t_1,\mathbf{X})dx   \\
=- \int _{t_1}^{t_2}\int _{\Gamma} (\rho e+\frac{1}{2}\rho \mathbf{u}^2)\mathbf{u}\cdot \mathbf{n}dSdt-\int _{t_1}^{t_2}\int _{\Gamma} p\mathbf{u}\cdot\mathbf{n}dSdt+\int _{t_1}^{t_2}\int _{\Omega}\rho\mathbf{F}\cdot \mathbf{u}dxdt             \tag{1.8}
$$


将能量守恒方程化为微分形式
$$
\frac{\partial}{\partial t}(\rho e+\frac {1}{2}\rho\mathbf{u}^2)+div(\rho e+\frac{1}{2}\rho \mathbf{u}^2+\rho)\mathbf{u}=\rho \mathbf{F\cdot u}    \tag{1.9}
$$
利用连续性方程化简得：
$$
\frac{de}{dt}+\frac{p}{\rho^2}\frac{dp}{dt}=0   \tag{1.10}
$$
方程（1.1）(1.3)(1.7)(2.0)构成了理想流体力学的基本方程组。

### 1.3.3 粘性流体力学方程组

自然界中并不存在真正的理想流体，对于粘性系数为$\mu$（动力学粘性系数，又称第一粘性系数）的流体，他的基本方程组为：

质量守恒方程（1.3）不变
$$
\frac {\partial \rho}{\partial t}+div(\rho \mathbf{u})=0    \tag{1.11}
$$
动量守恒方程为
$$
\frac {\partial }{\partial t}(\rho \mathbf{u})+div(\rho \mathbf{u}\times\mathbf{u}-\mathbf{P})=\rho\mathbf{F}    \tag{1.12}
$$
其中$\mathbf{P}=\{ p_{ij} \}$，

$p_{ij}=-p\delta_{ij}+\mu(\frac{\partial u_i}{\partial x_j}+\frac{\partial u_j}{\partial x_i}-\frac{2}{3}div\mathbf{u}\delta_{ij})+\mu ^{'}div\mathbf{u}\delta_{ij}$，

$\mu^{'}=\lambda+\frac{2}{3}\mu$，称为膨胀粘性系数，又称第二粘性系数。

能量守恒方程为
$$
\frac{\partial }{\partial t}((\rho e+\frac{1}{2}\rho \mathbf{u}^2)\mathbf{u}-p\mathbf{u})
=div(\kappa gradT)+\rho \mathbf{F}\cdot\mathbf{u}                            \tag{1.13}
$$
其中$\kappa$为热传导系数。

方程（1.1）（2.1）（2.2）（2.3）构成了粘性流体力学方程组。

对于不可压缩的粘性流体，密度$\rho$为常数，取$\rho=1$，则有
$$
div\mathbf{u}=0            \tag{1.14}
$$
方程（1.12）变为
$$
\frac{\partial u_i}{\partial t}+\sum _{k=1}^{3}u_k\frac{\partial u_i}{\partial x_k}-\mu\Delta u_i+\frac{\partial p}{\partial x_i}=F_i,i=1,2,3                     \tag{1.15}
$$
方程（1.14）（1.15）即为三维不可压缩的粘性流体的Navier-Stokes方程，简称N-S方程。

### 参考文献

[^1]: 岳戈. ADINA流体与流固耦合功能的高级应用[M]. 人民交通出版社, 2010.
