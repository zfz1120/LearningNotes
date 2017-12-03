%example2.6
clc
clear
%轨迹定义条件
%时间
t0=0;
t1=8;
%位置和速度（a）
q0=0;
q1=10;
v0=0;
v1=0;
%利用公式（1-22）求系数
h=q1-q0;
T=t1-t0;
a0=q0;
a1=v0;
a2=(3*h-(2*v0+v1)*T)/(T*T);
a3=(-2*h+(v0+v1)*T)/(T*T*T);
%轨迹生成
t=t0:0.1:t1;
%位置
q=a0+a1*power((t-t0),1)+a2*power((t-t0),2)+a3*power((t-t0),3);
%速度
v=a1+2*a2*power((t-t0),1)+3*a3*power((t-t0),2);
%加速度
acc=2*a2+6*a3*power((t-t0),1);
%绘图
subplot(3,2,1)
plot(t,q,'r');
ylabel('position')
grid on
subplot(3,2,3)
plot(t,v,'b');
ylabel('velocity')
grid on
subplot(3,2,5)
plot(t,acc,'g');
xlabel('(a)');
ylabel('acceleration')
grid on

%时间
t0=0;
t1=8;
%位置和速度（b）
q0=0;
q1=10;
v0=-5;
v1=-10;
%利用公式（1-22）求系数
h=q1-q0;
T=t1-t0;
a0=q0;
a1=v0;
a2=(3*h-(2*v0+v1)*T)/(T*T);
a3=(-2*h+(v0+v1)*T)/(T*T*T);
%轨迹生成
t=t0:0.1:t1;
%位置
q=a0+a1*power((t-t0),1)+a2*power((t-t0),2)+a3*power((t-t0),3);
%速度
v=a1+2*a2*power((t-t0),1)+3*a3*power((t-t0),2);
%加速度
acc=2*a2+6*a3*power((t-t0),1);
%绘图
subplot(3,2,2)
plot(t,q,'r');
ylabel('position')
grid on
subplot(3,2,4)
plot(t,v,'b');
ylabel('velocity')
grid on
subplot(3,2,6)
plot(t,acc,'g');
xlabel('(b)');
ylabel('acceleration')
grid on


