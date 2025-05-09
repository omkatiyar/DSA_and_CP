#include <bits/stdc++.h>
using namespace std;
// BUBBLE SORT
// We move the largest element at the end of the array by swapping it with the previous element if previous element > current element
int main(){
    int a[] = {13, 46, 24, 52, 20, 9};
    int n = sizeof(a)/sizeof(a[0]);
    int maxx = INT_MIN;
    int ind = -1;
    for(int i=n;i>0;i--){
        for(int j=0;j<i-1;j++){
            if(a[j]>a[j+1])
            swap(a[j],a[j+1]);
        }
    }
    for(int i=0;i<n;i++)
    cout<<a[i]<<" ";
}