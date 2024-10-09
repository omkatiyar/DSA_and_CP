#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to calculate mean
double calculate_mean(const vector<double>& data) {
    double sum = 0;
    for (double val : data) {
        sum += val;
    }
    return sum / data.size();
}

// Function to calculate standard deviation
double calculate_stddev(const vector<double>& data, double mean) {
    double sum = 0;
    for (double val : data) {
        sum += (val - mean) * (val - mean);
    }
    return sqrt(sum / data.size());
}

// Function to detect out-of-control signals
bool detect_out_of_control(const vector<double>& data) {
    double mean = calculate_mean(data);
    double stddev = calculate_stddev(data, mean);
    int dataSize = data.size();

    // Control limits for single value beyond control boundaries
    double upper_control_limit = mean + 3 * stddev;
    double lower_control_limit = mean - 3 * stddev;

    // Check Rule 1: Single value beyond control boundaries
    for (int i = 0; i < dataSize; ++i) {
        if (data[i] > upper_control_limit || data[i] < lower_control_limit) {
            return false;
        }
    }

    // Check Rule 2: Two out of three consecutive values more than 2 stddev away
    for (int i = 0; i <= dataSize - 3; ++i) {
        int count = 0;
        for (int j = i; j < i + 3; ++j) {
            if (data[j] > mean + 2 * stddev || data[j] < mean - 2 * stddev) {
                count++;
            }
        }
        if (count >= 2) {
            return false;
        }
    }

    // Check Rule 3: Four out of five consecutive values more than 1 stddev away
    for (int i = 0; i <= dataSize - 5; ++i) {
        int count = 0;
        for (int j = i; j < i + 5; ++j) {
            if (data[j] > mean + 1 * stddev || data[j] < mean - 1 * stddev) {
                count++;
            }
        }
        if (count >= 4) {
            return false;
        }
    }

    // Check Rule 4: Sequence of eight consecutive values on one side of the mean
    for (int i = 0; i <= dataSize - 8; ++i) {
        bool all_above = true, all_below = true;
        for (int j = i; j < i + 8; ++j) {
            if (data[j] < mean) all_above = false;
            if (data[j] > mean) all_below = false;
        }
        if (all_above || all_below) {
            return false;
        }
    }

    // Check Rule 5: Patterns like 10 out of 11, 12 out of 14, 16 out of 20 values on one side of the mean
    vector<pair<int, int>> rule5_patterns = {{11, 10}, {14, 12}, {20, 16}};
    for (const auto& pattern : rule5_patterns) {
        int window_size = pattern.first;
        int required_on_one_side = pattern.second;

        for (int i = 0; i <= dataSize - window_size; ++i) {
            int count_above = 0, count_below = 0;
            for (int j = i; j < i + window_size; ++j) {
                if (data[j] > mean) count_above++;
                if (data[j] < mean) count_below++;
            }
            if (count_above >= required_on_one_side || count_below >= required_on_one_side) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    // Example dataset
    vector<double> data = {48, 49, 47, 52, 67, 53, 50, 48, 49, 51, 60, 58, 62, 61, 63, 65, 67};

    // Detect out-of-control signals in the data
    bool ans = detect_out_of_control(data);

    return 0;
}
