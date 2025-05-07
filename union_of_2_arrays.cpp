#include <bits/stdc++.h>
using namespace std;

/*
task link : https://www.geeksforgeeks.org/problems/union-of-two-sorted-arrays-1587115621/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=union-of-two-sorted-arrays
*/

vector<int> findUnion(int a[], int b[], int n, int m){
        int i=0,j=0;
        vector<int>v;
        while(i<n && j<m){
            if(a[i]==b[j]){
                if(v.size()==0 || a[i]!=v[(int)v.size()-1])
                    v.push_back(a[i]);
                i++;j++;
            }
            else if(a[i]>b[j]){
                if(v.size()==0 || b[j]!=v[(int)v.size()-1])
                    v.push_back(b[j]);
                j++;
            }
            else{
                if(v.size()==0 || a[i]!=v[(int)v.size()-1])
                    v.push_back(a[i]);
                i++;
            }
        }
        
        for(;i<n;i++){
            if(v.size()==0 || a[i]!=v[(int)v.size()-1])
                v.push_back(a[i]);
        }
        for(;j<m;j++){
            if(v.size()==0 || b[j]!=v[(int)v.size()-1]) 
            v.push_back(b[j]);
        }
        return v;
}

int main(){
    return 0;
}

