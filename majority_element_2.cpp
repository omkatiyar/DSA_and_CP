/*
task link : https://leetcode.com/problems/majority-element-ii/
*/

class Solution {
public:
    vector<int> majorityElement(vector<int>& a) {
        int n=a.size();
        int freq = n/3+1;
        sort(a.begin(),a.end());
        set<int>s;
        int c=1;
        for(int i=1;i<n;i++){
            
            if(a[i]==a[i-1]){
                c++;
            }
            else{
                c=1;
            }
            if(c>=freq)
            s.insert(a[i]);
        }
        vector<int>v;
        if(n<3){
            s.insert(a[0]);
            if(n==2)
                s.insert(a[1]);
        }
        for(auto it:s){
            v.push_back(it);
        }
        return v;
    }
};