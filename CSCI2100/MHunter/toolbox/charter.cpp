#include <bits/stdc++.h>
#include "preprocessor.cpp"

using namespace std;

void print_csv_chart(std::string file_name){
    FILE* csv=fopen(file_name.c_str(), "w+");
    fprintf(csv,"Xcoord,Ycoord,SquareX,SquareY,CubeX,CubeY,Depth\n");
    for(int i=0;i<251;++i){
        for(int j=0;j<201;++j){
            fprintf(csv, "%.2lf,%.2lf,%.4lf,%.4lf,%.7lf,%.7lf,%.5lf\n", 
                0.02*(double)i, 
                0.02*(double)j, 
                pow((0.02*(double)i),2), 
                pow((0.02*(double)j),2), 
                pow((0.02*(double)i),3),
                pow((0.02*(double)j),3),
                dat[i][j]
            );
        }
    }
}

int main(){
    _read("raw_data.txt");
    print_csv_chart("04alt.csv");
}