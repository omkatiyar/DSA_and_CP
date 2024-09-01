#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Function to calculate modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to calculate the expected value of points
int calculateExpectedValue(int N, vector<int> S, vector<int> P) {
    long long numerator = 0;  // p in the problem statement
    long long denominator = 1;  // q in the problem statement

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Calculate the probability that S[i] < S[j] contributes to the score
            double prob = (P[i] / 100.0) * ((100 - P[j]) / 100.0) + 
                          ((100 - P[i]) / 100.0) * (P[j] / 100.0);
            
            if (S[i] < S[j]) {
                numerator += prob;
            } else if (S[i] > S[j]) {
                numerator += prob;
            }
        }
    }

    numerator = (numerator * 2) % MOD;
    denominator = modExp(N * (N - 1) / 2, MOD - 2, MOD);  // Modular inverse of denominator

    return (numerator * denominator) % MOD;
}
