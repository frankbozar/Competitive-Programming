#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;
const int H=20;

lld dfs(const vector<vector<int>>& e, vector<lld>& c, int u=1)
{
    for(int v : e[u])
        c[u]+=dfs(e, c, v)+1;
    
    return c[u];
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<lld> a(n+1, 0), l(n+1, 0), c(n+1, 0);
    vector<vector<int>> e(n+1), p(H, vector<int>(n+1, 0));
    l[0]=-INF;
    queue<int> Q;
    
    for(int i=1; i<=n; i++)
        scanf("%lld", &a[i]);
    
    for(int i=2; i<=n; i++)
    {
        scanf("%d%lld", &p[0][i], &l[i]);
        e[ p[0][i] ].push_back(i);
    }
    
    for(Q.push(1); !Q.empty(); Q.pop())
    {
        int u=Q.front();
        
        for(int v : e[u])
        {
            l[v]+=l[u];
            Q.push(v);
        }
    }
    
    for(int i=1; i<H; i++)
        for(int j=1; j<=n; j++)
            p[i][j]=p[i-1][ p[i-1][j] ];
    
    for(int i=1; i<=n; i++)
    {
        int u=i;
        
        for(int j=H-1; j>=0; j--)
            if( l[ p[j][u] ]>=l[i]-a[i] )
                u=p[j][u];
        
        c[ p[0][u] ]--;
    }
    
    dfs(e, c);
    
    for(int i=1; i<=n; i++)
        printf(i==n ? "%lld\n" : "%lld ", c[i]);
}

//p[v]>=p[u]-a[u]
