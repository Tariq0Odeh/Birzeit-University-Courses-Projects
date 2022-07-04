clc
clear
close all
%----------------------------------------------------------------
%Print the Menu

    fprintf(' +---------------------------------------------------------------------------------------------------------+\n');
    fprintf(' |        [Welcome in this system to identification of males and females from their speech analysis]       |\n');
    fprintf(' +---------------------------------------------------------------------------------------------------------+\n');
    fprintf(' |  [Please use the next formula [''data#.wav''] where # is the number of file when enter the name of file]  |\n');
    fprintf(' +---------------------------------------------------------------------------------------------------------+\n');

%----------------------------------------------------------------
%Read an audio file.
%Find its sampling frequency (Fs).

    file = input('       #-->Please use name of file:   ');
    fileReader = dsp.AudioFileReader(file)
    [A,Fs] = audioread(file);
    figure;
    plot(A)         %plot audio file
    title('Audio');
    xlabel('Time');
    ylabel('Amplitude');
    grid
    
%----------------------------------------------------------------
%Find the values.

    m500 = Fs/500;                      %maximum speech Fx at 500Hz
    m50 = Fs/50;                        %maximum speech Fx at 50Hz
    windowLength = round(0.03*Fs);      %short frames 30ms
    overlapLength = round(0.01*Fs);     %overlap 10ms
    F0 = pitch(A,Fs);                   %estimates of the fundamental frequency 
     
%----------------------------------------------------------------
%Autocorrelation.

    AUCO = xcorr(A,m50);
    Delay = (-m50:m50)/Fs;                
    figure;
    plot(Delay,AUCO);             %plot autocorrelation
    title('Autocorrelation');
    xlabel('Delay(s)');
    ylabel('Correlation Coefficient');
    grid
    AUCO = AUCO(m50 + 1 : 2 * m50 + 1);    %region corresponding to positive delays
    [AUCO_max, Tx] = max(AUCO(m500:m50));
    Fx = Fs/(m500 + Tx - 1);
    
%----------------------------------------------------------------    
%Threshold frequency (Fth) of a male voice lies between 85-155 Hz
%Threshold frequency (Fth) of a female voice lies between 165 to 255 Hz

    Fth = ((155 + 165) / 2);        %Threshold frequency (Fth)
    Fmax = 255;
    Fmin = 85;

    if( Fx >= Fmin && Fx < Fth )
           fprintf('--->[It is a male voice!]\n');
           
    elseif( Fx <= Fmax && Fx > Fth )
           fprintf('--->[It is a female voice!]\n');
           
    else
           fprintf('Unable to identification, please make sure the sound is clear!!\n');
    end
    
%----------------------------------------------------------------
