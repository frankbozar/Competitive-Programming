#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;
#define edge pair<int,int>
#define u first
#define v second

int main()
{
    int n;
    scanf("%d", &n);
    vector<vector<lld>> e(n, vector<lld>(n, INF));
    vector<edge> m;
    lld mw=INF;
    
    for(int i=0; i<n; i++)
    {
        
        for(int j=i+1; j<n; j++)
        {
            lld t;
            scanf("%lld", &t);
            e[j][i]=e[i][j]=t;
            
            if( mw>t )
            {
                mw=t;
                m.clear();
            }
            
            if( mw==t )
                m.push_back(edge(i, j));
        }
    }
    
    vector<lld> ans(n+1, INF), vis(n, 0);
    vector<int> pre(n, -1);
    
    for(const edge& E : m)
    {
        pre[E.u]=E.u;
        pre[E.v]=E.v;
        ans[E.u]=ans[E.v]=mw*(n-1);
    }
    
    for(int k=0; k<n; k++)
    {
        int u=n;
        
        for(int i=0; i<n; i++)
            if( ans[u]>ans[i] && ans[i]>=0 )
                u=i;
        
        for(int i=0; i<n; i++)
        {
            if( ans[i]>ans[u]+min(vis[u], e[u][i])+e[u][i]-mw-mw )
            {
                ans[i]=ans[u]+min(vis[u], e[u][i])+e[u][i]-mw-mw;
                vis[i]=min(vis[u], e[u][i]);
                pre[i]=u;
            }
            /*
            if( ans[i]>ans[ pre[u] ]+e[ pre[u] ][i]-mw )
            {
                ans[i]=ans[ pre[u] ]+e[ pre[u] ][i]-mw;
                
                pre[i]=pre[u];
            }
             */
        }
        
        ans[u]=-ans[u];
    }
    
    for(int i=0; i<n; i++, printf("\n"))
        for(int j=0; j<n; j++)
            printf("%21lld", e[i][j]);
    
    for(int i=0; i<n; i++)
        printf("%lld\n", -ans[i]);
}
