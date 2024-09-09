// ideal_completion.cpp

#include <iostream>
#include <vector>
#include <numeric>  // For std::gcd
#include <string>   // For std::to_string

using namespace std;

string calculateExpectedValue(int N, vector<int> S, vector<int> Pr) {
    double expectedScore = 0.0;
    vector<double>P;

    // converting probability from percentage to normal decimal
    for (auto p : Pr) {
        P.push_back((double)p/100.0);
    }

    // Loop over all consecutive pairs (S[i], S[i+1])
    for (int i = 0; i < N - 1; i++) {
        // Check if S[i] < S[i+1]
        if (S[i] < S[i + 1]) {
            // Add to expected score based on probability
            expectedScore += P[i] * P[i + 1];                     // Both go to array A
            expectedScore += (1 - P[i]) * (1 - P[i + 1]);         // Both go to array B
        }
    }
    // converting expected value to fraction
    int numerator = (expectedScore*10000); // converting from 4 decimal places doubele to normal int
    int denominator = 10000; // since we multiplied expected score by 10000, denominator becomes 10000
    int gcdd = gcd(numerator,denominator);
    numerator = numerator/gcdd;
    denominator = denominator/gcdd;

    string ans = to_string(numerator) + "/" + to_string(denominator);
    cout<<ans<<endl;

    // Return the fraction as a string "p/q"
    return ans;
}

// int main() {
//     int N = 4;
//     vector<int> S = {1, 2, 3, 6}; // This vector is not used in the current implementation
//     vector<int> P = {50, 50, 50, 70};

//     string result = calculateExpectedValue(N, S, P);
//     cout << "Expected value as a fraction: " << result << endl;

//     return 0;
// }

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
