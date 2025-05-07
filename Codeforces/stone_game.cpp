#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        vector <int> arr(n);
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
            auto min_it = min_element(arr.begin(), arr.end());
    auto max_it = max_element(arr.begin(), arr.end());

    int min_idx = min_it - arr.begin();
    int max_idx = max_it - arr.begin();

    // Ensure min_idx is the leftmost and max_idx is the rightmost
    if (min_idx > max_idx) {
        swap(min_idx, max_idx);
    }

    // Scenario 1: Remove both from the left
    int ops1 = max_idx + 1;

    // Scenario 2: Remove both from the right
    int ops2 = arr.size() - min_idx;

    // Scenario 3: Remove one from the left and one from the right
    int ops3 = (min_idx + 1) + (arr.size() - max_idx);

    cout<<min({ops1, ops2, ops3})<<endl;

    }
}
