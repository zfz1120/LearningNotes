# 机器人学之指数坐标推导雅可比（Jacobian）

![猎豹机器人越障--百度图片](image\猎豹机器人越障.gif)

## 空间雅可比(Space Jacobian)

假设一个开链机构的正运动学以指数积形式写成
$$
T(\theta)=e^{[\mathcal S_1]\theta_1}\dots e^{[\mathcal S_n]\theta_n}M.
$$
空间雅可比$J_s(\theta)\in \mathbb R^{6\times n}$关联了关节速度向量$\dot \theta \in\mathbb R^n$和空间旋量$\mathcal V_s$，即$\mathcal V_s=J_s(\theta)\dot \theta$。$J_s(\theta)$第$i$列由下式确定
$$
J_{si}(\theta)=Ad_{e^{[\mathcal S_1]\theta_1}...e^{[\mathcal S_{i-1}]\theta_{i-1}}}(\mathcal S_i),
$$
对于$i=2, \dots, n,$第1列$J_{s1}=\mathcal S_1$。螺旋矢量$J_{si}$的物理意义是在任意非零关节角度$\theta$下，第$i$个关节在空间固定坐标系下的表达。

**推导**：

已知正运动学指数形式表达为
$$
T(\theta)=e^{[\mathcal S_1]\theta_1}\dots e^{[\mathcal S_n]\theta_n}M.\tag{5.5}
$$
空间旋量$\mathcal V_s$由齐次变换矩阵给出$[\mathcal V_s]=\dot TT^{-1}$, 其中
$$
\dot T=(\frac {d}{dt}e^{[\mathcal S_1]\theta_1})\dots e^{[\mathcal S_n]\theta_n}M+e^{[\mathcal S_1]\theta_1}(\frac{d}{dt}e^{[\mathcal S_2]\theta_2})\dots e^{[\mathcal S_n]\theta_n}M+\dots\\
=[\mathcal S_1]\dot \theta_1e^{[\mathcal S_1]\theta_1}\dots e^{[\mathcal S_n]\theta_n}M+e^{[\mathcal S_1]\theta_1}[\mathcal S_2]\dot \theta_2e^{[\mathcal S_2]\theta_2}\dots e^{[\mathcal S_n]\theta_n}M+\dots\\
$$
也有
$$
T^{-1}=M^{-1}e^{-[\mathcal S_n]\theta_n}\dots e^{-[\mathcal S_1]\theta_1}.
$$
计算$\dot TT^{-1}$得到
$$
[\mathcal V_s]=[\mathcal S_1]\dot \theta_1+e^{[\mathcal S_1]\dot \theta_1}[\mathcal S_2]e^{-[\mathcal S_1]\dot \theta_1}+e^{[\mathcal S_1]\dot \theta_1}e^{[\mathcal S_2]\dot \theta_2}[\mathcal S_3]e^{-[\mathcal S_1]\dot \theta_1}e^{-[\mathcal S_2]\dot \theta_2}+\dots
$$
上式可以进一步写成向量形式的伴随映射
$$
\mathcal V_s=\underbrace {\mathcal S_1}_{J_{s1}}\dot\theta_1+\underbrace{\text{Ad}_{e^{[\mathcal S_1]\theta_1}}(\mathcal S_2)}_{J_{s2}}\dot \theta_2+\underbrace{\text{Ad}_{e^{[\mathcal S_1]\theta_1}{e^{[\mathcal S_2]\theta_2}}}(\mathcal S_3)}_{J_{s3}}\dot \theta_3+\dots \tag{5.6}
$$
观察发现，$\mathcal V_s$是$n$个空间旋量的和的形式
$$
\mathcal V_s=J_{s1}\dot\theta_1+J_{s2}(\theta)\dot\theta_2+\dots +J_{sn}(\theta)\dot \theta_n,\tag{5.7}
$$
这里对任意$i=2, \dots,n$, 每个$J_{si}(\theta)=(\omega_{si}(\theta,v_{si}(\theta)))$显式地决定于关节变量$\theta\in\mathbb R^n$. 写成矩阵形式
$$
\mathcal V_s=\left[  \begin{matrix}
J_{s1} & J_{s2} (\theta)&\dots &J_{sn}(\theta)
\end{matrix}\right]
\left[  \begin{matrix}
\dot\theta_1 \\ \dot \theta\\ \vdots\\\dot\theta
\end{matrix}\right]
=J_s(\theta)\dot\theta .\tag
{5.8}
$$
矩阵$J_s(\theta)$称为在（空间）固定坐标系的雅可比，或称为空间雅可比。

**补充：**这里伴随映射的定义：给定一个齐次变换矩阵$T=\left[  \begin{matrix} R&p\\0&1    \end {matrix}\right]\in SE(3)$，其伴随表示$[\text{Ad}_T]$是
$$
\text{Ad}_T=\left[  \begin{matrix} R&R\\ [p]R&0    \end {matrix}\right] \in \mathbb R^{6\times6}
$$
这里$[p]$ 表示向量$p$对应的反对称矩阵。 $[\text{Ad}_T]$的物理意义实际是对6维旋量进行坐标变换，类似于齐次矩阵对3维向量进行坐标变换。例如，坐标系{s}到坐标系{b}的其次变换为$T_{sb}$，对一个旋量$\mathcal V_b$进行伴随表示可以写成
$$
\mathcal V_s=[\text{Ad}_{T_{sb}}]\mathcal V_b=\text{Ad}_{T_{sb}}(\mathcal V_b)
$$

## 物体雅可比（Body Jacobian）

类似的，若旋量在物体坐标系里描述，那么可以推导出在物体坐标系描述的运动学表达式，进而推导出物体雅可比,即

假设一个开链机构的正运动学以指数积形式写成
$$
T(\theta)=Me^{[\mathcal B_1]\theta_1}\dots e^{[\mathcal B_n]\theta_n}.
$$
空间雅可比$J_b(\theta)\in \mathbb R^{6\times n}$关联了关节速度向量$\dot \theta \in\mathbb R^n$和空间旋量$\mathcal V_b$，即$\mathcal V_b=J_b(\theta)\dot \theta$。$J_b(\theta)$第$i$列由下式确定
$$
J_{bi}(\theta)=Ad_{e^{[\mathcal B_1]\theta_1}...e^{[\mathcal B_{i-1}]\theta_{i-1}}}(\mathcal B_i),
$$
对于$i=n-1, \dots, 1,$第n列$J_{B_n}=\mathcal B_n$。螺旋矢量$J_{bi}$的物理意义是在任意非零关节角度$\theta$下，第$i$个关节在物体坐标系下的表达。

## 空间雅可比与物体雅可比的联系

物体雅可比和空间雅可比的关系用下式表达
$$
J_s(\theta)=[\text {Ad}_{T_{sb}}]J_b(\theta),\\
J_b(\theta)=[\text {Ad}_{T_{bs}}]J_s(\theta),
$$
这里$T_{sb}=T(\theta)$。

##例子：雅可比计算

**Example 1**: 计算如图的RRRP空间机器人的空间雅可比。

![ScaraRobot](image\ScaraRobot.png)

我们知道雅可比的第$i$列，就是第$i$个关节的螺旋轴（旋量）在空间坐标系（固定坐标）的表示$J_{si}=[\omega_{si},v_{si}]^T$。有时不能直接看出其旋量时，可以通过$[\text {Ad}_{T_{i-1}}]$矩阵对螺旋轴进行坐标变换，得到其在固定坐标系的表示。

(1)观察发现$\omega _{s1}$始终沿$\hat z_s$方向不变，因此$\omega_{s1}=[0,0,1]^T$。选择坐标原点为$q_1$,那么$v_{s1}=[0,0,0]^T$.

(2)$\omega _{s2}$始终沿$\hat z_s$方向不变，因此$\omega_{s2}=[0,0,1]^T$。选择轴线上$[L_1c_1,L_1s_1,0]^T$为$q_2$,其中$c_1=\text{cos}\theta_1,s_1=\text{sin}(\theta_2)$,那么$v_{s2}=-\omega_2\times q_2=[L_1s_1,-L_1c_1,0]^T$.

(3)不管如何运动，$\omega_{s3}$也是沿固定坐标系$\hat z_s$方向，因此$\omega_{s3}=[0,0,1]^2$，选择$q_3=[L_1c_1+L_2c_{12}, L_1s_1+L_2s_{12},0]^T$，其中$c_{12}=\text{cos}(\theta_1+\theta_2),s_{12}=\text{sin}(\theta_1+\theta_2)$，那么$v_{s3}=(L_1s_1+L_2s_{12},-L_1c_1-L_2c_12,0)$.

(4)最后一个关节时移动副，$\omega_{s4}=[0,0,0]^2$,轴的方向为$v_{s4}=[0,0,1]^2$

综合上述分析，空间雅可比为
$$
J_s(\theta)=\left[ \begin{matrix}
0 & 0 & 0& 0\\
0 &0  &0 &0\\
1 & 1 &1 & 0\\
0 &L_1s_1 &L_1s_1+L_2s_{12}&0\\
0 &-L_1c_1& -L_1c_1-L_2c_{12}&0\\
0 & 0& 0 &1
\end{matrix}\right]
$$
**Example 2**: 计算如图的RRPRRR空间机器人的空间雅可比。

![SixAxisRobot](image\SixAxisRobot.png)



(1)第一个轴线始终保持不变，$\omega_{s1}=[0,0,1]^2$，选择$q_1=[0,0,L1]^2$,得到$w_{s1}=-\omega_{s1}\times q_1=[0,0,0]^T$

(2)第二个关节的轴线随$\theta_1$变化，$\omega_{s2}=[-c_1,-s_1,0]^2$ ，选择$q_1=(0,0,L_1)$ ，那么$v_{s2}=-\omega_{s2}\times q_2=[L_1s_1,-L_1c_1,0]$。

(3)第三个关节是移动副，因此$\omega_{s3}=[0,0,0]^T$,轴线方向
$$
v_{s3}=Rot(\hat z,\theta_1)Rot(\hat x,-\theta_2)[0,1,0]^T=[-s_1c_2,c_1c_2,-s_2]^T
$$
(4)后三个轴交于一点
$$
q_w=\left[ \begin{matrix}
0\\
0\\
L_1
\end{matrix}\right]
+Rot(\hat z,\theta_1)Rot(\hat x,-\theta_2)
\left[ \begin{matrix}
0\\
L_2+\theta_3\\
0
\end{matrix}\right]
=
\left[ \begin{matrix}
-(L_2+\theta_3)s_1c_2\\
(L_2+\theta_3)c_1c_2\\
L_1-(L_2+\theta_3)s_2
\end{matrix}\right]
$$
后三个轴的轴线方向为
$$
\omega_{s4}=Rot(\hat z,\theta_1)Rot(\hat x,-\theta_2)
\left[ \begin{matrix}
0\\
0\\
1
\end{matrix}\right]
=
\left[ \begin{matrix}
-s_1s_2\\
c_1s_2\\
c_2
\end{matrix}\right],\\
\omega_{s5}=Rot(\hat z,\theta_1)Rot(\hat x,-\theta_2)Rot(\hat z,\theta_4)
\left[ \begin{matrix}
-1\\
0\\
0
\end{matrix}\right]
=
\left[ \begin{matrix}
-c_1c_4+s_1c_2s_4\\
-s_1c_4-c_1c_2s_4\\
s_2s_4
\end{matrix}\right],\\
\omega_{s6}=Rot(\hat z,\theta_1)Rot(\hat x,-\theta_2)Rot(\hat z,\theta_4)Rot(\hat x,-\theta_5)
\left[ \begin{matrix}
0\\
1\\
0
\end{matrix}\right]\\
=
\left[ \begin{matrix}
-c_5(s_1c_2c_4+c_1s_4)+s_1s_2s_5\\
c_5(c_1c_2c_4-s_1s_4)-c_1s_2s_5\\
-s_2c_4c_5-c_2s_5
\end{matrix}\right]
$$
因此，空间雅可比可以写成矩阵的形式为
$$
J_s(\theta)=\left[ \begin{matrix}
\omega_{s1}&\omega_{s2}&0 &\omega_{s4}&\omega_{s5}& \omega_{s6}\\
0&-\omega_{s2}\times q_2 & v_{s3}&-\omega_{s4}\times q_w &-\omega_{s5}\times q_w& -\omega_{s6}\times q_w
\end{matrix}\right]
$$
注意到，我们不需要对正运动学模型进行微分，就可以直接获得整个雅可比。

## 算法实现（C语言）
基于指数坐标计算雅可比的算法，我已用C语言实现，包括两个函数JacobianBody和JacobianSpace 。源码参见github--[链接](https://github.com/libing403/LearningNotes/tree/master/Robotics/Modern%20Robotics%20Mechanics%20planning%20control)





------

参考文献

Kenvin M. Lynch , Frank C. Park, Modern Robotics Mechanics,Planning , and Control. May 3, 2017



