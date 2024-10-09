#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
using namespace std;

// Define point2d as an array of two doubles
using point2d = std::array<double, 2>;

pair<double,double> calculateMinMax(vector<point2d>front_curve){
     auto min_x_it = std::min_element(front_curve.begin(), front_curve.end(),
        [](const point2d& a, const point2d& b) { return a[0] < b[0]; });
    double min_x = min_x_it->at(0);

    // Find the maximum x value in front_curve
    auto max_x_it = std::max_element(front_curve.begin(), front_curve.end(),
        [](const point2d& a, const point2d& b) { return a[0] < b[0]; });

    double max_x = max_x_it->at(0);
    
    return {min_x,max_x};
}
int main() {
    std::vector<point2d> front_curve = {
        {3.0, 5.0},
        {1.0, 2.0},
        {4.0, 6.0},
        {0.5, 1.5}
    };
    pair<double,double>p = calculateMinMax(front_curve);
    cout<<p.first<<" "<<p.second<<endl;

    return 0;
}
