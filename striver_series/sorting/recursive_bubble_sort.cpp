#include <bits/stdc++.h>
using namespace std;

void rec_bS(vector<int>&v, int i, int n){
    if(i<=0)
    return;
    int maxx=INT_MIN;
    for(int j=0;j<i-1;j++){
        if(v[j]>v[i])
        swap(v[j],v[i]);
        
   }
   rec_bS(v,i-1,n);
}

int main(){
    vector<int>v={5,3,2,4,2,3,1};
    int n=v.size();
    rec_bS(v,n-1,n);
    for(auto i:v)
    cout<<i<<" ";
}