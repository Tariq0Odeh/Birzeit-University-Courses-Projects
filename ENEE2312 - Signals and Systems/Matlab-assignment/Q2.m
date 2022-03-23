clear all
close all
clc

syms t
y1 = sin(200.*pi.*t);
T1 = 1/100;
y2 = cos(500.*pi.*t);
T2 = 1/250;
y = y1.*y2;
subplot(2,2,2)
fplot( t,y1,[-T1,T1] )
title('sin(200.*pi.*t)')
xlabel('time (s)')
ylabel('y1')
subplot(2,2,4)
fplot( t,y2,[-T2,T2] )
title('cos(500.*pi.*t)')
xlabel('time (s)')
ylabel('y2')
subplot(2,2,[1,3])
fplot( t,y,[-2e-2,2e-2])
title('sin(200.*pi.*t) * cos(500.*pi.*t)')
xlabel('time (s)')
ylabel('y1*y2')
