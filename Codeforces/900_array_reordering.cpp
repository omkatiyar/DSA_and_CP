#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
    int n;cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++)
    cin>>a[i];

    sort(a.begin(),a.end(),greater<int>());
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
        int g = __gcd(a[i],2*a[j]);
        if(g>1)
        ans++;
        }
    }
    cout<<ans<<endl;
    }
}