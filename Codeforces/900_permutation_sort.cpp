
#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        vector<int>a(n);
        for(int i=0;i<n;i++)
        cin>>a[i];
        vector<int>v=a;
        int minIdx = min_element(a.begin(),a.end())-a.begin();
        int maxIdx = max_element(a.begin(),a.end())-a.begin();
        sort(v.begin(),v.end());
        if(v==a)
        cout<<0<<endl;
        else if(minIdx==n-1 && maxIdx==0)
        cout<<3<<endl;
        else if(minIdx==0 || maxIdx==n-1)
        cout<<1<<endl;
        else
        cout<<2<<endl;
    }
}