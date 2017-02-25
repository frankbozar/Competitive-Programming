#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;
const int N=128;
int c[N], p[N][N];
lld dp[N][N][N];

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    memset(c, 0, sizeof(c));
    memset(p, 0, sizeof(p));
    memset(dp, 0x3F, sizeof(dp));
    dp[0][m+1][0]=0;
    
    for(int i=1; i<=n; i++)
        scanf("%d", &c[i]);
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            scanf("%d", &p[i][j]);
    
    for(int i=1; i<=n; i++)
    {
        if(  c[i]==0)
        {
            for(int j=1; j<=m; j++)
                for(int k=1; k<=r; k++)
                    for(int l=1; l<=m+1; l++)
                        dp[i][j][k]=min(dp[i][j][k], dp[i-1][l][j==l ? k : k-1]+(c[i] ? 0 : p[i][j]));
        }
        else
        {
            for(int j=1; j<=m; j++)
            {
                if( j!=c[i] )
                    continue;
                
                for(int k=1; k<=r; k++)
                    for(int l=1; l<=m+1; l++)
                        dp[i][j][k]=min(dp[i][j][k], dp[i-1][l][c[i]==l ? k : k-1]);
            }
        }
    }
    
    lld ans=INF;
    
    for(int i=1; i<=m; i++)
        ans=min(ans, dp[n][i][r]);
    
    printf("%lld\n", ans>=INF ? -1 : ans);
}
