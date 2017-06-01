#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<50;

struct edge
{
    int v;
    lld w;
    edge(int _v=0, lld _w=0) : v(_v), w(_w){}
    
    bool operator<(const edge& E) const
    {
        return w>E.w;
    }
};

lld sol(const vector<vector<edge>>& e, const int n)
{
    vector<lld> d(n+1, INF);
    d[1]=0;
    priority_queue<edge> PQ;
    
    for(PQ.push(edge(1, d[1])); !PQ.empty(); )
    {
        int u=PQ.top().v;
        lld w=PQ.top().w;
        PQ.pop();
        
        if( d[u]<w )
            continue;
        
        for(const edge& E : e[u])
        {
            if( d[E.v]>d[u]+E.w )
            {
                d[E.v]=d[u]+E.w;
                PQ.push(edge(E.v, d[E.v]));
            }
        }
    }
    
    lld ans=0;
    
    for(int i=1; i<=n; i++)
    {
        if( d[i]>=INF )
            return -1;
        else
            ans+=d[i];
    }
    
    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<edge>> e(n+1), f(n+1);
    
    for(; m>0; m--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[u].push_back(edge(v, w));
        f[v].push_back(edge(u, w));
    }
    
    lld x=sol(e, n);
    lld y=sol(f, n);
    printf("%lld\n", x<0 || y<0 ? 0 : x+y);
}
