#include <bits/stdc++.h>
using namespace std;

long long maximize_xor_sum(int n, vector<int>& arr) {
    long long maxSum = 0;
    for(int bit = 30; bit >= 0; bit--) {
        long long sum0 = 0, sum1 = 0;
        for(int i = 0; i < n; i++) {
            if(arr[i] & (1 << bit)) {
                sum0 += (1 << bit) - (arr[i] & ((1 << bit) - 1));
                sum1 += (arr[i] & ((1 << bit) - 1));
            } else {
                sum0 += (arr[i] & ((1 << bit) - 1));
                sum1 += (1 << bit) - (arr[i] & ((1 << bit) - 1));
            }
        }
        maxSum += max(sum0, sum1);
    }
    return maxSum;
}
