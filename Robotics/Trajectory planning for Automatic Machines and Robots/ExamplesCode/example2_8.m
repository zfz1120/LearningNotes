%example2.8
clc
clear
%轨迹定义条件
t_array=[0,2,4,8,10];
q_array=[10,20,0,30,40];
v_array=[-1,-10,5,3,8];
%计算轨迹
%初始位置
t=t_array(1);
q=q_array(1);
v=v_array(1);
v_array2=v_array;

for k=1:length(t_array)-1
    %按照式（1-23）式确定中间点的速度值
    if(k>1)
        dk1=(q_array(k)-q_array(k-1))/(t_array(k)-t_array(k-1));
        dk2=(q_array(k+1)-q_array(k))/(t_array(k+1)-t_array(k));
        if((dk2>=0 && dk1>=0) || (dk2<=0 && dk1<=0))
            v_array2(k)=1.0/2.0*(dk1+dk2);
        else
            v_array2(k)=0;
        end  
    end
end

%计算各段轨迹
for k=1:length(t_array)-1
    %计算各段多项式的系数
    h(k)=q_array(k+1)-q_array(k);
    T(k)=t_array(k+1)-t_array(k);
    a0(k)=q_array(k);
    a1(k)=v_array2(k);
    a2(k)=(3*h(k)-(2*v_array2(k)+v_array2(k+1))*T(k))/(T(k)*T(k));
    a3(k)=(-2*h(k)+(v_array2(k)+v_array2(k+1))*T(k))/(T(k)*T(k)*T(k));
    
    %生成各段轨迹密化的数据点
    %局部时间坐标
    tau=t_array(k):T(k)/100:t_array(k+1);
    %全局时间坐标，由局部时间坐标组成
    t=[t,tau(2:end)];
    %局部位置坐标
    qk=a0(k)+a1(k)*power(tau-tau(k),1)+a2(k)*power(tau-tau(k),2)+a3(k)*power(tau-tau(k),3);
    %全局位置坐标
    q=[q,qk(2:end)];
    %速度
    vk=a1(k)+2*a2(k)*power(tau-tau(k),1)+3*a3(k)*power(tau-tau(k),2);
    v=[v,vk(2:end)];
    %加速度
    acck=2*a2(k)+6*a3(k)*power(tau-tau(k),1);
    if(k==1)
        acc=2*a2(k);
    end
    acc=[acc,acck(2:end)];
    
end
%绘图
subplot(3,1,1);
h2=plot(t,q,'--r');
legend(h2,'第二种方式')
hold on;
plot(t_array,q_array,'^r');
axis([0,10,-5,45]);
ylabel('position')
grid on;
subplot(3,1,2);
plot(t_array,v_array2,'^b');
hold on;
plot(t,v,'--b');
axis([0,10,-20,15]);
ylabel('velocity')
grid on;
subplot(3,1,3);
plot(t,acc,'--g');
axis([0,10,-45,45]);
ylabel('acceleration')
grid on;

