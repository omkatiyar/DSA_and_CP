/*
task link:https://www.geeksforgeeks.org/problems/floor-in-a-sorted-array-1587115620/1?track=DSASP-Searching&amp%253BbatchId=154&utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=floor-in-a-sorted-array
*/

class Solution {
  public:
    // Function to find floor of x
    // n: size of vector
    // x: element whose floor is to find
    int findFloor(vector<long long> v, long long n, long long x) {

        long long l=0, r=n-1;
        long long ans=-1;
        while(l<=r){
         long long mid = (l+r)/2;
            if(v[mid]>x){
                r=mid-1;
            }
            else{
                l=mid+1;
                ans=mid;
            }
        }
        //cout<<v[l]<<endl;
        return ans;
    }
};