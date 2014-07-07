function [ ] = run_post_processing(frames,workingfolder,bw)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

if isscalar(frames) == 1
    post_processing_analysis_gui;
else
    frames = 100
    post_processing_analysis_gui;
end
    
end

