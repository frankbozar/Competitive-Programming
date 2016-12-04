#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int solve_row(int n){
  map<int,int> arr;
  vector<pair<int,int>> ids;

  for (int i=0; i<n; i++){
    cin>>arr[i];
    ids.emplace_back(arr[i],i);
  }
  sort(ids.begin(),ids.end());

  int res=0;
  for (int i=n; (i-=2)>=-1;){
    if (i<0 or ids[i].first!=ids[i+1].first){
      return max(res,ids[i+1].first);
    }
    auto const s=arr.upper_bound(ids[i].second),
               t=arr.lower_bound(ids[i+1].second);
    for (auto it=s; it!=t; arr.erase(it++)){
      res=max(res,min(ids[i].first,it->second));
    }
  }
  return res;
}

int main(){
  ios::sync_with_stdio(0);

  int n; cin>>n;
  cout<<max(solve_row(n),solve_row(n))<<endl;
}
