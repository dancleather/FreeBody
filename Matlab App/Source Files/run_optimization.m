function [ ] = run_optimization(frames,workingfolder)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

running_optimization = 'yes'

if isscalar(frames) == 1
    freebody_optimization_gui;
else
    frames = 100
    freebody_optimization_gui;
end

optimization_complete = 'yes'
    
end

