#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> v(n);
        
        if (n % 2 == 0) {
            for (int i = 0; i < n; i += 2) {
                v[i] = i + 2;
                v[i + 1] = i + 1;
            }
        } else {
            v[0] = 3; v[1] = 1; v[2] = 2;
            for (int i = 3; i < n; i += 2) {
                v[i] = i + 2;
                if (i + 1 < n) v[i + 1] = i + 1;
            }
        }
        
        for (int i = 0; i < n; i++) {
            cout << v[i] << " ";
        }
        cout << endl;
    }
    return 0;
}