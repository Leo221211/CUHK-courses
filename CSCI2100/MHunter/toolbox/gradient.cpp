#include <bits/stdc++.h>

using namespace std;

#define coord_2d std::pair<double,double>

#define xc(coord) coord.first
#define yc(coord) coord.second
#define GRID 0.02

double field[251][201];

void _read(std::string file_name){
    FILE* raw_data=fopen(file_name.c_str(), "r+");
    FILE* raw_data_clone=fopen("raw_data_clone.txt", "w+");
    for(int i=0;i<251;++i){
        for(int j=0;j<201;++j){
            fscanf(raw_data, "%lf", &field[i][j]);
            fprintf(raw_data_clone, "%2.2lf\t",field[i][j]);
        }   fprintf(raw_data_clone, "\n");
    }
    fclose(raw_data);
    fclose(raw_data_clone);
}

class contour{
    std::vector<coord_2d> anchors;
};

/**
 * @brief Find anchors of the contour along east-west grid borders.
 * 
 * @param height 
 * @return std::vector<coord_2d> 
 */
std::vector<coord_2d> findAnchorsAlongEWGrids(double height){
    std::vector<coord_2d> anchors;  // Anchors are points, or coordinates at which the contour intersects with the field.
    for(int i=0;i<251;++i){ // For every line of vertices...
        double global_y=i*GRID;
        for(int j=0;j<200;++j){     // For each vertex in the line, see if it's on different sides of the contour than its next vertex.
            if( (field[i][j]<height && field[i][j+1]>height) || (field[i][j]>height && field[i][j+1]<height) ){
                bool inc_flag=field[i][j]<field[i][j+1]; // Whether the field's height is increasing along the grid-border.
                double _lvert=inc_flag?field[i][j]:field[i][j+1];        // Height of higher vertex.
                double _hvert=inc_flag?field[i][j+1]:field[i][j];        // Height of lower vertex.

                double local_x=GRID*(height-_lvert)/(_hvert-_lvert);    // Interpolate for the x-distance between the anchor and the lower vertex.

                double global_x=inc_flag?(GRID*j+local_x):(GRID*(j+1)-local_x);     // Obtain x coordinate of the anchor.
                
                anchors.push_back(make_pair(global_x, global_y));
            }
        }
    }
    return anchors;
}

std::vector<coord_2d> findAnchorsAlongNSGrids(double height){
    std::vector<coord_2d> anchors;  // Anchors are points, or coordinates at which the contour intersects with the field.
    for(int i=0;i<201;++i){ // For every column of vertices...
        double global_x=i*GRID;
        for(int j=0;j<250;++j){     // For each vertex in the line, see if it's on different sides of the contour than its next vertex.
            if( (field[j][i]<height && field[j][i+1]>height) || (field[j][i]>height && field[j][i+1]<height) ){
                bool inc_flag=field[j][i]<field[j][i+1]; // Whether the field's height is increasing along the grid-border.
                double _lvert=inc_flag?field[j][i]:field[j][i+1];        // Height of higher vertex.
                double _hvert=inc_flag?field[j][i+1]:field[j][i];        // Height of lower vertex.

                double local_y=GRID*(height-_lvert)/(_hvert-_lvert);    // Interpolate for the x-distance between the anchor and the lower vertex.

                double global_y=inc_flag?(GRID*j+local_y):(GRID*(j+1)-local_y);     // Obtain x coordinate of the anchor.
                
                anchors.push_back(make_pair(global_x, global_y));
            }
        }
    }
    return anchors;
}

int main(){
    
    
}