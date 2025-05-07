#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
    int n; cin>>n;
    int ans=0;int count=0;

    if(n<10 || n==10){
        if(n==10)
        cout<<9<<endl;
    else
        cout<<n<<endl;
    }
    else{
        double x = log10(n)/log10(10);
        int ans = 9*(int)(x);
        int y=x+1;
        string repeatedString(y ,'0' + 1);
        int r = stoi(repeatedString);
        int prev=r;
       
        while(prev<=n){
            count++;
            string repeatedString(y , '0' + 1);
            prev=prev+ stoi(repeatedString);
        }
        cout<< ans+count<<endl;
    }
        
    }
}
// 3289---> 27+ 1+1+1
// 7561
/*
34 --> 9 + 1+ 1 + 1
44 --> 9+ 1+ 1+ 1+1
100 --> 9 + 1 + 1 + 1 + 1 + 1 + 1 + 1+ 1+ 1
1000 --> 9 + 9 + 9
454 ---> 9+9+ 1+ 1+1+1
694 ---> 9+9+ 6
*/