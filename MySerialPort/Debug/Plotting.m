Data1=load('ecgdata.txt');% load the heart rate
Data2=load('accdata.txt');% load the breathing rate and GSR
fs=50;%sample frequency
t=(1:length(Data1))./fs;% relative time start from 0:00

HeartRate = Data1(:,1);
BreathingRate = Data2(:,2);
GSR = Data2(:,1);

figure 
subplot(3,1,1)
plot(t,HeartRate);
title('Heart Rate');
xlim([0 max(t)]);
subplot(3,1,2)
plot(t,BreathingRate);
title('Breathing Rate');
xlim([0 max(t)]);
subplot(3,1,3)
plot(t,GSR);
title('GSR');
xlim([0 max(t)]);