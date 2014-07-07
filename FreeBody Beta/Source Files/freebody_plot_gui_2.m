muscles = 163;
frequency = 200;

figure('OuterPosition',[300,100,400,650],'Name','Model Geometry',...
    'NumberTitle','off');
leg{1} = plot3(z{1,1},x{1,1},y{1,1},'Color',colours(1,:));
hold on;
scat = scatter3(z_orig{1},x_orig{1},y_orig{1},25,colour_orig,'fill');
hold off;

for k = 2:(muscles+1)
    leg{k} = line(z{k},x{k},y{k},'Color',colours(k,:));
end
set(leg{164},'LineWidth',3);


axis equal
axis (axis_limits,'xy') %[-0.6 0 -0.2 0.5 -0.1 1.8]
view(70,20)

for h = 2:frames

set(scat,'XData',z_orig{h},'YData',x_orig{h},'ZData',y_orig{h});    
    
pause(1/frequency);    
set(leg{1},'XData',z{1,h});
set(leg{1},'YData',x{1,h});
set(leg{1},'ZData',y{1,h});

for k = 2:(muscles+1)
    set(leg{k},'XData',z{k,h});
    set(leg{k},'YData',x{k,h});
    set(leg{k},'ZData',y{k,h});
end

drawnow

end


