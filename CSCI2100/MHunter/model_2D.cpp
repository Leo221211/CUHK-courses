/**
 * @file model_2D.cpp
 * @author CUHKJohnDoe@github.com
 * @brief This module calculates route-depth (Dk), detection width (Wk) and neighbour overlapping rate (eta_k) with given serial number
 *      k and certain water area presets.
 * @version 0.1
 * @date 2023-09-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <bits/stdc++.h>
using namespace std;

// Converts an angle in degree to radian.
#define rad(deg) (deg*acos(-1)/180)

// Cotangent
#define cot(alpha) tan((0.5*acos(-1))-alpha)

/**
 * @brief Calculate depth under a certain detection route on which the detector travels.
 * 
 * @param centre_depth Depth of the centre of the water area.
 * @param slope_angle_deg Slope of the sea bottom as orthogonal to the route's direction.
 * @param route_num Serial number of detection line k as mentioned in document.
 * @param route_dist The constant distance between adjacent routes, as orthogonal to the route's direction.
 * @return double 
 */
double route_depth(double centre_depth, double slope_angle_deg, double route_dist, int route_num){
    double slope_angle_rad=rad(slope_angle_deg);
    double slope_depth_var=route_dist*route_num*tan(slope_angle_rad);
    return centre_depth-slope_depth_var;
}

double detection_width(double centre_depth, double slope_angle_deg, double route_dist, int route_num, double detect_angle_deg){
    double cur_depth=route_depth(centre_depth, slope_angle_deg, route_dist, route_num);
    double cur_lb=cur_depth/((tan(rad(slope_angle_deg))-cot(0.5*detect_angle_deg)));
    double cur_rb=cur_depth/((tan(rad(slope_angle_deg))+cot(0.5*detect_angle_deg)));
    return cur_rb-cur_lb;
}

double overlapping_rate(double centre_depth, double slope_angle_deg, double route_dist, int route_num, double detect_angle_deg){
    double cur_depth=route_depth(centre_depth, slope_angle_deg, route_dist, route_num);
    double pre_depth=route_depth(centre_depth, slope_angle_deg, route_dist, route_num-1);
    double cur_lb=cur_depth/((tan(rad(slope_angle_deg))-cot(0.5*detect_angle_deg)));
    double pre_rb=cur_depth/((tan(rad(slope_angle_deg))+cot(0.5*detect_angle_deg))) - route_dist;
    
}


