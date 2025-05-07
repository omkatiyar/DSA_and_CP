// task; https://codeforces.com/problemset/problem/1549/B
#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
    int n; cin>>n;
    string ep; cin>>ep;
    string fp; cin>>fp;
    // cout<<" ep is "<<ep<<endl;
    // cout<<" fp is "<<fp<<endl;
    map<int,int>me;
    for(int i=0;i<n;i++){
        if(ep[i]=='1')
        me[i]=-1;
        else
        me[i]=0;
    }
    int count=0;
    for(int i=0;i<n;i++){
        // cout<<" i is "<<i<<endl;
        if(fp[i]=='1'){
            
            if((me[min(i+1,n-1)]==-1&& (i+1)!=n) || (me[max(i-1,0)]==-1 && (i-1)!=-1) || me[i]==0){
                if((me[min(i+1,n-1)]==-1&& (i+1)!=n) || (me[max(i-1,0)]==-1 && (i-1)!=-1))
                    {me[i]=1;count++;}
                else
                    count++;
            // cout<<"count is "<<count<<endl;
            }
        }
    }
    if(count>0)
    cout<<count<<endl;
    else
    cout<<0<<endl;
    }
}