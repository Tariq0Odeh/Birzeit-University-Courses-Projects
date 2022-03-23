clear all
close all
clc

syms y(t)
a = diff(y,t) + 30.*y(t) == 20;
c = y(0) == 0;
y(t) = dsolve(a,c)
t = 0:0.01:1; 
x = 20.*(t>=0);
y = double(vpa(y(t)));
subplot (3,1,1);
plot(t,y);
grid on;
ylim([0 1])
title('solve ode')
xlabel('time (Sec)')
ylabel('y(t)')

%***********************************************

f = -100:1:100;
dt = t(2)-t(1);
for i = 1:length(f)
    X(i) = sum(x.*exp(-2.*1i.*pi.*f(i).*t)).*dt;
    Y(i) = sum(y.*exp(-2.*1i.*pi.*f(i).*t)).*dt;
    H(i) = Y(i)/X(i);
end

%***********************************************

subplot (3,1,2);
plot(f,abs(H));
grid on;
title("Magnitude Spectrum");
ylabel("abs H(f)");
xlabel("freq");
subplot (3,1,3);
plot(f,angle(H));
grid on;
title("Phase Spectrum");
ylabel(" angle H(f)"); 
xlabel("freq");

