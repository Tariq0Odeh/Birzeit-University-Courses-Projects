clear all
close all
clc

syms t n
x = symsum(rectangularPulse((t-(3.*n))/2),n,-Inf,Inf);
fplot(x)
title('A finite pulse')
xlabel('times (s)')
ylabel('X(t)')