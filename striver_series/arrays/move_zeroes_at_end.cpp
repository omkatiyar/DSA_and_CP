#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++)
    cin>>a[i];
    int index=0;
    for(int i=0;i<n;i++){
        if(a[i]!=0){
            swap(a[i],a[index]);
            index++;
        }
    }
    for(int i=0;i<n;i++)
    cout<<a[i]<<" ";
}