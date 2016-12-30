#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int INF=1<<20;
#define edge pair<int,int>
#define u first
#define v second

struct set
{
    vector<int> p;
    set(int n) : p(n+1, -1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    void join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x!=y )
            p[x]=y;
    }
};

pair<int, int> bfs(const vector<vector<int>>& e, int u)
{
    vector<int> d(e.size(), INF);
    d[u]=1;
    queue<int> Q;
    
    for(Q.push(u); !Q.empty(); Q.pop())
    {
        u=Q.front();
        
        for(int v : e[u])
            if( d[v]>d[u]+1 )
            {
                d[v]=d[u]+1;
                Q.push(v);
            }
    }
    
    return {u, d[u]};
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    
    vector<edge> e(n-1);
    set S(n+1);
    
    for(edge& E : e)
    {
        scanf("%d%d", &E.u, &E.v);
        
        if( a[E.u]==a[E.v] )
            S.join(E.u, E.v);
    }
    
    vector<vector<int>> d(n+1);
    
    for(const edge& E : e)
    {
        d[S.find(E.u)].push_back(S.find(E.v));
        d[S.find(E.v)].push_back(S.find(E.u));
    }
    
    int u=bfs(d, S.find(1)).first;
    printf("%d\n", bfs(d, u).second>>1);
}
