cd('./Files/Outputs/optimization')

load force.txt
load solve.txt
load rotations.txt

freq=200;

no_muscles=163;
no_ligaments=14;
no_joint_contacts=5;


for i = 3:(frames-2)
    
    time(i) = (i-1)/freq;

    adductors(i)=0;
    bi_hamstrings(i)=0;
    gastroc(i)=0;
    glutes(i)=0;
    rec_fem(i)=0;
    soleus(i)=0;
    vastus(i)=0;
    for j = 1:no_joint_contacts
            jrf(i,j)=0;
    end
    ratio(i)=0;
    for j = 1:3
        tf_force(i,j)=0;
    end
    pat_tendon(i)=0;
 
    
    if ((solve(i) == 5) || (solve(i) == 1))    
      
        for j = 1:25
            adductors(i)=adductors(i)+force(i,j)/bw;
        end
        bi_hamstrings(i)=force(i,26)/bw;
        for j = 121:122  
            bi_hamstrings(i)=bi_hamstrings(i)+force(i,26)/bw;
        end
        for j = 42:43
            gastroc(i)=gastroc(i)+force(i,j)/bw;
        end
        for j = 46:72
            glutes(i)=glutes(i)+force(i,j)/bw;
        end
        for j = 117:118
            rec_fem(i)=rec_fem(i)+force(i,j)/bw;
        end
        for j = 123:128
            soleus(i)=soleus(i)+force(i,j)/bw;
        end
        for j = 140:163
            vastus(i)=vastus(i)+force(i,j)/bw;
        end
        pat_tendon(i)=force(i,no_muscles+1)/bw;

        for j = 1:no_joint_contacts
            jrf(i,j)=0;
            for k = 1:3
                jrf(i,j)=jrf(i,j)+(force(i,no_muscles+1+no_ligaments+3*(j-1)+k))^2;
            end
            jrf(i,j)=sqrt(jrf(i,j))/bw;
        end

        if (pat_tendon(i)/(rec_fem(i)+vastus(i)))<2 && (pat_tendon(i)/(rec_fem(i)+vastus(i)))>0
            ratio(i)=pat_tendon(i)/(rec_fem(i)+vastus(i));
        end

        for j = 1:4
           q(j) = rotations(i,4+j);
        end
        for j = 1:3
            v0(j) = force(i,no_muscles+1+no_ligaments+3+j) + force(i,no_muscles+1+no_ligaments+6+j);
        end

        v1 = qrotate(v0,q);
 
        for j = 1:3
            tf_force(i,j) = v1(j);
        end
        

    
     end
    
end

peak_adductors=max(adductors);
peak_bi_hamstrings=max(bi_hamstrings);
peak_gastroc=max(gastroc);
peak_glutes=max(glutes);
peak_rec_fem=max(rec_fem);
peak_soleus=max(soleus);
peak_vastus=max(vastus);
peak_jrf=max(jrf);
peak_tf=max(tf_force);
low_tf=min(tf_force);


for i = 3:(frames-2)
    summary(i,1) = adductors(i);
    summary(i,2) = bi_hamstrings(i);
    summary(i,3) = gastroc(i);
    summary(i,4) = glutes(i);
    summary(i,5) = rec_fem(i);
    summary(i,6) = soleus(i);
    summary(i,7) = vastus(i);
    for j = 1:no_joint_contacts
       summary(i,7+j) = jrf(i,j);
    end
    summary(i,7+no_joint_contacts+1)=tf_force(i,1);
end

save 'summary.txt' summary -ASCII;

figure('OuterPosition',[700,50,650,700],'Name','Model Analysis',...
    'NumberTitle','off');
subplot(3,2,1);
plot(time,adductors,time,glutes);
title('Forces in hip musculature','FontWeight','bold');
ylabel('Force (x BW)');
xlabel('Time (s)');
leg1=legend('ADD','GL','Location','NorthWest');
set(leg1,'Box','off');
subplot(3,2,2);
plot(time,pat_tendon,time,rec_fem,time,vastus,time,bi_hamstrings);
title('Forces in knee musculature','FontWeight','bold');
ylabel('Force (x BW)');
xlabel('Time (s)');
leg2=legend('PT','RF','VAS','BIH','Location','NorthWest');
set(leg2,'Box','off');
subplot(3,2,3);
plot(time,gastroc,time,soleus);
title('Forces in ankle musculature','FontWeight','bold');
ylabel('Force (x BW)');
xlabel('Time (s)');
leg3=legend('GAS','SOL','Location','NorthWest');
set(leg3,'Box','off');
subplot(3,2,4);
plot(time,ratio);
title('P/Q ratio','FontWeight','bold');
ylabel('Ratio');
xlabel('Time (s)');
subplot(3,2,5);
plot(time,jrf(:,1),time,jrf(:,2),time,jrf(:,3),time,jrf(:,4),time,jrf(:,5));
title('Joint contact forces','FontWeight','bold');
ylabel('Force (x BW)');
xlabel('Time (s)');
leg4=legend('AF','Lat TFJ','Med TFJ','HF','PFJ','Location','NorthWest');
set(leg4,'Box','off');
subplot(3,2,6);
bar(peak_jrf)
title('Peak joint contact forces','FontWeight','bold');
ylabel('Force (x BW)');
xlabel('1=AF, 2=TFJ-Lat, 3=TFJ-Med, 4=HF, 5=PFJ');

cd(workingfolder);
cd('./Files/Outputs/');

saveas(gca,'model_analysis.pdf')
save 'forces_summary.txt' summary -ASCII;

