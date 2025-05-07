#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n; cin>>n;
        double p = log2(n);
        // cout<<p<<endl;
        if(floor(p)==ceil(p))
        cout<<n-1<<endl;
        else{
            int ans = pow(2,floor(p));
            cout<<ans-1<<endl;
        }
    }
}