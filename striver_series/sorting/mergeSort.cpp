#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& v,int low, int mid, int high){
    int left=low;
    int right =mid+1;
    vector<int>temp;
    while(left<=mid && right<=high){
        if(v[left]<v[right])
        temp.push_back(v[left++]);
        else
        temp.push_back(v[right++]);
    }
    while (left<=mid) temp.push_back(v[left++]);
    while (right<=high) temp.push_back(v[right++]);

    for(int i=low;i<=high;i++){
        v[i]=temp[i-low];
    }
}
void mergeSort(vector<int>& v,int low, int high){
    if(low>=high)return;
    int mid = (low+high)/2;
    mergeSort(v,low,mid);
    mergeSort(v,mid+1,high);
    merge(v,low,mid,high);
}

int main(){
    vector<int>v = {3,3,3,3, 7,8,9,7,4,8,2,2,0,0};
    mergeSort(v,0,v.size()-1);
    for(int i=0;i<v.size();i++)
    cout<<v[i]<<" ";
}