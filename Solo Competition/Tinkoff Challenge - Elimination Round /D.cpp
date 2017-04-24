#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=0x3F3F3F3F;
const int N=128;
int a[N][N][N];
int e[N][N];

int solve(int u, int v, int k)
{
    int& ans=a[u][v][k];
    
    if( ans<0 )
    {
        ans=INF;
        
        if( k==1 )
            ans=0;
        else if( u<v )
        {
            for(int i=u; i<=v; i++)
            {
                ans=min(ans, e[u][i]+solve(i, u+1, k-1));
                ans=min(ans, e[u][i]+solve(i, v, k-1));
            }
        }
        else if( u>v )
        {
            for(int i=u; i>=v; i--)
            {
                ans=min(ans, e[u][i]+solve(i, u-1, k-1));
                ans=min(ans, e[u][i]+solve(i, v, k-1));
            }
        }
    }
    
    return ans;
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &k, &m);
    memset(a, 0xFF, sizeof(a));
    memset(e, 0x3F, sizeof(e));
    
    for(; m>0; m--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[u][v]=min(e[u][v], w);
    }
    
    int ans=INF;
    
    for(int i=1; i<=n; i++)
    {
        ans=min(ans, solve(i, 1, k));
        ans=min(ans, solve(i, n, k));
    }
    
    printf("%d\n", ans>=INF ? -1 : ans);
}
