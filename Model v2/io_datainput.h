Vec_DP io_datainput(string filename, int k);
Mat_DP io_datainput(string filename);
void io_datainput(string filename, int muscles, Muscle *m[]);
void io_datainput(Vec_DP &data, int index, string filename);
void io_datainput(Mat_DP &data, Vec_DP markers, int segments, int index, string filename);
void io_datainput(Mat_DP &data, int frames, int num, string filename);