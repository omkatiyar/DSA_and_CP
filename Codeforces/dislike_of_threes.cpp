#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int>a;
    
    for(int i=0;i<10000;i++){
        if(i%3!=0 && i%10!=3){
            a.push_back(i);
        }
    }
    int t;cin>>t;
    while(t--){
        int k;cin>>k;
        cout<<a[k-1]<<endl;
    }
}

// b jhhgh kkuyu gy dteewqe uyuyu po oljkkk  
// j hkj kjl ;; l;; ; ;hgf h;// jnu hbh j kj ug h k,l joljkj h j ll lkl;' hgfhffh h jjk
// nk k kj k';l jkh hfgfgd jhk jl ./ ,j kj/
// 