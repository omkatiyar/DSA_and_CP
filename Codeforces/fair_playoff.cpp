#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n=4;
        vector<int>a(n);
        for(int i=0;i<n;i++)
        cin>>a[i];
        int x = max(a[0],a[1]);
        int y = max(a[2],a[3]);
        sort(a.begin(),a.end());
        if((x==a[n-1]&&y==a[n-2])||(x==a[n-2]&&y==a[n-1]))
        cout<<"YES"<<endl;
        else
        cout<<"NO"<<endl;
    }
}
