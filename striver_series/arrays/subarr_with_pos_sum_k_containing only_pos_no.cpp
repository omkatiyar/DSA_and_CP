#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;cin>>n; int k; cin>>k;
    int a[n];
    for(int i=0;i<n;i++)
    cin>>a[i];
    int s=0;
    map<int,int>mp; int len=-1;
    for(int i=0;i<n;i++){
        s=s+a[i];
        if(s==k)
        len=i+1;
        if(mp.find(s-k)!=mp.end()){
            len=max(len,i-mp[s-k]);
        }
        if(mp.find(s-k) == mp.end()){
            mp[s-k]=i;
        }
    }
    cout<<"len is "<<len<<endl;
}