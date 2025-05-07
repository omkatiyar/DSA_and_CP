// task link : https://codeforces.com/problemset/problem/1624/A
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        int a[n];
        int mx=INT_MIN; int mn=INT_MAX;
        for(int i=0;i<n;i++){
            cin>>a[i];
            mx=max(mx,a[i]);
            mn=min(mn,a[i]);
        }
        if(n==1)
        cout<<0<<endl;
        else
        cout<<mx-mn<<endl;
    }
}