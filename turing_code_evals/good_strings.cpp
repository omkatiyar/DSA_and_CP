// solution.cpp
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

#define mod 1000000007

long long power(long long x, long long n) {
    if (n == 0) {
        return 1;
    }
    long long ans = power(x, n / 2);
    ans *= ans;
    ans %= mod;
    if (n % 2 == 1) {
        ans *= x;
        ans %= mod;
    }
    return ans;
}

int countGoodNumbers(long long n) {
    long long numberOfOddPlaces = n / 2;
    long long numberOfEvenPlaces = n / 2 + n % 2;
    return (power(5, numberOfEvenPlaces) * power(4, numberOfOddPlaces)) % mod;
}

int main(){
    cout<<countGoodNumbers(1)<<endl;
    cout<<countGoodNumbers(50)<<endl;
    cout<<countGoodNumbers(10000)<<endl;

    return 0;
}
/*
The code provided by the assistant has major issues:
- The DP approach used is completely wrong and has unnecessary logic for prime numbers.
- The code is very complex.
- The code fails for basic test cases when the input is 50,1000 and so on.

The assistant provided the wrong approach and code, which failed for most basic test cases. Further, the code is also complex and has unnecessary logic.

The assistant should have provided the correct approach and explained it well initially. Further, the assistant should have provided the correct code and then explained the code with the help of examples.
*/