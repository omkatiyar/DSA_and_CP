#include <algorithm>
#include <iostream>
using namespace std;
// INSERTION SORT
// We move the element to its correct position
int main(){
    int a[] = {14,9, 9, 15, 12, 6, 8, 13};
    int n = sizeof(a)/sizeof(a[0]);
    for(int i=0;i<n;i++){
        int j=i;
        cout<<" i is "<<i<<" and j is "<<j<<endl;
        while(j>0 && a[j-1]){
            cout<<"a[j] is "<<a[j]<<" and a[j-1 is] "<<a[j-1]<<endl;
            if(a[j-1]>a[j])
            swap(a[j-1],a[j]);
            j--;
        }
    }
    cout<<"sorted arr is "<<endl;
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
}