#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main(){
      // 10 = 2*3+1*4     
      // 11 = 2*4 + 1*3     
      // 13 = 2*4 + 1*5   
      // 15 = 2*5 + 1*5
    int t; cin>>t;
      while (t--){
        long long int n;cin>>n;
        if(n==1 || n==3){
        	cout<<ceil((double)n/(double)3)<<" "<<n/3<<endl;
        }
        else{
	        long c1,c2;
	        long x= n/3;
          if(n-(x+2*x)==0){
            c1=x;
            c2=x;
          }
          else if(n-(x+2*x)==1){
            c1=x+1;
            c2=x;
          }
          else{
            c1=x;
            c2=x+1;
          }
	      cout<<c1<<" "<<c2<<endl;
        }
    }
}
          
         
         
         