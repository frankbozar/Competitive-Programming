#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <map>
using namespace std;

map<int,int> bfs(vector<int> const s,vector<vector<int>> const &e){
  map<int,int> res;
  queue<int> todo;
  for (auto i: s) res[i]=0, todo.push(i);
  for (; not todo.empty(); todo.pop())
    for (auto i: e[todo.front()])
      if (not res.count(i))
        res[i]=res[todo.front()]+1,
        todo.push(i);
  return res;
}

int main(){
  int n,as,bs; cin>>n>>as>>bs;
  vector<vector<int>> edge(n),redge(n);
  vector<int> a(as),b(bs);
  for (auto &i: a){cin>>i; i--;}
  for (auto &i: b){cin>>i; i--;}
  int idx=0;
  for (auto &i: edge) {int m; cin>>m; i.resize(m); for (auto &j: i) cin>>j, j--, redge[j].push_back(idx); ++idx;}

  int res=(1<<30);
  map<int,int> u=bfs({0},edge),v=bfs(a,redge),w=bfs(b,redge);
  for (auto i: u)
    if (v.count(i.first) and w.count(i.first))
      res=min(res,i.second+v[i.first]+w[i.first]);
  if (res==(1<<30)) cout<<"impossible\n"; else cout<<res<<endl;
}
