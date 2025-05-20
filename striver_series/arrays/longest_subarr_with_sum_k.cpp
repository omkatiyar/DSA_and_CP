#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;cin>>n; int k; cin>>k;
    int a[n];
    for(int i=0;i<n;i++)
    cin>>a[i];

    int i=0, j=0;int sum=0;
    int len=-1;
    while(i<n && i>=j){
        cout<<"inside while loop"<<endl;
        sum+=a[i];
        if(sum>k){
            sum-=a[j];
            j++;
        }
        else if(sum<k){
            i++;
        }
        else
            len=max(len,i-j+1);
    }
    if(sum==k){
        len=max(len,i-j+1);
        i++;
    }
    cout<<"length is "<<len<<endl;
}