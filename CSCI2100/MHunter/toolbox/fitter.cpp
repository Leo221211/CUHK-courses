#include "bits/stdc++.h"
using namespace std;

double getFittedDepth(double _x, double _y){
    return 51.173-14.709*_x-6.4*_y+3.2*_x*_x+6.4*_y*_y;
}

int main(){
    FILE* fit_data=fopen("fit_data.txt", "w+");
    for(int i=0;i<251;++i){
        for(int j=0;j<201;++j){
            fprintf(fit_data,"%.2lf ", getFittedDepth(0.02*(double)i, 0.02*(double)j));
        }
        fprintf(fit_data, "\n");
    }
    fclose(fit_data);
    exit(0);
}