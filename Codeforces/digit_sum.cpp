#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
    int n;cin>>n;
    int r=n%10;
    if(n==9||n==19)
    cout<<1+n/10<<endl;
    else{
        if(r==9)
        cout<<n/10+1<<endl;
        else
        cout<<n/10<<endl;
    }
    }
}