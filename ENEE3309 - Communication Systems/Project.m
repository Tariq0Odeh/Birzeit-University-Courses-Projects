clear all
close all
clc

%AM signal s(t) = Ac[1 + u cos(2pifmt)]cos(2pifct) 
u = 0.25;               %modulation index
Ac = 1;                 %amplitude of the carrier signal
fc = 25;                %frequency of the the carrier signal
fm = 1;                 %frequency of the modulating signal
Tc = 1/fc;             
Tm = 1/fm;              
t = 0: 0.0001 :2*Tm;    %time vector 
tau = Tc: 0.0001 :Tm;   %1/fc << tau << 1/fm

%--------------------------------------------------------%
%plot modulating signal Message m(t) = cos(2pifmt) 
mt = cos(2.*pi.*fm.*t);
subplot (3,1,1)
plot (t,mt)
axis([0 2 -2 2]);
grid on
title('Modulating Signal Message m(t)')
xlabel('Time (s)')
ylabel('Message m(t)')

%--------------------------------------------------------%
%plot AM signal s(t) = Ac[1 + u cos(2pifmt)]cos(2pifct) 
st = (Ac.*(1 + u.*mt).*cos(2.*pi.*fc.*t));
subplot (3,1,2)
plot (t,st)
axis([0 2 -2 2]);
grid on
title('AM Signal s(t)')
xlabel('Time (s)')
ylabel('Signal Amplitude (volts)')

%--------------------------------------------------------%
%s(t)passed through an ideal envelope detector,
%plot the demodulated signal 
yi = abs(Ac.*(1 + u.*cos(2.*pi.*fm.*t)));
subplot (3,1,3)
plot (t,yi,t,st)
axis([0 2 -2 2]);
grid on
title('Demodulated Signal yi(t)')
xlabel('Time (s)')
ylabel('yi(t)')

%--------------------------------------------------------%
time_length = length(t);       %length of time vector
tau_length = length(tau);      %length of tau vector

y = zeros(1,time_length);            %output signal
D_matrix = zeros(1,tau_length);      %mean squared error

for i = 1: 1 :tau_length        %first loop for tau
    max = st(1);        %max = 1*[1+u*1*cos(0)]cos(0) --> 1+u --> 1.25
    delay = 0;
    D = 0;
    
    for j = 1: 1 :time_length   %second loop for tau
        %Diode is off
        if st(j) <  max*exp(-1*(t(j)-delay)/tau(i)) 
            y(j) =  max*exp(-1*(t(j)-delay)/tau(i));
            
        %Diode is on    
        elseif st(j) >=  max*exp(-1*(t(j)-delay)/tau(i))
            y(j) = st(j);
            
            %update the max and delay
            if st(j) == yi(j)
                delay = t(j);
                max = st(j);
            end  
        end
        D = D + ((yi(j) - y(j)).^2);  %find the integration value   
    end
     D_matrix(i)=(1/time_length)*D;   %find the mean squared error value
end

%find minimum value of D
minimum_D = min(D_matrix);     
disp('The minimum value of D:')
disp(minimum_D)

%find minimum value of time constant that minimizes D
[~,x] = min(D_matrix); 
disp('value of the time constant that minimizes D:')
disp(tau(1,x))

figure
subplot (2,1,1)
plot(tau,D_matrix)
grid on
subplot (2,1,2)
plot(t,y)
grid on