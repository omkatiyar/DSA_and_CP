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
        while(j>0 && a[j-1]){
            if(a[j-1]>a[j])
            swap(a[j-1],a[j]);
            j--;
        }
    }
    cout<<"sorted arr is "<<endl;
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
}