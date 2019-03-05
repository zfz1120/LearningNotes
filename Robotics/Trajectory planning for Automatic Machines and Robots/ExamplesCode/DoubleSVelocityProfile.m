%{
%SProfileTest.m
S型速度规划测试程序，2019.02.12，Brian
（1）输入轨迹的边界条件及约束条件；
（2）绘制速度规划的结果。
%}
clc
clear
close('all')
%%
%定义轨迹边界条件及约束条件
q0=-5;
q1=10;
v0=-3;
v1=0;
v_max=10;
a_max=10;
j_max=30;
%%
%调用算法子函数，进行速度规划，得到规划结果
fun=CalcFun();
Param=fun.CalcSProfile(q0,q1,v0,v1,v_max,a_max,j_max);
%%
%根据规划结果，调用算法子函数计算轨迹
Ts=0.001;
i=0;
for t=0:Ts:Param.T
    i=i+1; 
    time(i)=i*Ts;
    dis(i)=fun.displacement(t,Param);
    vel(i)=fun.velocity(t,Param);
    acc(i)=fun.acceleration(t,Param);
    jerk(i)=fun.jerk(t,Param);
end
%%
%绘图
figure
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
v_ref2=-v_max*ones(1,length(time));
plot(time,v_ref1,'b--','LineWidth',1.5);
plot(time,v_ref2,'b--','LineWidth',1.5);
%加速度
subplot(4,1,3)
plot(time,acc,'g','LineWidth',1.5);
grid on
hold on
ylabel('acceleration')
a_ref1=a_max*ones(1,length(time));
a_ref2=-a_max*ones(1,length(time));
plot(time,a_ref1,'g--','LineWidth',1.5);
plot(time,a_ref2,'g--','LineWidth',1.5);
%加加速度
subplot(4,1,4)
plot(time,jerk,'m','LineWidth',1.5)
grid on
hold on
ylabel('jerk')
j_ref1=j_max*ones(1,length(time));
j_ref2=-j_max*ones(1,length(time));
plot(time,j_ref1,'m--','LineWidth',1.5);
plot(time,j_ref2,'m--','LineWidth',1.5);
%结束