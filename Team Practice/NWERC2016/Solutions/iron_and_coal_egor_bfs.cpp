//c++ port of egor.py
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int MAX=1<<25;
void bfs(const vector<vi> &graph,const vi &start, vi &dists){
  std::fill(dists.begin(), dists.end(), MAX);
  
  queue<int> q;
  for(auto s: start){
      q.push(s);
      dists[s]=0;
  }
  
  while(! q.empty()){
    int cur=q.front();
    for(auto next: graph[cur])
        if(dists[next]==MAX){
           dists[next]=dists[cur]+1;
           q.push(next);
        }
    q.pop();
  }
  
}

vi read_vector(int s){
    vi res(s);
    for(auto &e : res){
        cin >> e; e--;
    }
    return res;
}


int main(){
    ios_base::sync_with_stdio(false);  
      
    int n,m,k;
    cin >> n >> m >>k;
    vi ores=read_vector(m);
    vi coals=read_vector(k);
    
    vector<vi> graph(n);
    vector<vi> rev_graph(n);
    
    for(int i=0;i<n;i++){
       int a;
       cin >> a;
       graph[i]=read_vector(a);
       for (int j=0;j<a;j++)
         rev_graph[graph[i][j]].push_back(i);
    }
    
    vi dist_root(n);
    vi dist_ore(n);
    vi dist_coal(n);
    
    bfs(graph,{0}, dist_root);
    bfs(rev_graph, ores, dist_ore);
    bfs(rev_graph, coals, dist_coal);
    
    int best=MAX;
    for(int i=0;i<n;i++)
      best=std::min(best, dist_root[i]+dist_ore[i]+dist_coal[i]);
      
    if (best>=MAX)
            cout<<"impossible\n";
    else
        cout<<best<<"\n";
}



