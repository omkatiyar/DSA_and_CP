#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long a[n];
        for (int i = 0; i < n; i++)
            cin >> a[i];
        sort(a, a + n);
        double ans = INT_MIN;
        long long sum = 0;
        for (int i = 0; i < n - 1; i++) {
            sum += a[i];
        }
        double sum1 = (double)sum / (double)(n - 1);
        ans = (double)a[n - 1] + sum1;

        cout << fixed << setprecision(6) << ans << endl;
    }
    return 0;
}
