%{
一般的抛物线过渡线性轨迹（梯形速度曲线）,example3.3
Brian
2018-12-23,
%}
%  close('all')
clc
clear
%给定的轨迹参数
t0=2;
q0=5;
q1=20;
v0=30;
v1=20;
vmax=150;
aa=1000;
ad=-1500;
%%
%设置绘图布局

fig1=subplot(3,1,1);
axis([2,2.6 ,0,25])
ylabel('position');
grid on
hold on
fig2=subplot(3,1,2);
axis([2,2.6 ,0,200])
ylabel('velocity');
grid on
hold on
fig3=subplot(3,1,3);
axis([2,2.6 ,-1600,1600])
ylabel('acceleration');
xlabel('time');
grid on
hold on
for k=1:50%循环画图
    
vmax=max(v0,v1)+3*k;
h=q1-q0;
%确定最大速度
vf=sqrt((2*aa*ad*h-aa*v1^2+ad*v0^2)/(ad-aa));
if(vf>vmax)
    Vv=vmax;
else
    Vv=vf;
end
%计算加速和减速段时间
Ta=(Vv-v0)/aa;
La=v0*Ta+1.0/2.0*aa*Ta^2;
Td=(v1-Vv)/ad;
Ld=Vv*Td+1.0/2.0*ad*Td^2;
Tv=(h-(Vv^2-v0^2)/(2.0*aa)-(v1^2-Vv^2)/(2.0*ad))/Vv;
Lv=h-La-Ld;

%计算轨迹的离散点
Ts=0.001;
j=1;
for t=t0:Ts:t0+Ta+Tv+Td
    time(j)=t;
    t=t-t0;
    if(t>=0&&t<Ta)
        q(j)=q0+v0*t+1.0/2.0*aa*t^2;
        dq(j)=v0+aa*t;
        ddq(j)=aa;
    end

   if(t>=Ta &&t<Ta+Tv)
       q(j)=q0+La+Vv*(t-Ta);
       dq(j)=Vv;
       ddq(j)=0;
   end
   if(t>Ta+Tv)
       q(j)=q0+La+Lv+Vv*(t-Ta-Tv)+1.0/2.0*ad*(t-Ta-Tv)^2;
       dq(j)=Vv+ad*(t-Ta-Tv);
       ddq(j)=ad;
   end   
   j=j+1;
end
%绘图 
if(k>1)
delete(c1)
delete(c2)
delete(c3)
end
c1=plot(fig1,time,q,'-r','LineWidth',1.5);
c2=plot(fig2,time,dq,'-b','LineWidth',1.5);
c3=plot(fig3,time,ddq,'-g','LineWidth',1.5);
clear time   q dq ddq  
pause(0.2)
end