clear;
clc;
close all;

addpath('./CCSS_ref_data');
addpath('./plainC_SimOutput');

% load C-Code output data
load CHC_out_I.am;
load CHC_out_Q.am;

% load System Studio Reference output data
load ChannelCorr_out_real.am;
load ChannelCorr_out_imag.am;

figure(1)
plot(CHC_out_I)
hold on;
plot(ChannelCorr_out_real, 'r')
hold off;
title('CHC out I vs. ChannelCorr out real');
grid;

figure(2)
plot(CHC_out_Q)
hold on;
plot(ChannelCorr_out_imag, 'r')
hold off;
title('CHC out Q vs. ChannelCorr out imag');
grid;


Delta_real = sqrt((sum((ChannelCorr_out_real(1:2028,1) - CHC_out_I(1:2028,1)).^2))/2028)
Delta_imag = sqrt((sum((ChannelCorr_out_imag(1:2028,1) - CHC_out_Q(1:2028,1)).^2))/2028)
