#include <vector>
#include <array>
#include <algorithm>

using point2d = std::array<double, 2>;

std::pair<double, double> calculateMinMax(std::vector<point2d> front_curve) {
    // Find the minimum x value in front_curve
    auto min_x_it = std::min_element(front_curve.begin(), front_curve.end(),
        [](const point2d& a, const point2d& b) { return a[0] < b[0]; });
    double min_x = min_x_it->at(0);

    // Find the maximum x value in front_curve
    auto max_x_it = std::max_element(front_curve.begin(), front_curve.end(),
        [](const point2d& a, const point2d& b) { return a[0] > b[0]; });
    double max_x = max_x_it->at(0);
    
    return {min_x, max_x};
}
