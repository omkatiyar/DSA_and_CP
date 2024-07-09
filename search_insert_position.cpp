/*
task link: https://leetcode.com/problems/search-insert-position/
*/

class Solution {
public:
    int searchInsert(vector<int>& a, int x) {
        int l=0,r=a.size()-1;
        int ans=0;
        while(l<=r){
            int mid = (l+r)/2;
            if(a[mid]<x){
                l=mid+1;
            }
            else if(a[mid]==x){
                return mid;
            }
            else
                r=mid-1;
        }
        return l;
    }
};