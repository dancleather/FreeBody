% Optimization routine

cd('./Files/Outputs/optimization/')

start = 3;              % Default = 3
finish = frames-2;      % Default = frames-2

segments = 3;                       %
muscles = 163;
pat_tendon_force = 1;
ligaments = 14;
joint_contacts = 15;
unknowns = muscles + pat_tendon_force + ligaments + joint_contacts;
n = 3;

% Input data

for i = 1:segments
    for j = 1:3
     myfilename = sprintf('muscle_force_seg%d%d.txt',i-1, j-1);
     muscle_force{i,j} = importdata(myfilename);
     myfilename = sprintf('muscle_moment_seg%d%d.txt',i-1, j-1);
     muscle_moment{i,j} = importdata(myfilename);
     myfilename = sprintf('ligament_force_seg%d%d.txt',i-1, j-1);
     ligament_force{i,j} = importdata(myfilename);
     myfilename = sprintf('ligament_moment_seg%d%d.txt',i-1, j-1);
     ligament_moment{i,j} = importdata(myfilename);
    end
end
for i = 1:3
    myfilename = sprintf('muscle_force_seg4%d.txt',i-1);
    muscle_force{4,i} = importdata(myfilename);
end

pat_tendon_time = importdata('pat_tendon.txt');
joint_contact_time = importdata('joint_contacts.txt');
ratios_time = importdata('ratios.txt');
rhs_time = importdata('rhs.txt');
force_ub_time = importdata('force_ub.txt');
ligament_ub_time = importdata('ligament_ub.txt');

% Specify optimization parameters

x0(unknowns) = 0;
A = [];
b = [];
lb(unknowns) = 0;
coeff2(unknowns) = 0;

nonlcon=[];
options = optimset('MaxFunEvals',1000000000,'MaxIter',2000,'TolCon',1);     % Set optimization options

for i = 1:muscles
    coeff2(i)=1;
end
for i = 1:ligaments
    coeff2(muscles+pat_tendon_force+i)=1;
end

% Specify parts of equations of motion that are invariant by frame

joint_equations = zeros(joint_contacts-3,joint_contacts);
for i = 1:6
    joint_equations(i,i) = -1;
    joint_equations(i+6,i+9) = -1;
    joint_equations(i+3,i) = 1;
end
for i = 1:3
    joint_equations(i+3,i+6) = -1;
    joint_equations(i+6,i+6) = 1;
    joint_equations(i+6,i+12) = 1;
end

for i = 1:joint_contacts-3
    for j = 1:joint_contacts
        equations_of_motion(i,j+muscles+pat_tendon_force+ligaments)=joint_equations(i,j);
    end
end
for i = 1:3
    force_ub(i+muscles+pat_tendon_force+ligaments) = 20000;
    lb(i+muscles+pat_tendon_force+ligaments) = -20000;
end
for i = 4:9
    force_ub(i+muscles+pat_tendon_force+ligaments) = 10000;
    lb(i+muscles+pat_tendon_force+ligaments) = -10000;
end
for i = 10:15
    force_ub(i+muscles+pat_tendon_force+ligaments) = 20000;
    lb(i+muscles+pat_tendon_force+ligaments) = -20000;
end



equations_of_motion(6*segments+3+1,muscles+pat_tendon_force) = -1;
force_ub(muscles+pat_tendon_force) = 20000;

for i = 1:3
    rhs(9+i) = 0;
end
rhs(6*segments+3+1) = 0;


% Loop through all frames

for i = start:finish
  
    i
    
   % Construct equations of motion for the given frame 
    
   for j = 1:segments
       for k = 1:3
           for l = 1:muscles
               equations_of_motion (3*(j-1)+k,l) = muscle_force{j,k} (i,l);
               equations_of_motion (((segments+1)*3)+3*(j-1)+k,l) = muscle_moment{j,k} (i,l);
           end
           for l = 1:ligaments
               equations_of_motion (3*(j-1)+k,l+muscles+pat_tendon_force) = ligament_force{j,k} (i,l);
               equations_of_motion (((segments+1)*3)+3*(j-1)+k,l+muscles+pat_tendon_force) = ligament_moment{j,k} (i,l);
           end
   
       end
   end
   for j = 1:3
       for k = 1:muscles
           equations_of_motion (9+j,k) = muscle_force{4,j} (i,k);
       end
   end
   for j = 1:3
       equations_of_motion(j+3,muscles+pat_tendon_force) = pat_tendon_time(i,j);
       equations_of_motion(j+9,muscles+pat_tendon_force) = pat_tendon_time(i,j+3);
       equations_of_motion(j+15,muscles+pat_tendon_force) = pat_tendon_time(i,j+6);
   end
   for j = 1:3
       f(j) = joint_contact_time(i,j);
       d2(j) = joint_contact_time(i,j+3);
       g21(j) = -joint_contact_time(i,j+6);
       g22(j) = -joint_contact_time(i,j+9);       
       d31(j) = joint_contact_time(i,j+12);
       d32(j) = joint_contact_time(i,j+15);       
   end
   fmat = make_skew_sym_matrix_gui(f);
   d2mat = make_skew_sym_matrix_gui(d2);
   g21mat = make_skew_sym_matrix_gui(g21);
   g22mat = make_skew_sym_matrix_gui(g22);
   d31mat = make_skew_sym_matrix_gui(d31);
   d32mat = make_skew_sym_matrix_gui(d32);
   for j = 1:3
       for k = 1:3
           equations_of_motion(18+j,190+k) = fmat(j,k);
           equations_of_motion(15+j,178+k) = d2mat(j,k);
           equations_of_motion(15+j,181+k) = g21mat(j,k);
           equations_of_motion(15+j,184+k) = g22mat(j,k);
           equations_of_motion(18+j,181+k) = d31mat(j,k);
           equations_of_motion(18+j,184+k) = d32mat(j,k);
       end
   end

   for j = 1:muscles
       equations_of_motion(6*segments+3+1,j) = ratios_time(i,j);
       force_ub(j) = force_ub_time(i,j);
   end
   for j = 1:ligaments
       force_ub(j+muscles+pat_tendon_force) = ligament_ub_time(i,j);
   end
   for j = 1:(3*segments)
       rhs(j) = rhs_time(i,j);
       rhs(3*(segments+1)+j) = rhs_time(i,3*segments+j);
   end
    
  

   
   
   % Specify cost function

   coeff1 = 1./force_ub;   
   fun = @(x) sum(coeff2.*((x.*coeff1).^n));

    
   % Perform optimization

   [x,fval,exitflag,output] = fmincon(fun,x0,A,b,equations_of_motion,rhs,lb,force_ub,nonlcon,options);


    
    
    
    
    
    
    
    
% Use solution (if it exists) as starting point for next frame    
    
 if exitflag == 5 | exitflag == 1
     x0=x;                
 else
     x0(muscles+pat_tendon_force+ligaments+joint_contacts)=0;
 end

 
exitflag


% Save results

solve(i) = exitflag;
force(i,:) = x;

    
    
end

save 'force.txt' force -ASCII;
sol=solve';
save 'solve.txt' sol -ASCII;

cd(workingfolder);
cd('./Files/Outputs');

save 'all_forces.txt' force -ASCII;
save 'optimization_results.txt' sol -ASCII;
