clc
clear
close('all')
rad=pi/180;
pos=[10 , 15 , 30, 15*rad, 20*rad;
         15, 30,   35, 20*rad, 30*rad;
         50,  40,  70,  45*rad,60*rad;
         32,  55,  85,  80*rad,30*rad;
         45,  65,  90,  60*rad,70*rad];

 N=5;
 t=[0,0.2,0.5,0.8,1.0];
 for i=1:N
     posA(i)=pos(i,4);
     posC(i)=pos(i,5);
 end
 figure
 ah=plot(t,posA,'g');
 hold on
 ch=plot(t,posC,'b');
 legend([ah ch],'A÷·','C÷·');
 xlabel('time(s)')
 ylabel('AC÷·Œª“∆')
 grid on
 
 
 
 
 
 
 
 
 
 