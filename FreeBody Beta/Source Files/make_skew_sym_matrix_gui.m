function matrix = make_skew_sym_matrix_gui(vector)

matrix = zeros(3);

   matrix(1,2) = -vector(3);
   matrix(1,3) = vector(2);
   matrix(2,1) = vector(3);
   matrix(2,3) = -vector(1);
   matrix(3,1) = -vector(2);
   matrix(3,2) = vector(1);
   
end