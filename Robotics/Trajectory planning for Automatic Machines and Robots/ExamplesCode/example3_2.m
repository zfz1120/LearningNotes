%{
使用抛物线过渡线性轨迹,example3.2
Brian
2018-12-22,
%}
close('all')
clc
clear
%%
%已知轨迹给定条件
q0=0;
q1=30;
t0=0;
t1=4;
Ta=1;
Vv=10;
%%
%计算轨迹的离散点
i=1;
Ts=0.001;
for t=t0:Ts:t1
    time(i)=t;
    if(t0 <=t && t<t0+Ta)
        q(i)=q0+Vv/(2.0*Ta)*(t-t0)^2;
        dq(i)=Vv/Ta*(t-t0);
        ddq(i)=Vv/Ta;
    end
    if(Ta <=t && t<t1-Ta)
        q(i)=q0+Vv*(t-t0-Ta/2.0);
        dq(i)=Vv;
        ddq(i)=0;      
    end
    if(t1-Ta<=t&&t<=t1)
        q(i)=q1-Vv/(2.0*Ta)*(t1-t)^2;
        dq(i)=Vv/Ta*(t1-t);
        ddq(i)=-Vv/Ta;
    end
    i=i+1;
end

%%
%设置绘图布局
figure
fig1=subplot(3,1,1);
ylabel('position');
grid on
hold on
fig2=subplot(3,1,2);
ylabel('velocity');
grid on
hold on
fig3=subplot(3,1,3);
ylabel('acceleration');
xlabel('time');
grid on
hold on
%绘图
c1=plot(fig1,time,q,'-r','LineWidth',1.5);
c2=plot(fig2,time,dq,'-b','LineWidth',1.5);
c3=plot(fig3,time,ddq,'-g','LineWidth',1.5);
%end
