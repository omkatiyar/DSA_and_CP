#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; int m; 
    cin>>n>>m;
    int a[n];
    int b[m];
    int i=0,j=0;
    for(int k=0;k<n;k++)
    cin>>a[k];
    for(int k=0;k<m;k++)
    cin>>b[k];

    vector<int>v;
    while(i<n || j<m){
        if(a[i]<b[j]){
                v.push_back(a[i]);
                i++;
          
        }
        else if(a[i]==b[j]){
            v.push_back(a[i]);
            v.push_back(b[j]);
            i++;j++;
        }
        else{
            v.push_back(b[j]);
            j++;
        }
    }
    while(i<n)
    v.push_back(a[i++]);
    while(j<m)
    v.push_back(b[j++]);

    for(int k=0;k<(int)v.size();k++)
    cout<<v[k]<<" ";
}