clear all
close all
clc

t = 0:12;
e = 10.*exp(-0.2.*t);
a = rectangularPulse((t-7)/4);
x = e.*a;
subplot(2,2,1)
plot(x)
ylim([0 5])
title('x(t)')
xlabel('time')
ylabel('Amp')

a = 10.*exp(0.2.*t);
b = rectangularPulse((t-1)/2);
h = a.*b;
subplot(2,2,2)
plot(h)
ylim([0 15])
title('h(t)')
xlabel('time')
ylabel('Amp')

y=conv(x,h);
subplot(2,2,[3 4]);
plot(y)
ylim([0 70])
title('convolution')
xlabel('time')
ylabel('Amp')
