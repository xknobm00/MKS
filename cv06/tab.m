clear all;
close all;

ntc = csvread('ntc.csv')';

temp1 = ntc(1,:);
r = ntc(2,:);

adc1 = r./(r+10).*(1024);

plot(adc1, temp1, 'o')

p = polyfit(adc1,temp1, 10);

ad2 = 0:1023;
t2 = round(polyval(p, ad2), 1);
hold on, plot(ad2, t2, 'r');

dlmwrite('data.dlm', t2*10, ',');

x = dlmread('data.dlm');