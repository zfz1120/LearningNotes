%{
OnLineFun.m
S型速度规划在线计算相关子函数定义
%}
function fun=OnLineFun
fun.InitialParam=@InitialParam;
fun.CalcJk1=@CalcJk1;
fun.CalcJk2=@CalcJk2;
fun.CalcQk=@CalcQk;
fun.OnLineCalc=@OnLineCalc;
end

%{
（1）参数合法性检查
（2）初始化参数结构体
%}
function IniParam=InitialParam(q0,q1,v0,v1,a0,a1,v_max,v_min,a_max,a_min,j_max,j_min,Ts)
%参数检查，绝对值小于1.0E-8的数值认为是0.
if(abs(v_max)<1.0E-8)
    disp('参数错误。最大速度不能为0！程序退出。');
    return;
end
if(abs(a_max)<1.0E-8 || abs(a_min)<1.0E-8)
    disp('参数错误。最大/最小加速度不能为0！程序退出。');
    return;
end
if(abs(j_max)<1.0E-8 || abs(j_min)<1.0E-8)
    disp('参数错误。最大/最小加加速度不能为0！程序退出。');
    return;
end
if(abs(q1-q0)<1.0E-8)
    disp('参数错误。输入位移不能为0！程序退出。');
    return;
end
if(Ts<1.0E-8)
    disp('参数错误。采样周期不能为0！程序退出。');
    return;
end
%%
%定义并初始化输入参数的结构体
if(q1-q0>0)
    sigma=1;
else
    sigma=-1;
end
%计算（3.31），
hq0=sigma*q0;
hq1=sigma*q1;
hv0=sigma*v0;
hv1=sigma*v1;
%计算（3.32）
hv_max=(sigma+1)/2*v_max+(sigma-1)/2*v_min;
hv_min=(sigma+1)/2*v_min+(sigma-1)/2*v_max;
ha_max=(sigma+1)/2*a_max+(sigma-1)/2*a_min;
ha_min=(sigma+1)/2*a_min+(sigma-1)/2*a_max;
hj_max=(sigma+1)/2*j_max+(sigma-1)/2*j_min;
hj_min=(sigma+1)/2*j_min+(sigma-1)/2*j_max;
IniParam=struct(...
 'Ts',{Ts},...
'q0',{hq0},...
'q1',{hq1},...
'v0',{hv0},...
'v1',{hv1},...
'a0',{a0},...
'a1',{a1},...
'vmax',{hv_max},...
'vmin',{hv_min},...
'amax',{ha_max},...
'amin',{ha_min},...
'jmax',{hj_max},...
'jmin',{hj_min},...
'sigma',{sigma}...
);

end

%{
计算（3.35），确定加速阶段的加加速度
%}
function jk=CalcJk1(Q0,InParam)
vk=Q0.vk;
ak=Q0.ak;
if((vk-ak^2/(2*InParam.jmin)<InParam.vmax) && ak<InParam.amax)
    jk=InParam.jmax;  
elseif((vk-ak^2/(2*InParam.jmin)<InParam.vmax) && ak >=InParam.amax)
    jk=0;
elseif((vk-ak^2/(2*InParam.jmin)>=InParam.vmax) && ak>0)
    jk=InParam.jmin;
elseif((vk-ak^2/(2*InParam.jmin)>=InParam.vmax) && ak<=0)
    jk=0;
end
if(Q0.k>980)
    Q0.k;
end
end
%{
计算（3.38），确定减速度阶段的加加速度
%}
function jk=CalcJk2(Q0,InParam)
Tj2a=Q0.Tj2a;
Tj2b=Q0.Tj2b;
Td=Q0.Td;
if( (Q0.k-Q0.kd)>0 && (Q0.k-Q0.kd)<=(Tj2a/InParam.Ts))
    jk=InParam.jmin;
elseif((Q0.k-Q0.kd)>(Tj2a/InParam.Ts) && (Q0.k-Q0.kd)<=((Td-Tj2b)/InParam.Ts))
    jk=0;
else
    jk=InParam.jmax;
end

end
%{
计算（3.34），根据当前周期的轨迹点计算下一个周期的轨迹点
%}
function Qk=CalcQk(jk,Q0,InParam)
%Q0为当前周期的值，Qk为下一个周期的值
Qk=Q0;%相当于定义一个Qk
Ts=InParam.Ts;
Qk.k=Q0.k+1;
Qk.t=Q0.t+Ts;
Qk.jk=jk;
Qk.ak=Q0.ak+Ts/2*(Q0.jk+jk);
Qk.vk=Q0.vk+Ts/2*(Q0.ak+Qk.ak);
Qk.qk=Q0.qk+Ts/2*(Q0.vk+Qk.vk);

end

%{
S型速度在线规划
%}
function Qk=OnLineCalc(Q0,InParam)
Qk=Q0;
jmax=InParam.jmax;
jmin=InParam.jmin;
q1=InParam.q1;
amin=InParam.amin;
a0=InParam.a0;
a1=InParam.a1;
v1=InParam.v1;
%判断减速点
if(Q0.flag<1) 
    Tj2a=(amin-Q0.ak)/jmin;
    Tj2b=(a1-amin)/jmax;
    Td=(v1-Q0.vk)/amin+Tj2a*(amin-Q0.ak)/(2*amin)+...
        Tj2b*(amin-a1)/(2*amin);
    if(Td>=Tj2a+Tj2b)
        %达到最小加速度
    else
        %不能达到最小加速度
        Tj2a=-Q0.ak/jmin+sqrt((jmax-jmin)*(Q0.ak^2*jmax-jmin*(a1^2+2*jmax*(Q0.vk-v1))))/(jmin*(jmin-jmax));
        Tj2b=a1/jmax+sqrt((jmax-jmin)*(Q0.ak^2*jmax-jmin*(a1^2+2*jmax*(Q0.vk-v1))))/(jmax*(jmax-jmin));
        Td=Tj2a+Tj2b;
    end
    hk=1.0/2*Q0.ak*Td^2+1.0/6*(jmin*Tj2a*(3*Td^2-3*Td*Tj2a+Tj2a^2)+jmax*Tj2b^3)+Td*Q0.vk;
    if(hk<q1-Q0.qk)
        %未进入减速段
    else
        %进入减速阶段
        Q0.flag=1;
        Q0.kd=Q0.k;
        Q0.Tj2a=Tj2a;
        Q0.Tj2b=Tj2b;
        Q0.Td=Td;
    end
end
if(Qk.flag<1)
    %还未到减速段
    jk=CalcJk1(Q0,InParam);
else
    %进入减速段
   jk=CalcJk2(Q0,InParam);
end
   Qk=CalcQk(jk,Q0,InParam);
   if(Qk.qk>=InParam.q1)
       Qk.qk=InParam.q1;
       Qk.flag=2;
   end
   Qk.qk=InParam.sigma*Qk.qk;
   Qk.vk=InParam.sigma*Qk.vk;
   Qk.ak=InParam.sigma*Qk.ak;
   Qk.jk=InParam.sigma*Qk.jk;
end

