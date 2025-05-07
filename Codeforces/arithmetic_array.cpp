#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        int sum=0;
        //
        for(int i=0;i<n;i++){
            int x;
            cin>>x;sum+=x;
        }
        //
        if((double)sum/(double)n==1.0 && sum>0)
            cout<<0<<endl;
        else if(sum<n)
            cout<<1<<endl;
        else
            cout<<sum-n<<endl;
        
    }
}
