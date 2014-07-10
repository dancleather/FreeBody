function [ ] = plot_activations(frames,x,y,z,axis_limits,workingfolder)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here



if isscalar(frames) == 1
    freebody_plot_activations_gui_2;
else
    frames = 100;
    freebody_plot_activations_gui_2;
end
    
    
end

