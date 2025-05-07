#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n; 
        cin>>n; 
        vector<int> a(2*n+1);
        for(int i=0;i<2*n;i++)
        cin>>a[i];
        int count=0;
        
        for(int i=0;i<2*n;i++){
            if(a[i]%2!=0)
            count++;
        }
        if(count==n)
        cout<<"YES"<<endl;
        else
        cout<<"NO"<<endl;
    }
}
