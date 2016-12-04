//c++ port of egor.py
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int MAX=1<<25;
void dij(const vector<vi> &graph,const vi &start, vi &dists){
  std::fill(dists.begin(), dists.end(), MAX);
  
  typedef std::pair<int, size_t> State;
  priority_queue<State, vector<State>, greater<State> > q;
  for(auto e:start){
    dists[e]=0;
    q.push(make_pair(dists[e],e));
   }
  while (!q.empty()){
       int cur_dist=q.top().first; size_t cur_id=q.top().second;
       q.pop();       
       if(cur_dist!=dists[cur_id])
            continue;        
       for(auto e:graph[cur_id]){
           int next_dist=cur_dist+1;
           if(next_dist<dists[e]){
               dists[e]=next_dist;
               q.push(make_pair(next_dist, e));
           }
       }
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
    
    dij(graph,{0}, dist_root);
    dij(rev_graph, ores, dist_ore);
    dij(rev_graph, coals, dist_coal);
    
    int best=MAX;
    for(int i=0;i<n;i++)
      best=std::min(best, dist_root[i]+dist_ore[i]+dist_coal[i]);
      
    if (best>=MAX)
            cout<<"impossible\n";
    else
        cout<<best<<"\n";
}



