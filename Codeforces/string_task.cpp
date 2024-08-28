#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main(){
    string s="";
    cin>>s;
    
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    string ans="";

    int n=s.size();
    for(int i=n-1;i>=0;i--){
        if(s[i]=='a' || s[i]=='e' || s[i]=='i'|| s[i]=='o' || s[i]=='u' || s[i]=='y')
            continue;
        else{
            ans =ans+ s[i]+'.';
        }
    }
    reverse(ans.begin(),ans.end());

    cout<<ans<<endl;
}