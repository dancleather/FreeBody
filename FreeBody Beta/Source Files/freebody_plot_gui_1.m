

cd('./Files/Outputs/muscle_geometry')


for i = 1:163                 % default muscles in grey
colours(i,:)=[0.75 0.75 0.75];
end
for i = 1:25                  % adductors in green
colours(i,:)=[0 0.4 0];
end
for i = 26:29                 % hamstrings in grey
colours(i,:)=[0.3 0.3 0.3];
end
for i = 42:43                 % gastrocnemius in red
colours(i,:)=[0.6 0 0];
end
for i = 46:69                 % glute max in red
colours(i,:)=[0.4 0 0];
end
for i = 70:72                 % glute min in light blue
colours(i,:)=[0 0 0.8];
end
for i = 75:83                 % iliopsoas in gold
colours(i,:)=[1 0.8 0];
end
for i = 109:112               % iliopsoas in gold
colours(i,:)=[1 0.8 0];
end
for i = 117:118               % quads in pink
colours(i,:)=[1 0.5 0.5];
end
for i = 119:120               % sartorius in light green
colours(i,:)=[0 0.8 0];
end
for i = 121:122               % hamstrings in black
colours(i,:)=[0.3 0.3 0.3];
end
for i = 123:128               % soleus in purple
colours(i,:)=[0.5 0 0.5];
end
for i = 140:163               % quads in pink
colours(i,:)=[1 0.5 0.5];
end
colours(164,:)=[0.5 0 0];


muscles = 163;
frequency = 200;

origins = importdata('origins.txt');
rot_centres = importdata('rot_centres_gcs.txt');
tf_contact = importdata('tf_contact_gcs.txt');
max_origins = max(origins);
min_origins = min(origins);
axis_limits = [(min_origins(3)-0.5) (max_origins(3)+0.5) (min_origins(1)-0.5) (max_origins(1)+0.5) (min_origins(2)-0.2) (max_origins(11)+0.2)];

for k=1:frames
    for l=1:5
        x_orig{k}(l)=origins(k,3*(l-1)+1);
        y_orig{k}(l)=origins(k,3*(l-1)+2);
        z_orig{k}(l)=origins(k,3*(l-1)+3);
    end
    for l=6:8
        x_orig{k}(l)=rot_centres(k,3*(l-6)+1);
        y_orig{k}(l)=rot_centres(k,3*(l-6)+2);
        z_orig{k}(l)=rot_centres(k,3*(l-6)+3);
    end
    for l=9:10
        x_orig{k}(l)=tf_contact(k,3*(l-9)+1);
        y_orig{k}(l)=tf_contact(k,3*(l-9)+2);
        z_orig{k}(l)=tf_contact(k,3*(l-9)+3);
    end
end

for i = 1:5                 
    colour_orig(i,:)=[0 0 0.5];
end
for i = 6:8                  
    colour_orig(i,:)=[0 0.5 0];
end
for i = 9:10                 
    colour_orig(i,:)=[0.5 0 0];
end


for k = 1:muscles
     myfilename = sprintf('muscle_path%d.txt', k-1);
     muscle{k} = importdata(myfilename);

    points=size(muscle{k},2)/3;
    for l=1:frames
    for i=0:points-1
        x{k,l}(i+1)=muscle{k} (l,3*i+1);
        y{k,l}(i+1)=muscle{k} (l,3*i+2);
        z{k,l}(i+1)=muscle{k} (l,3*i+3);
    end
    end
defining_muscle = k
end

myfilename = 'patella.txt';
muscle{164} = importdata(myfilename);

points=4;
for l=1:frames
  for i=0:points-1
    x{164,l}(i+1)=muscle{164} (l,3*i+1);
    y{164,l}(i+1)=muscle{164} (l,3*i+2);
    z{164,l}(i+1)=muscle{164} (l,3*i+3);
  end
end
defining_muscle = 164

cd(workingfolder);
