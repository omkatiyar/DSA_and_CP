#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
    int n; cin>>n;
    map <int,vector<int>> mp;
    for(int i=0;i<n;i++){
    int x; cin>>x;
    mp[x].push_back(i);
    }
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        if(it->second.size() == 1)
        cout << it->second[0]+1 << endl;
    }
}
}