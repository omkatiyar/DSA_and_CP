#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        if(n/10 == 0)
        cout<<n<<endl;
        else{
            double lg = log(n)/log(10);
            // cout<<" log is "<<lg<<endl;
            int ru = ceil(lg); 
            // cout<<" ceil is "<<ru<<endl;
            int ans=9;
            string s="11";
            int count=0;
            for(int i=1;i<=ru;i++){
               
                int num = stoi(s);
                // cout<<"number is "<<num<<endl;
                for(int j=1;j<=9;j++){
                    // cout<<" nums*i is "<<num*i<<" "<<endl;
                    if(num*j<=n)
                    ans++;
                    else{
                    count++;break;
                    }
                }
                if(count==0)
                s=s+"1";
                else 
                break;
            }
            cout<<ans<<endl;
        }
    }
}