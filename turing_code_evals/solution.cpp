
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

long long calculateSum(int x) {
    return (x ^ 1) + (x ^ 2) + (x ^ 3) + (x ^ 4) + (x ^ 5);
}

int main() {
    long long S = 10737418221;
    int x;
    cout<<"Inside the code block"<<endl;

    for (x = (1<<25); x < (1 << 30); ++x) {
        long long xor_val = calculateSum(x);
        cout<<"xor_val is "<<xor_val<<endl;
          // Iterate over a range of x values
        if (xor_val == S) {
            cout << "The value of x is: " << x << endl;
            break;
        }
    }

    return 0;
}
