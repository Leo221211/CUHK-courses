#include <bits/stdc++.h>
using namespace std;

double dat[251][201];

void _read(std::string file_name){
    FILE* raw_data=fopen(file_name.c_str(), "r+");
    FILE* raw_data_clone=fopen("raw_data_clone.txt", "w+");
    for(int i=0;i<251;++i){
        for(int j=0;j<201;++j){
            fscanf(raw_data, "%lf", &dat[i][j]);
            fprintf(raw_data_clone, "%2.2lf\t",dat[i][j]);
        }   fprintf(raw_data_clone, "\n");
    }
    fclose(raw_data);
    fclose(raw_data_clone);
}

void _write(std::string file_name){
    FILE* pix_data=fopen(file_name.c_str(), "w+");
    fprintf(pix_data, "%d %d\n", 200, 250);
    for(int i=0;i<250;++i){
        for(int j=0;j<200;++j){
            int cur_pix=16-((int)( (dat[i][j]/200.0)*16.0 ));
            fprintf(pix_data, "%d ", cur_pix);
        }
        fprintf(pix_data, "\n");
    }
    fclose(pix_data);
}

void make(){
    _read("raw_data.txt");
    _write("gs_bitmap.txt");
}

// int main(){make();}