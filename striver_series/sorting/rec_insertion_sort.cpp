#include <bits/stdc++.h>
using namespace std;

void rec_IS_pass(vector<int>&v, int j, int n){
    
    if(j<=0)
    return;
    if(v[j-1]>v[j])
    swap(v[j],v[j-1]);

    rec_IS_pass(v,j-1,n);
}
void rec_IS(vector<int>&v, int i,int n){
    if(i>=n)
    return;
    rec_IS_pass(v,i,n);
    rec_IS(v,i+1,n);
}

int main(){
    vector<int>v = {2, 3,2, 2};
    int n = v.size();
    rec_IS(v,0,n);
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
}