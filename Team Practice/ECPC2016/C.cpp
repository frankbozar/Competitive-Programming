#include<cmath>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;
#define point pair<double,double>
#define x first
#define y second

struct HK
{
    int n, m;
    vector<int> d, p;
    vector<vector<int>> e;
    HK(int _n, int _m) : n(_n), m(_m), e(n+m+1){}
    
    void add(int u, int v)
    {
        e[u].push_back(n+v);
        e[n+v].push_back(u);
    }
    
    bool bfs()
    {
        d.assign(n+m+1, INF);
        queue<int> Q;
        
        for(int i=1; i<=n; i++)
        {
            if( p[i]==0 )
            {
                d[i]=0;
                Q.push(i);
            }
        }
        
        for(; !Q.empty(); Q.pop())
        {
            int u=Q.front();
            
            if( d[u]>d[0] )
                break;
            
            for(int v : e[u])
            {
                if( d[ p[v] ]==INF )
                {
                    d[ p[v] ]=d[u]+1;
                    Q.push(p[v]);
                }
            }
        }
        
        return d[0]<INF;
    }
    
    bool dfs(int u)
    {
        if( u==0 )
            return true;
        
        for(int v : e[u])
        {
            if( d[ p[v] ]==d[u]+1 && dfs(p[v]) )
            {
                p[v]=u;
                p[u]=v;
                return true;
            }
        }
        
        d[u]=INF;
        return false;
    }
    
    int operator()()
    {
        int ans=0;
        p.assign(n+m+1, 0);
        
        while( bfs() )
            for(int i=1; i<=n; i++)
                if( p[i]==0 && dfs(i) )
                    ans++;
        
        return ans;
    }
};

double dist(const point& p, const point& q)
{
    double dx=p.x-q.x;
    double dy=p.y-q.y;
    return sqrt(dx*dx+dy*dy);
}

int main()
{
    freopen("wall.in", "rb", stdin);
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        HK hk(n, m+1);
        
        for(; k>0; k--)
        {
            point p;
            scanf("%lf%lf", &p.x, &p.y);
            int i=p.x, j=0;
            
            for(; j<m; j++)
                if( dist(p, point(n/2.0, j))<=n/2.0 )
                    break;
            
            hk.add(i+1, j+1);
        }
        
        printf("%d\n", hk());
    }
}
