#include <iostream>
#include <vector>
#include <cmath>    // For std::sqrt

// Function to calculate the mean of a dataset
double calculateMean(const std::vector<double>& data) {
    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

// Function to calculate the standard deviation of a dataset
double calculateStdDev(const std::vector<double>& data, double mean) {
    double variance = 0.0;
    for (double value : data) {
        variance += (value - mean) * (value - mean);
    }
    return std::sqrt(variance / data.size());
}

// Function to detect out-of-control signals based on control limits and rules
bool detect_out_of_control(const std::vector<double>& data) {
    // Step 1: Calculate mean and standard deviation
    double mean = calculateMean(data);
    double stdDev = calculateStdDev(data, mean);

    // Step 2: Define control limits
    double UCL = mean + 3 * stdDev;  // Upper Control Limit
    double LCL = mean - 3 * stdDev;  // Lower Control Limit

    // Step 3: Detect out-of-control signals
    int n = data.size();

    // Rule 1: Single point outside control limits
    for (int i = 0; i < n; ++i) {
        if (data[i] > UCL || data[i] < LCL) {
            return false;
        }
    }

    // Rule 2: Two out of three successive points beyond 2σ on the same side
    for (int i = 2; i < n; ++i) {
        int countAbove2Sigma = 0, countBelow2Sigma = 0;
        if (data[i] > mean + 2 * stdDev) countAbove2Sigma++;
        if (data[i - 1] > mean + 2 * stdDev) countAbove2Sigma++;
        if (data[i - 2] > mean + 2 * stdDev) countAbove2Sigma++;

        if (data[i] < mean - 2 * stdDev) countBelow2Sigma++;
        if (data[i - 1] < mean - 2 * stdDev) countBelow2Sigma++;
        if (data[i - 2] < mean - 2 * stdDev) countBelow2Sigma++;

        if (countAbove2Sigma >= 2 || countBelow2Sigma >= 2) {
            return false;
        }
    }

    // Rule 3: Four out of five points beyond 1σ on the same side
    for (int i = 4; i < n; ++i) {
        int countAbove1Sigma = 0, countBelow1Sigma = 0;
        if (data[i] > mean + stdDev) countAbove1Sigma++;
        if (data[i - 1] > mean + stdDev) countAbove1Sigma++;
        if (data[i - 2] > mean + stdDev) countAbove1Sigma++;
        if (data[i - 3] > mean + stdDev) countAbove1Sigma++;
        if (data[i - 4] > mean + stdDev) countAbove1Sigma++;

        if (data[i] < mean - stdDev) countBelow1Sigma++;
        if (data[i - 1] < mean - stdDev) countBelow1Sigma++;
        if (data[i - 2] < mean - stdDev) countBelow1Sigma++;
        if (data[i - 3] < mean - stdDev) countBelow1Sigma++;
        if (data[i - 4] < mean - stdDev) countBelow1Sigma++;

        if (countAbove1Sigma >= 4 || countBelow1Sigma >= 4) {
            return false;
        }
    }

    // Rule 4: Run of 8 or more points on the same side of the centerline
    int runAbove = 0, runBelow = 0;
    for (int i = 0; i < n; ++i) {
        if (data[i] > mean) {
            runAbove++;
            runBelow = 0;
        } else if (data[i] < mean) {
            runBelow++;
            runAbove = 0;
        } else {
            runAbove = runBelow = 0;
        }

        if (runAbove >= 8 || runBelow >= 8) {
            return false;
        }
    }

    return true;  // No out-of-control signals detected
}
