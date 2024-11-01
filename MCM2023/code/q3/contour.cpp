#include <bits/stdc++.h>

using namespace std;

#define __DEBUG__ false

#define coord_2d std::pair<double,double>

#define xc(coord) coord.first
#define yc(coord) coord.second
#define GRID 0.02

#define manh_dist(coord_a, coord_b) ( abs(coord_a.first-coord_b.first) + abs(coord_a.second-coord_b.second) )

const double CONTOUR_DEPTH_BEGIN=21.005;    //21
const double CONTOUR_DEPTH_END=196.005; //196
const double CONTOUR_DEPTH_STEP=1.000;

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
            double global_x=j*GRID;
            if( (field[i][j]<=height && field[i][j+1]>height) || (field[i][j]>=height && field[i][j+1]<height) ){
                bool inc_flag=field[i][j]<field[i][j+1]; // Whether the field's height is increasing along the grid-border.
                double _lvert=inc_flag?field[i][j]:field[i][j+1];        // Height of higher vertex.
                double _hvert=inc_flag?field[i][j+1]:field[i][j];        // Height of lower vertex.

                double local_x=GRID*(height-_lvert)/(_hvert-_lvert);    // Interpolate for the x-distance between the anchor and the lower vertex.

                double real_x=global_x+(inc_flag?local_x:(GRID-local_x));     // Obtain x coordinate of the anchor.
                
                anchors.push_back(make_pair(real_x, global_y));
            }
        }
    }
    return anchors;
}

/**
 * @brief Find anchors of the contour along north-south grid borders.
 * 
 * @param height 
 * @return std::vector<coord_2d> 
 */
std::vector<coord_2d> findAnchorsAlongNSGrids(double height){
    std::vector<coord_2d> anchors;  // Anchors are points, or coordinates at which the contour intersects with the field.
    for(int i=0;i<201;++i){ // For every column of vertices...
        double global_x=i*GRID;
        for(int j=0;j<250;++j){     // For each vertex in the line, see if it's on different sides of the contour than its next vertex.
            double global_y=j*GRID;
            if( (field[j][i]<=height && field[j+1][i]>height) || (field[j][i]>=height && field[j+1][i]<height) ){
                bool inc_flag=field[j][i]<field[j+1][i]; // Whether the field's height is increasing along the grid-border.
                double _lvert=inc_flag?field[j][i]:field[j+1][i];        // Height of higher vertex.
                double _hvert=inc_flag?field[j+1][i]:field[j][i];        // Height of lower vertex.

                double local_y=GRID*(height-_lvert)/(_hvert-_lvert);    // Interpolate for the y-distance between the anchor and the lower vertex.

                double real_y=global_y+((inc_flag)?local_y:(GRID-local_y));     // Obtain y coordinate of the anchor.
                
                anchors.push_back(make_pair(global_x, real_y));
            }
        }
    }
    return anchors;
}

/**
 * @brief Print a list of coordinates at which the contour intersects with east-west grid borders on the console.
 * 
 */
void test_ew_grid_anchors(double depth){
    std::vector<coord_2d> ew_grid_anchors=findAnchorsAlongEWGrids(depth);
    for(int i=0;i<ew_grid_anchors.size();++i){
        printf("<%1.5lf,%1.5lf>\n", ew_grid_anchors.at(i).first, ew_grid_anchors.at(i).second);
    }
}

/**
 * @brief Print a list of coordinates at which the contour intersects with east-west grid borders on the console.
 * 
 */
void test_ns_grid_anchors(double depth){
    std::vector<coord_2d> ns_grid_anchors=findAnchorsAlongNSGrids(depth);
    for(int i=0;i<ns_grid_anchors.size();++i){
        printf("<%1.5lf,%1.5lf>\n", ns_grid_anchors.at(i).first, ns_grid_anchors.at(i).second);
    }
}

std::vector<coord_2d> get_contour(double depth, bool discontinue_contour){
// merge all anchors
    std::vector<coord_2d> anchors=findAnchorsAlongEWGrids(depth);   // Find all anchors along ew-grid-borders.

    std::vector<coord_2d> _ns_anchors_=findAnchorsAlongNSGrids(depth);
    anchors.insert(anchors.end(), _ns_anchors_.begin(), _ns_anchors_.end());    // Include all anchors along ns_grid_borders.

    int ancsiz=anchors.size();  // Number of anchors in total.

    bool *ancflags=new bool[ancsiz];    // Marks if each of the anchor is visited.
    for(int i=0;i<ancsiz;++i){
        ancflags[i]=false;
    }

// mark edge anchors
    std::vector<int> _extreme_inds;     // Marks all the anchors on the edge of the map.
    for(int i=0;i<ancsiz;++i){
        if(anchors.at(i).first==0.0 || anchors.at(i).second==0.0 || anchors.at(i).first==4.0 || anchors.at(i).second==5.0){
            _extreme_inds.push_back(i);
        }
    }
    printf("Extreme Points acquired:\n");
    for(int i=0;i<_extreme_inds.size();++i){
        printf("%d\t<%.5lf,%.5lf>\t\n", _extreme_inds.at(i), anchors.at(_extreme_inds.at(i)).first, anchors.at(_extreme_inds.at(i)).second);
    }   printf("\n");

// order anchors form edge
    int cur_anc=_extreme_inds.at(0);  // Start visiting anchors from the first extreme point.
    printf("Iterating from extreme point <%.5lf,%.5lf>\n", anchors.at(cur_anc).first, anchors.at(cur_anc).second);
    std::vector<coord_2d> contour;

    while(1){
        ancflags[cur_anc]=true;     // Mark the current anchor to be visited.
        contour.push_back(anchors.at(cur_anc));       // Add the current anchor to the route.

        bool forward_flag=false;    // Marks whether the forward anchor is found.
        double cur_min_manh_dist=2.0;   // Stores the minimum manhattan distance to the forward anchor found so far.

// find the closest anchor
        // Iterate through all anchors and search for the forward anchor that the contour progresses to.
        for(int i=0;i<ancsiz;++i){  // For each of the anchors in the list...
            if(manh_dist(anchors.at(i), anchors.at(cur_anc))<(2.0*GRID) && !ancflags[i]){  // If a first anchor within manhattan distance of 2 is found unvisited...
                if(manh_dist(anchors.at(i), anchors.at(cur_anc))< cur_min_manh_dist){  // If the minimum manhattan distance is updated...
                    cur_anc=i;  // Visit this anchor.
                    cur_min_manh_dist=manh_dist(anchors.at(i), anchors.at(cur_anc));
                    forward_flag=true;  // Mark that a forward anchor is found.
                }
            }
        }


        if(!forward_flag){  // If no forward anchor is found, check if there's any anchor at extremes yet to be visited.
            if(!discontinue_contour){break;}     // If the graph doesn't allow discontinuity, end the loop
            bool fill_flag=true;    // Check if all anchors are visited.
            int unfill_index=-1;    // Marks index of the first unvisited anchor.
            for(int i=0;i<_extreme_inds.size();++i){
                if(!ancflags[_extreme_inds.at(i)]){
                    fill_flag=false;
                    unfill_index=_extreme_inds.at(i);
                    break;
                }
            }

            if(!fill_flag){     // If any anchor is left unvisited...
                cur_anc=unfill_index;   // Jump to the first unfilled index and resume the trip.
                printf("Iterating from extreme point <%.5lf,%.5lf>\n", anchors.at(cur_anc).first, anchors.at(cur_anc).second);
                continue;
            }else{
                break;  // Break the loop if no anchor is left unvisited.
            }
        }  
    }

    delete [] ancflags;
    return contour;
}

void test_contour(double depth, bool discontinue_contour=false){
    std::vector<coord_2d> _contour_=get_contour(depth, true);

    for(int i=0;i<_contour_.size();++i){
        printf("<%1.5lf,%1.5lf>\n", _contour_.at(i).first, _contour_.at(i).second);
    }
}

void write_contour_to_file(std::vector<coord_2d> contour, std::string file_name){
    FILE* _file_=fopen(file_name.c_str(), "w+");
    fprintf(_file_,"XCOORD,YCOORD\n");
    for(int i=0;i<contour.size();++i){
        fprintf(_file_, "%.5lf,%.5lf\n", contour.at(i).first, contour.at(i).second);
    }
    fclose(_file_);
}

void debug(){
    _read("raw_data.txt");
    test_contour(70.005, true);
}

int main(){
    if(__DEBUG__){
        debug();
        exit(0);
    }
    _read("raw_data.txt");

    int csv_serial=0;
    for(double cur_depth=CONTOUR_DEPTH_BEGIN;cur_depth<CONTOUR_DEPTH_END;cur_depth+=CONTOUR_DEPTH_STEP){
        write_contour_to_file(get_contour(cur_depth, true), "contour_map_"+to_string(csv_serial)+".csv");
        csv_serial++;
    }
    


    exit(0);
}