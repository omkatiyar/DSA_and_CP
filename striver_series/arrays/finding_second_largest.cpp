#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++)
    cin>>v[i];
    int maxwa=v[0];int sec=INT_MIN;
    for(int i=0;i<n;i++){
        if(v[i]>maxwa){
            sec = maxwa;
            maxwa=v[i];
            
        }
        else if(v[i]<maxwa && v[i]>=sec)
        sec=v[i];
    }
    cout<<sec<<endl;
}