cd('./Files/Outputs/optimization')

muscles = 163;
frequency = 200;

force = zeros(frames,muscles);


force_ub_time = importdata('force_ub.txt');
force_in = importdata('force.txt');
solve_in = importdata('solve.txt');

num_frames_opt = size(force_in,1);

for i = 1:num_frames_opt
    if (solve_in(i) == 5) || (solve_in(i) == 1)
       for j = 1:muscles
        
            force(i,j)=force_in(i,j);
       end
    else
        force(i,:)=0;
    end
end



for i = 1:163                 % default muscles in grey
colours(i,:)=[0.7 0.7 0.7];
line_w(i)=0.5;
end



figure('OuterPosition',[300,100,400,650],'Name','Model Activations',...
    'NumberTitle','off');
leg{1} = plot3(z{1,1},x{1,1},y{1,1},'Color',colours(1,:),'LineWidth',line_w(1));

for k = 2:muscles
    leg{k} = line(z{k},x{k},y{k},'Color',colours(k,:),'LineWidth',line_w(k));
end


axis equal
axis (axis_limits,'xy')
view(70,20)

M(1) = getframe(gcf);

for h = 2:frames
    
       for i = 1:muscles
        activation(h,i) = force(h,i)/force_ub_time(h,i);
    
        if activation(h,i) > 1
            colours(i,:) = [0.98 0 0];
            line_w(i) = 2;
        elseif activation(h,i) > 0.05 
           colours(i,:) = [0.98 (0.8*(1-activation(h,i))) (0.8*(1-activation(h,i)))];
           line_w(i) = 2;
        else
           colours(i,:) = [0.5 0.5 0.5];
           line_w(i) = 0.5;
        end
       end


%pause(1/frequency);    
set(leg{1},'XData',z{1,h});
set(leg{1},'YData',x{1,h});
set(leg{1},'ZData',y{1,h});
set(leg{1},'Color',colours(1,:),'LineWidth',line_w(1));

for k = 2:muscles
    set(leg{k},'XData',z{k,h});
    set(leg{k},'YData',x{k,h});
    set(leg{k},'ZData',y{k,h});
    set(leg{k},'Color',colours(k,:),'LineWidth',line_w(k));
end

drawnow

M(h) = getframe(gcf);

end

cd(workingfolder);
cd('./Files/Outputs')

save('film.mat','M')

myVideo = VideoWriter('freebody_video.avi');
myVideo.FrameRate = 30;
myVideo.Quality = 90;
open(myVideo);
writeVideo(myVideo, M);
close(myVideo);


