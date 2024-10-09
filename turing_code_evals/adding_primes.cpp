#include <iostream>
#include <vector>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;  // 0 and 1 are not prime numbers
    if (n <= 3) return true;   // 2 and 3 are prime numbers

    // If n is divisible by 2 or 3, it is not a prime number
    if (n % 2 == 0 || n % 3 == 0) return false;

    // Check for factors up to the square root of n
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}

long long sumOfPrimes(int n) {
   return 0;
}
int main(){
    
}
