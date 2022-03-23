
clear all
close all
clc

t = -7:0.01:7;
X1 = heaviside(t+3)-heaviside(t-4);
figure (1)
plot (t, X1)
title('X1(t)= u(t+3)-u(t-4)')

