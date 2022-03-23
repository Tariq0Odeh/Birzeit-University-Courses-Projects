clear all
close all
clc

t = 0:0.01:16;
r1 = (t-4).*heaviside (t-4); 
r2 = (t-7).*heaviside (t-7);
r3 = (t-13).*heaviside (t-13);
X2 = heaviside(t-4) + r1 - 2*r2 + r3;
plot(t,X2)
title('X2(t)= u(t-4) +r(t-4)-2r(t-7) +r(t-13)')
xlabel('times (s)')
ylabel('X2(t)')