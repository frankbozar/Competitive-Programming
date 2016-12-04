#include <bits/stdc++.h>
using namespace std;

long long constexpr inf=(1ll<<50ll);
int constexpr max_edges=100000;

struct Edge{
  int to;
  long long cap;
};

struct Graph{
  vector<vector<Edge*>> edges;
  Edge edge_storage[max_edges];
  size_t edges_stored=0;

  Graph(int n){
    edges.resize(n);
  }

  size_t nodes()const{
    return edges.size();
  }

  Edge *opp(Edge const *s){
    return edge_storage+((s-edge_storage)^1);
  }

  void add_edge(int x,int y,long long c){
    assert(edges_stored+2<=max_edges);
    assert(c>=0);
    edges[x].push_back(&(edge_storage[edges_stored++]={y,c}));
    edges[y].push_back(&(edge_storage[edges_stored++]={x,0}));
  }

  vector<int> dist;

  bool bfs(int src,int sink){
    dist=vector<int>(nodes(),-1); dist[src]=0;
    queue<int> todo; todo.push(src);
    while (not todo.empty()){
      int x=todo.front(); todo.pop();
      for (auto const &y: edges[x])
        if (y->cap and !~dist[y->to]){
          dist[y->to]=dist[x]+1; if (y->to==sink) return true;
          todo.push(y->to);
        }
    }
    return false;
  }

  int dfs(int src,int sink,long long limit=inf){
    if (limit==0 or src==sink) return limit;
    int res=0;
    for (auto const &y: edges[src]){
      if (y->cap and dist[y->to]==dist[src]+1){
        long long got=dfs(y->to,sink,min(y->cap,limit));
        if (not got) dist[y->to]=-1; else{
          limit-=got;
          res+=got;
          y->cap-=got;
          opp(y)->cap+=got;
        }
      }
    }
    return res;
  }
};

int main(){
  int windows,queues,instruments; cin>>windows>>queues>>instruments;
  vector<int> target(instruments); for (auto &i: target) cin>>i, --i;
  vector<long long> capacity(queues); for (auto &i: capacity) cin>>i;

  auto const src=0;
  auto const sink=1;
  auto const lab=[queues](int x,int y){return 2+(queues+1)*x+y;};

  Graph g(lab(windows,0));
  long long total_data=0;

  for (int i=0; i<windows; i++){
    // Egressed data (collector => sink)
    long long downlink; cin>>downlink;
    g.add_edge(lab(i,queues),sink,downlink);

    long long tadded=0;

    // Total up additions to each queue from instruments
    vector<long long> added(queues);
    for (int j=0; j<instruments; j++){
      long long data; cin>>data;
      added[target[j]]+=data;
      total_data+=data;
      tadded+=data;
    }

    for (int j=0; j<queues; j++){
      if (added[j]>capacity[j]){
        cout<<"impossible"<<endl;
        return 0;
      }

      // Egressed data (queue => collector)
      g.add_edge(lab(i,j),lab(i,queues),capacity[j]);

      // Incoming data during this window
      g.add_edge(src,lab(i,j),added[j]);

      // Incoming data from previous window
      if (i and added[j]<capacity[j]){
        g.add_edge(lab(i-1,j),lab(i,j),capacity[j]-added[j]);
      }
    }
  }

  // Make sure we finished reading from input
  {string x; assert(not (cin>>x));}

  long long res=0;
  while (g.bfs(src,sink)) res+=g.dfs(src,sink);
  cerr<<res<<" / "<<total_data<<endl;
  cout<<(res==total_data?"possible":"impossible")<<endl;
}
