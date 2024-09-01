#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

int countMonotonicPairs(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(51, 0));

    // Initialize the dp array for the first element in nums
    for (int j = 0; j <= nums[0]; ++j) {
        int k = nums[0] - j;
        dp[0][j] = 1;
    }

    // Fill dp table for the rest of the elements
    for (int i = 1; i < n; ++i) {
        std::vector<long long> prefixSum(51, 0);

        // Calculate prefix sums for the previous row in dp array
        prefixSum[0] = dp[i-1][0];
        for (int j = 1; j <= 50; ++j) {
            prefixSum[j] = (prefixSum[j-1] + dp[i-1][j]) % MOD;
        }

        for (int j = 0; j <= nums[i]; ++j) {
            int k = nums[i] - j;
            dp[i][j] = prefixSum[j];
        }
    }

    // Sum up all the valid pairs in the dp array for the last element
    long long result = 0;
    for (int j = 0; j <= 50; ++j) {
        result = (result + dp[n-1][j]) % MOD;
    }

    return result;
}
