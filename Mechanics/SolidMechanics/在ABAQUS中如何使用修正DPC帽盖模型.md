# 在ABAQUS中如何使用修正DPC帽盖模型

## 引言

修正Drucker-Prager盖帽模型（简称修正DPC模型）和修正剑桥（简称MCC模型）在岩土领域广泛使用，而修正DPC模型应用更加广，应用于描述存在大体积应变的材料力学行为。它在线性Drucker-Prager模型上增加了一个帽盖状的屈服面，从而引入了压缩导致的屈服，同时也能控制材料在剪切作用下的无限制剪胀现象。如下图是修正DPC模型的屈服面。

![修正DPC模型的屈服面](image\修正DPC模型的屈服面.png)

## ABAQUS中设置修正DPC帽盖模型的参数

在很多有限元软件提供了修正DPC帽盖模型的本构模型，下面简要介绍在ABAQUS中设置相关参数。修正DPC模型可以与线弹性体、多孔介质弹性体一起使用，还可以与基于Darcy定律的多孔介质属性一起组合来描述类似土壤固结的力学行为，或类似的渗流/应力耦合力学行为。

以线弹性体+修正DPC帽盖模型为例，设置材料属性。

**设置弹性参数**

新建一个材料名称，然后增加一个弹性力学行为：Mechanical-->Elasticity-->Elastic，如下图所示

<center>

<img src="image\ABAQUS-elastic.png" width="400">

设置弹性参数

</center>

## 设置修正DPC模型参数

在ABQAUS软件中需要设置的参数有：

p-t平面上的粘聚力(Material Cohesion) $d$

p-t平面上的摩擦角(Angle of Friction) $\beta$

R (Cap Eccentricity)，需大于0

定义初始屈服位置(Init Yld Surf Pos)$\varepsilon_{vol}^{in }|_0$

过渡区参数(Transition Surf Rad) $\alpha$，包含蠕变效应时，$\alpha$=0

三轴拉伸强度与三轴压缩强度之比(FlowStress Ratio) k，

通过表格给定$p_b$随$\varepsilon_{vol}^{pl}$的变化

前面6个参数设置步骤：Mechanical-->Platicity-->Cap Platicity，弹出如下对话框，在对应位置输入上述的6个参数。

<center>

<img src="image\ABAQUS-Cap platicity.png" width="450">

设置修正dpc塑性参数（cap platicity）

</center>

**设置硬化律参数**

修正的Drucker-Prager帽盖模型中的硬化参数为$p_b$，用户可以分段指定$p_b$与塑性体积应$\varepsilon_{vol}^{pl}$的关系。在上面对话框的基础上（或者选择刚刚创建的Cap Platicity），步骤：Suboption-->Cap Hardening，然后弹出一个小对话框，输入硬化律两列数据即可，如下图所示。

<center>

<img src="image\ABAQUS-Cap Hardenning.png" width="400">

设置帽盖硬化律（cap hardening）

</center>

## 小结

在ABAQUS中也可以通过关键字在inp文件中设置上述的这些材料参数，但是我觉得在cae界面里设置更方便，不容易出错。关于上述修正DPC本构模型的相关理论这里就不详细讨论，可以参考下面列出的一些教材，参考文献。

-----

参考资料：

[1]费康, 张建伟. ABAQUS在岩土工程中的应用[M]. 北京: 中国水利水电出版社, 2009.

[2]Han L H, Elliott J A, Bentham A C, et al. A modified Drucker-Prager Cap model for die compaction simulation of pharmaceutical powders[J]. International Journal of Solids and Structures, 2008,45(10):3088-3106.

[3]Rui Z, Zhang L, He B, et al. Numerical simulation of residual stress field in green power metallurgy compacts by modified Drucker–Prager Cap model[J]. Transactions of Nonferrous Metals Society of China, 2013,23(8):2374-2382.