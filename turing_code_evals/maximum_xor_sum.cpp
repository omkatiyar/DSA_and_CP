// ideal_completion.cpp

#include <iostream>
#include <vector>

using namespace std;

long long maximize_xor_sum(int n, vector<int>& arr) {
    long long max_xor_sum = 0;
    int best_x = 0;

    for (int bit = 31; bit >= 0; --bit) {
        // Set this bit in the potential x and calculate the new XOR sum
        int potential_x = best_x | (1 << bit);
        long long current_xor_sum = 0;

        for (int num : arr) {
            current_xor_sum += num ^ potential_x;
        }

        // If setting this bit gives a better XOR sum, update best_x and max_xor_sum
        if (current_xor_sum > max_xor_sum) {
            max_xor_sum = current_xor_sum;
            best_x = potential_x;
        }
    }

    return  max_xor_sum;
}
