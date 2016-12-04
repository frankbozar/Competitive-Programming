#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
using namespace std;
constexpr int maxn=1000000;

vector<int> edge[maxn];
int name[maxn],root[maxn];

pair<int,int> dv[maxn*3]; int dvn;
vector<pair<int,int>> dist[maxn];
int score[maxn];

vector<int> todo;

void tarjan(int x){
  static bool active[maxn];
  static stack<int> tar;
  static int indices;

  root[x]=name[x]=(indices++);
  tar.push(x); active[x]=true;
  for (auto y: edge[x]){
    if (active[y]) root[x]=min(root[x],name[y]);
    else if (!~root[y]) tarjan(y), root[x]=min(root[x],root[y]);
  }
  if (root[x]==name[x]) while (active[x]){
    int y=tar.top(); tar.pop(); active[y]=false; todo.push_back(y);
    root[y]=root[x];
  }
}

void bruteforce(int s,int x=-1,int eaten=0){
  static bool seen[maxn];
  if (!~x) x=s;
  seen[x]=true;
  for (auto y: edge[x]) if (not seen[y]){
    dv[dvn++]={y,eaten+1};
    if (root[y]==root[x]){
      bruteforce(s,y,eaten+1);
    }
  }
  seen[x]=false;
}

int main(){
  ios::sync_with_stdio(false);

  int n,m; cin>>n>>m;
  for (int i=0; i<n; i++) name[i]=root[i]=-1;
  for (int i=0; i<m; i++){
    int a,b; cin>>a>>b; --a,--b;
    edge[a].push_back(b);
  }

  // SCC O(N)
  for (int i=0; i<n; i++)
    if (!~root[i])
      tarjan(i);

  // Arrange SCCs in forward dependency order
  reverse(todo.begin(),todo.end());

  // Build component -> component edges O(component * edges(component))
  for (int i=n; i--;){
    dvn=0;
    bruteforce(i);
    dist[i]=vector<pair<int,int>>(dv,dv+dvn);
  }

  // Find a longest path by repeatedly taking the shortest path so far and extending it.
  int res=0;
  for (int x: todo){
    for (auto y: dist[x]){
      int will=score[x]+y.second;
      res=max(res,will);
      if (root[x]!=root[y.first]) score[y.first]=max(score[y.first],will);
    }
  }
  cout<<res+1<<endl;
}
