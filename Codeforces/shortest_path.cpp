#include <bits/stdc++.h>
using namespace std;

int main(){
 int t; cin>>t;
 while(t--){
    int x_a,y_a;
    cin>>x_a>>y_a;
    int x_b,y_b;
    cin>>x_b>>y_b;
    int x_f,y_f;
    cin>>x_f>>y_f;
    if(x_a==x_b && y_a>y_b)
        swap(y_a,y_b);
    if(y_a==y_b && x_b<x_a)
        swap(x_a,x_b);
    
    if(x_f==x_a && x_f==x_b&& y_f>y_a && y_f<y_b)
        cout<<abs(y_a-y_b)+2<<endl;
    else if(y_a==y_b && y_b==y_f && x_a<x_f && x_f<x_b)
        cout<<abs(x_a-x_b)+2<<endl;
    else {
        cout<<abs(x_a-x_b)+abs(y_a-y_b)<<endl;
    }
}
}

/*
2,4=*
7,3=d
3,4 = f
what we will do here
. . . . . . . . 
. . . . . . . .
. . . . . . . .
. * . . . . . .
. . . . . . . . 
. . . . . . . . 
. . . . d . . . 
vector<int>v,u;
*/