function [x,y,z,colours,x_orig,y_orig,z_orig,colour_orig,axis_limits] = ...
    load_activations(frames,workingfolder)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

loading_data = 'yes'

if isscalar(frames) == 1
    freebody_plot_gui_1;
else
    frames = 100;
    freebody_plot_gui_1;
end
    
data_loaded = 'yes'

end

