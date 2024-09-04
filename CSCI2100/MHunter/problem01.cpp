#include <bits/stdc++.h>
using namespace std;
#define __DEBUG__ true

const double STEP_LEN=200;
const double CENTRE_DEPTH=100;
double SLOPE_ANGLE_DEG=1.5;
const double OPEN_ANGLE_DEG=120;

double to_rad(double deg){
    return deg*acos(-1)/180;
}

double step_depth(int line_k){
    return CENTRE_DEPTH-line_k*STEP_LEN*tan(to_rad(SLOPE_ANGLE_DEG));
}

double getLeftXBound(int line_k){
    double h_prime=step_depth(line_k);
    return step_depth(line_k)/(tan(to_rad(SLOPE_ANGLE_DEG))-tan(to_rad(90-(0.5*OPEN_ANGLE_DEG))));
}

double getRightXBound(int line_k){
    double h_prime=step_depth(line_k);
    return step_depth(line_k)/(tan(to_rad(SLOPE_ANGLE_DEG))+tan(to_rad(90-(0.5*OPEN_ANGLE_DEG))));
}

double getDetectionWidth(int line_k){
    return getRightXBound(line_k)-getLeftXBound(line_k);
}

double getOverlappingRateWithPrevious(int line_k){
    double rb_prev=getRightXBound(line_k-1)-STEP_LEN;
    double lb_cur=getLeftXBound(line_k);
    return (rb_prev-lb_cur)/(getDetectionWidth(line_k));
}


void debug(){
    for(int i=-10;i<=10;++i){
        SLOPE_ANGLE_DEG=i;
        printf("[SLOPE-DEG]%1.3lf\t[DET-WIDTH]%.9lf\n", SLOPE_ANGLE_DEG, getDetectionWidth(0));
    }
    exit(0);
}


int main(){
    if(__DEBUG__){
        debug();
        exit(0);
    }
    double line_k_arr[9], step_depth_arr[9], scan_width_arr[9], overlap_rate_arr[9];
    for(int i=0;i<9;++i){
        line_k_arr[i]=i-4;
        step_depth_arr[i]=step_depth(i-4);
        scan_width_arr[i]=getDetectionWidth(i-4);
        overlap_rate_arr[i]=getOverlappingRateWithPrevious(i-4);
    }

    FILE* mdf=fopen("Problem01_data.md", "w+");

    fprintf(mdf, "# Problem 01 Data Table\n\n");
    fprintf(mdf, "| Test Point | Distance to Centre | Water Depth | Detection Width | Overlapping Rate |\n");
    fprintf(mdf, "|---|---|---|---|---|\n");
    for(int i=0;i<9;++i){
        fprintf(mdf, "| $%d$ | $%.9lf$ | $%.9lf$ | $%.9lf$ | $%.9lf$ |\n", i, line_k_arr[i]*STEP_LEN, step_depth_arr[i], scan_width_arr[i], overlap_rate_arr[i]);
    }

    fclose(mdf);
    exit(0);
}