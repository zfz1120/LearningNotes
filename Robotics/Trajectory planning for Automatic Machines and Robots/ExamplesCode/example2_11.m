%example2.11,七次多项式轨迹
clc
clear
close('all')
%轨迹定义条件
t0=0;t1=8;
q0=0;q1=10;
v0=0;v1=0;
acc0=0;acc1=0;
j0=0;j1=0;
%利用（1-26）式求系数
h=q1-q0;
T=t1-t0;

a0=q0;
a1=v0;
a2=acc0/2;
a3=j0/6;
a4=1.0/(6*power(T,4))*(210*h-T*((30*acc0-15*acc1)*T+(4*j0+j1)*T*T+120*v0+90*v0));
a5=1.0/(2*power(T,5))*(-168*h+T*((20*acc0-14*acc1)*T+(2*j0+j1)*T*T+90*v0+78*v1));
a6=1.0/(6*power(T,6))*(420*h-T*((45*acc0-39*acc1)*T+(4*j0+3*j1)*T*T+216*v0+204*v1));
a7=1.0/(6*power(T,7))*(-120*h+T*((12*acc0-12*acc1)*T+(j0+j1)*T*T+60*v0+60*v1));
%计算轨迹
t=linspace(t0,t1,100);
%位置
q=a0+a1*power(t-t0,1)+a2*power(t-t0,2)+a3*power(t-t0,3)+a4*power(t-t0,4)+...
    +a5*power(t-t0,5)+a6*power(t-t0,6)+a7*power(t-t0,7);
%速度
v=a1+2*a2*power(t-t0,1)+3*a3*power(t-t0,2)+4*a4*power(t-t0,3)+5*a5*power(t-t0,4)+...
    +6*a6*power(t-t0,5)+7*a7*power(t-t0,6);
%加速度
acc=2*a2+2*3*a3*power(t-t0,1)+3*4*a4*power(t-t0,2)+4*5*a5*power(t-t0,3)+...
    +5*6*a6*power(t-t0,4)+6*7*a7*power(t-t0,5);
%加加速度
j=2*3*a3+2*3*4*a4*power(t-t0,1)+3*4*5*a5*power(t-t0,2)+...
    +4*5*6*a6*power(t-t0,3)+5*6*7*a7*power(t-t0,4);

%绘图
subplot(4,1,1)
plot(t,q,'r');
hold on
axis([0,8,-1,12])
ylabel('position')
grid on
subplot(4,1,2)
plot(t,v,'b');
hold on
 axis([0,8,-1,3])
ylabel('velocity')
grid on
subplot(4,1,3)
plot(t,acc,'g');
axis([0,8,-1.5,1.5])
ylabel('acceleration')
grid on
subplot(4,1,4)
plot(t,j,'k');
axis([0,8,-1.1,1])
ylabel('jerk')
grid on
