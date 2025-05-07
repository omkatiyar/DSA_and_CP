#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        vector<int>a(n);
        for(int i=0;i<n;i++)
        cin>>a[i];
        sort(a.begin(),a.end());
        int m=a[0];
        int i=0; int count=0;
        while(a[i]==m && i<n){
            count++;
            i++;
        }
        cout<<n-count<<endl;
    }
}