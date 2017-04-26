#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int H=20;
#define edge pair<int,lld>
#define v first
#define w second

void dfs(const vector<vector<edge>>& e, vector<vector<int>>& p, vector<lld>& d, int u=1)
{
    for(const edge& E : e[u])
    {
        if( E.v==p[0][u] )
            continue;
        
        p[0][E.v]=u;
        d[E.v]=d[u]+E.w;
        dfs(e, p, d, E.v);
    }
}

void dfs(const vector<vector<edge>>& e, const vector<vector<int>>& p, vector<int>& c, int u=1)
{
    for(const edge& E : e[u])
    {
        if( E.v==p[0][u] )
            continue;
        
        dfs(e, p, c, E.v);
        c[u]+=c[E.v];
    }
}

int main()
{
    freopen("car.in", "rb", stdin);
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        vector<lld> a(n+1, 0), d(n+1, 0);
        vector<vector<edge>> e(n+1);
        vector<vector<int>> p(H, vector<int>(n+1, 0));
        vector<int> c(n+1, 0);
        
        for(int i=1; i<=n; i++)
            scanf("%lld", &a[i]);
        
        for(int i=1; i<n; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            e[u].push_back(edge(v, w));
            e[v].push_back(edge(u, w));
        }
        
        dfs(e, p, d);
        
        for(int i=1; i<H; i++)
            for(int j=1; j<=n; j++)
                p[i][j]=p[i-1][ p[i-1][j] ];
        
        for(int i=1; i<=n; i++)
        {
            int u=i;
            
            for(int h=H-1; h>=0; h--)
            {
                int v=p[h][u];
                
                if( v==0 || d[i]-d[v]>a[i] )
                    continue;
                
                u=v;
            }
            
            c[i]++;
            c[ p[0][u] ]--;
        }
        
        dfs(e, p, c);
        
        for(int i=1; i<=n; i++)
            printf(i==n ? "%d\n" : "%d ", c[i]-1);
    }
}
