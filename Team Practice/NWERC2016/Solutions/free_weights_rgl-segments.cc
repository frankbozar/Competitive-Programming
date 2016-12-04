#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,res=0; cin>>n;
  for (int row=0; row<2; row++){
    vector<int> v(n); for (auto &i: v) cin>>i;
    set<int> active;
    for (int i=0; i<v.size(); i++){
      if (active.count(v[i])) active.erase(v[i]); else active.insert(v[i]);
      if (active.size()>=2) res=max(res,*++active.rbegin());
    }
    for (auto i: active) res=max(res,i);
  }
  cout<<res<<endl;
}
