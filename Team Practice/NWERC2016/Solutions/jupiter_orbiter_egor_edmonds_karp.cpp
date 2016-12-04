//This solutions uses reduction to max-flow:
// there are ca. 2*N*Q nodes and ca. N*(I+2*Q) edges
//
// Uses Edmonds-Karp to solve the maxflow, resulting in O(n*m^2)=O(N^3*(Q+I)^2)
//
// NB: MaxFlow <=D*N<=10^8, so int32 is ok...

#include <bits/stdc++.h>
using namespace std;

struct CapEdge{
    size_t target;
    size_t reverse_edge;
    int cap;
    CapEdge(size_t target, size_t reverse_edge, int cap):
        target(target), reverse_edge(reverse_edge), cap(cap){}
};
typedef std::vector<CapEdge> Neighbors;
typedef std::vector<Neighbors> Graph;

typedef std::pair<size_t, int> Pred;//first->index of the reverse_edge, second->bottleneck value, min capacity
typedef std::vector<Pred> Preds;

size_t MAX=2000000000;

//remember the way and the minimal capacitance on the way 
bool bfs(const Graph &graph, size_t start, size_t end, Preds &preds){

    std::fill(preds.begin(), preds.end(), std::make_pair(MAX, MAX));
    std::deque<size_t> q;
    
    preds[start]=std::make_pair(2*MAX, MAX); 
    q.push_back(start);
    while (!q.empty()){
        size_t &cur=q.front();
        for(const auto &edge : graph[cur]){ 
            if(edge.cap>0 && preds[edge.target].first==MAX){
                preds[edge.target]=std::make_pair(edge.reverse_edge, std::min(preds[cur].second, edge.cap));
                q.push_back(edge.target);
                if(edge.target==end)
                    return true;
            }
        }
        q.pop_front();
   }
   return false;
}

int add_flow(Graph &graph, size_t end, const Preds &preds){
    int diff=preds[end].second;
    while(true){
        if(preds[end].second==MAX)
            break;
        CapEdge &back_edge=graph[end][preds[end].first];
        size_t next=back_edge.target;
        CapEdge &edge=graph[next][back_edge.reverse_edge];
        edge.cap-=diff;
        back_edge.cap+=diff;
        end=next;
    }
    return diff;
 }
    
int edmonds_karp(Graph &graph, size_t start, size_t end){
    int flow=0;
    size_t n=graph.size();
    Preds preds(n);
   
    while(bfs(graph, start, end, preds)){     
        flow+=add_flow(graph, end, preds);
    }

    return flow;
}
 
void add_edge(Graph &graph, size_t from, size_t to, int cap){
    CapEdge edge(to, graph[to].size(), cap);
    CapEdge rev_edge(from, graph[from].size(), 0);
    graph[from].push_back(edge);
    graph[to].push_back(rev_edge);
}

typedef vector<size_t> vs;
vs read_line(size_t n){
    vs res(n);
    for(auto &e:res)
       cin >> e;
    return res;
}
int main(){
    size_t N,Q,I;
    cin >> N >> Q >> I;
    
    vs Qs=read_line(I);
    vs Cs=read_line(Q);
    
    
    
    Graph graph(2*N*Q+N+2);
    size_t cur_queue=0;
    size_t cur_bottleneck=2*N*Q; 
    size_t source=cur_bottleneck+N;
    size_t target=source+1;
    
    
    
    int sum=0;
    for(size_t step=0;step<N;step++){
        int D; cin>>D;
        //collect data
        for(size_t i=0;i<I;i++){
          int cap; cin >> cap; sum+=cap;
          size_t target_queue=Qs[i]-1;
          add_edge(graph, source, cur_queue+target_queue, cap);
        }
        //to downlink:
        for(size_t i=0;i<Q;i++)
          add_edge(graph, cur_queue+i, cur_queue+Q+i, Cs[i]);
        cur_queue+=Q;
        //downlink->bottleneck
        for(size_t i=0;i<Q;i++)
           add_edge(graph, cur_queue+i, cur_bottleneck, D);
        //do downlinking
        add_edge(graph, cur_bottleneck, target, D);
        if(step==N-1)
            break;
        //downlink->collecting data
        for(size_t i=0;i<Q;i++)
          add_edge(graph, cur_queue+i, cur_queue+Q+i, Cs[i]);
      
        cur_bottleneck+=1;
        cur_queue+=Q;        
    }
    /*
    for(size_t i=0;i<graph.size();i++){
       cout << i << ":";
       for(auto &c:graph[i])
         cout << c.target << "("<< c.cap <<");";
       cout <<"\n";
    }
    */
    if (sum==edmonds_karp(graph, source, target))
        cout << "possible\n";
    else
        cout << "impossible\n";
}


