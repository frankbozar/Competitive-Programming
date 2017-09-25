#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;
#define edge pair<lld,lld>
#define v first
#define w second

vector<lld> dijk(const vector<vector<edge>>& e, lld u)
{
    vector<lld> d(e.size(), INF);
    d[u]=0;
    priority_queue<edge> PQ;
    
    for(PQ.push(edge(0, u)); !PQ.empty(); )
    {
        lld u=PQ.top().w;
        lld w=-PQ.top().v;
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
    
    return d;
}

lld sol(const vector<vector<lld>>& e, const vector<lld>& p, int n, int s, int t, int vol)
{
    vector<vector<lld>> d(n, vector<lld>(n+1, INF));
    d[s][n]=0;
    priority_queue<pair<lld, edge>> PQ;
    
    for(PQ.push(pair<lld, edge>(0, edge(s, n))); !PQ.empty(); )
    {
        lld w=-PQ.top().first;
        lld u=PQ.top().second.first;
        lld q=PQ.top().second.second;
        PQ.pop();
        
        if( w>d[u][q] )
            continue;
        
        for(int v=0; v<n; v++)
        {
            if( e[u][v]>vol || u==v )
                continue;
            
            lld cur= q==n ? 0 : vol-e[q][u] ;
            lld cos=(vol-cur)*p[u];
            
            if( d[v][u]>w+cos )
            {
                d[v][u]=w+cos;
                PQ.push(pair<lld, edge>(-d[v][u], edge(v, u)));
            }
            
            if( e[u][v]<=cur )
                continue;
            
            cos=(e[u][v]-cur)*p[u];
            
            if( d[v][n]>w+cos )
            {
                d[v][n]=w+cos;
                PQ.push(pair<lld, edge>(-d[v][n], edge(v, n)));
            }
        }
    }
    
    lld ans=INF;
    
    for(int i=0; i<=n; i++)
        ans=min(ans, d[t][i]);
    
    return ans;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m, k, v;
        scanf("%d%d%d%d", &n, &m, &k, &v);
        vector<vector<edge>> e(n+1);
        
        for(; m>0; m--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            e[u].push_back(edge(v, w));
            e[v].push_back(edge(u, w));
        }
        
        vector<lld> p(n+1, INF);
        
        for(int i=0; i<k; i++)
        {
            int u, w;
            scanf("%d%d", &u, &w);
            p[u]=min(p[u], (lld)w);
        }
        
        int s, t;
        scanf("%d%d", &s, &t);
        p[t]=0;
        vector<int> g;
        
        for(int i=1; i<=n; i++)
            if( p[i]<INF )
                g.push_back(i);
        
        n=g.size();
        vector<vector<lld>> d(n, vector<lld>(n, INF));
        
        for(int i=0; i<n; i++)
        {
            vector<lld> dis=dijk(e, g[i]);
            
            for(int j=0; j<n; j++)
                d[i][j]=dis[ g[j] ];
        }
        
        vector<lld> q(n);
        
        for(int i=0; i<n; i++)
            q[i]=p[ g[i] ];
        
        s=lower_bound(g.begin(), g.end(), s)-g.begin();
        t=lower_bound(g.begin(), g.end(), t)-g.begin();
        printf("%lld\n", sol(d, q, n, s, t, v));
    }
}

/*

3

3 3 2 2000
1 3 800
1 2 500
2 3 500
1 70
2 40
1 3

5 5 3 1000
1 2 800
2 5 800
1 3 400
3 4 600
4 5 600
1 80
2 90
3 20
1 5

4 3 3 1000
1 2 200
2 3 600
3 4 300
1 40
2 70
3 90
2 4

*/
