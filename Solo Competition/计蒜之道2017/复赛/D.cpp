#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<50;
#define edge pair<lld,int>
#define w first
#define v second

lld solve(const vector<vector<edge>>& e, int s, int t)
{
    vector<lld> d(e.size(), INF);
    d[s]=0;
    priority_queue<edge> PQ;
    
    for(PQ.push(edge(0, s)); !PQ.empty(); )
    {
        int u=PQ.top().v;
        lld w=-PQ.top().w;
        PQ.pop();
        
        if( w>d[u] )
            continue;
        
        for(const edge& E : e[u])
        {
            if( d[E.v]>w+E.w )
            {
                d[E.v]=w+E.w;
                PQ.push(edge(-d[E.v], E.v));
            }
        }
    }
    
    return d[t]<INF ? d[t] : -1 ;
}

int main()
{
    int n, m, k;
    scanf("%d%d", &n, &m);
    vector<vector<edge>> e(n+m+m+1);
    
    for(int i=1; i<=m; i++)
    {
        for(scanf("%d", &k); k>0; k--)
        {
            int x;
            scanf("%d", &x);
            e[x].push_back(edge(0, n+m+i));
            e[n+i].push_back(edge(0, x));
        }
    }
    
    for(scanf("%d", &k); k>0; k--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[u].push_back(edge(w, v));
        e[v].push_back(edge(w, u));
    }
    
    for(scanf("%d", &k); k>0; k--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[n+u].push_back(edge(w, n+v));
        e[n+v].push_back(edge(w, n+u));
        e[n+m+u].push_back(edge(w, n+v));
        e[n+m+v].push_back(edge(w, n+u));
    }
    
    int s, t;
    scanf("%d%d", &s, &t);
    printf("%lld\n", solve(e, s, t));
}

/*

5 4
2 5 1
2 2 4
1 3
2 3 4
2
1 2 9
1 5 18
2
1 2 6
1 3 10
1 5

*/
