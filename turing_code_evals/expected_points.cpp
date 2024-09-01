#include <iostream>
#include <vector>
#include <numeric>  // For std::gcd
#include <string>   // For std::to_string

using namespace std;

string calculateExpectedValue(int N, vector<int> S, vector<int> P) {
    int numerator = 0;
    int denominator = 1;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            numerator += P[i] * P[j];
        }
    }

    denominator = 10000;

    // Simplify the fraction numerator/denominator
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;

    // Return the fraction as a string "p/q"
    return to_string(numerator) + "/" + to_string(denominator);
}

int main() {
    int N = 3;
    vector<int> S = {1, 2, 3}; // This vector is not used in the current implementation
    vector<int> P = {50, 50, 50};

    string result = calculateExpectedValue(N, S, P);
    cout << "Expected value as a fraction: " << result << endl;

    return 0;
}

/*
// ideal_completion.cpp

#include <iostream>
#include <vector>

using namespace std;

int calculateExpectedValue(int N, vector<int> S, vector<int> P){
    double expected_value = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            double probA = (P[i] * P[j]) / 10000.0;
            expected_value += probA;
        }
    }

    return expected_value;
}


*/
