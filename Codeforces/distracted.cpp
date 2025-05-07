#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        string s;cin>>s;
        int count = 0;
        for(char  c='A';c<='Z';c++){
            int first=n;
            int last=-1;
            for(int i=0;i<n;i++){
                if(s[i]==c){
                first = min(first,i);
                last = max(last,i);
                }
            }
            for(int i=first;i<=last;i++){
                if(s[i]!=c)
                count++;
            }
        }
        if(count>=1)
            cout<<"NO"<<endl;
        else
            cout<<"YES"<<endl;
    }
}
