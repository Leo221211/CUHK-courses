#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

double calConLen(int depth){
    // open corresponding file
    std::string file_name = "contour_map_"+to_string(depth)+".csv";
    FILE* depthCon=fopen(file_name.c_str(), "r+");

    // Store the first 2 values of each row
    std::vector<std::vector<double>> data; 

    while (fgets(line, sizeof(line), file) != nullptr) {
        std::string row(line);
        std::istringstream iss(row);
        std::vector<std::string> values;

        std::string value;
        for (int i = 0; i < 2; ++i) {
            if (std::getline(iss, value, ','))
                values.push_back(value);
        }

        // Do something with the first 2 values of the row
        for (const auto& val : values) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        data.push_back(values);
    }

}

// return the geometric distance of 2 points
double cal2PDis(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double calAlpha(){
    return 0;
}

int main(){
    calConLen(173);
    // std::cout << calConLen(173) << std::endl

    exit(0);
}
