#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<vector<lld>> a(n+1, vector<lld>(m+1, 0));
        vector<vector<lld>> b(n+1, vector<lld>(m+1, 0));
        vector<vector<lld>> c(n+1, vector<lld>(m+1, INF));
        vector<vector<lld>> d(n+1, vector<lld>(m+1, INF));
        
        for(int i=0; i<n; i++)
            for(int j=1; j<=m; j++)
                scanf("%lld", &a[i][j]);
        
        for(int i=0; i<n; i++)
            for(int j=1; j<m; j++)
            {
                scanf("%lld", &b[i][j]);
                b[i][j]+=b[i][j-1];
            }
        
        c[0][1]=d[0][1]=0;
        
        for(int i=0; i<n; i++)
            for(int j=1; j<=m; j++)
                for(int k=1; k<=m; k++)
                {
                    lld w=c[i][j]+a[i][k], t=d[i][j];
                    
                    if( j<k )
                        t+=b[i][k-1]-b[i][j-1];
                    else if( j>k )
                        t+=b[i][j-1]-b[i][k-1];
                    
                    if( c[i+1][k]>w )
                        c[i+1][k]=w, d[i+1][k]=t;
                    else if( c[i+1][k]==w )
                        d[i+1][k]=min(d[i+1][k], t);
                }
        
        for(int i=1; i<=m; i++)
        {
            if( c[n][0]>c[n][i] )
                c[n][0]=c[n][i], d[n][0]=d[n][i];
            else if( c[n][0]==c[n][i] )
                d[n][0]=min(d[n][0], d[n][i]);
        }
        
        printf("%lld %lld\n", c[n][0], d[n][0]);
    }
}
