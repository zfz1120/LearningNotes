clc
clear
close('all')
%%
%定义轨迹边界条件及约束条件
Ts=0.001;
q0=0;
q1=10;
v0=1;
v1=0;
a0=0;
a1=0;
v_max=5;
v_min=-5;
a_max=10;
a_min=-10;
j_max=30;
j_min=-30;
%%
%调用算法子函数，进行速度规划，得到规划结果
fun=OnLineFun();
InParam=fun.InitialParam(q0,q1,v0,v1,a0,a1,v_max,v_min,a_max,a_min,j_max,j_min,Ts);
%初始化输出结构体
%falg:  轨迹点标志，0处于加速度段，1处于减速段，2到达终点
%   k:   轨迹点索引，初始位置q0为第一个轨迹点
% kd:   减速开始轨迹点的索引
Qk=struct('flag',{0},'k',{1},'kd',{0},'t',{0},'qk',{q0},'vk',{v0},'ak',{a0},'jk',{j_max},'Tj2a',{0},'Tj2b',{0},'Td',{0});

while(Qk.flag<2)
    time(Qk.k)=Qk.t;
    dis(Qk.k)=Qk.qk;
    vel(Qk.k)=Qk.vk;
    acc(Qk.k)=Qk.ak;
    jerk(Qk.k)=Qk.jk;
    Qk=fun.OnLineCalc(Qk,InParam);
end
%%
%绘图
hold on
%位置
subplot(4,1,1)
plot(time,dis,'r','LineWidth',1.5);
grid on
ylabel('position')
%速度
subplot(4,1,2)
plot(time,vel,'b','LineWidth',1.5);
grid on
hold on
ylabel('velocity')
v_ref1=v_max*ones(1,length(time));
v_ref2=v_min*ones(1,length(time));
plot(time,v_ref1,'b--','LineWidth',1.5);
plot(time,v_ref2,'b--','LineWidth',1.5);
%加速度
subplot(4,1,3)
plot(time,acc,'g','LineWidth',1.5);
grid on
hold on
ylabel('acceleration')
a_ref1=a_max*ones(1,length(time));
a_ref2=a_min*ones(1,length(time));
plot(time,a_ref1,'g--','LineWidth',1.5);
plot(time,a_ref2,'g--','LineWidth',1.5);
%加加速度
subplot(4,1,4)
plot(time,jerk,'m','LineWidth',1.5)
grid on
hold on
ylabel('jerk')
j_ref1=j_max*ones(1,length(time));
j_ref2=j_min*ones(1,length(time));
plot(time,j_ref1,'m--','LineWidth',1.5);
plot(time,j_ref2,'m--','LineWidth',1.5);
%结束
