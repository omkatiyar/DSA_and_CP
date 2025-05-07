#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int s; cin>>s;
        if(s<3)
         cout<<s<<endl;
        else{
            double x = sqrt(s);
            int y = sqrt(s);
            if(floor(x)!=ceil(x)){
                y = floor(x);
                y++;
            }
            cout<<y<<endl;
        }
    }
}
