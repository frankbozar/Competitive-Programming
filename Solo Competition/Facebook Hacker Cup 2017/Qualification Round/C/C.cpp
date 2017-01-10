#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int K=6, N=20, M=400;
const int f[K]={4, 6, 8, 10, 12, 20};
double p[K][N+1][M+1]={{{0}}};

double solve(const char* s, int m)
{
    int x, y, z=0;
    
    if( sscanf(s, "%dd%d%d", &x, &y, &z)==3 )
        m-=z;
    
    for(int i=0; i<K; i++)
        if( y==f[i] )
            y=i;
    
    if( m<=0 )
        return 1;
    else if( m>f[y]*x )
        return 0;
    else
        return 1-p[y][x][m-1];
}

int main()
{
    for(int k=0; k<K; k++)
    {
        for(int j=0; j<=f[k]*N; j++)
            p[k][0][j]=1;
        
        for(int i=1; i<=N; i++)
        {
            for(int j=1; j<=f[k]*i; j++)
                p[k][i][j]=p[k][i][j-1]+(p[k][i-1][j-1]-(j-f[k]-1>=0 ? p[k][i-1][ j-f[k]-1 ] : 0))/f[k];
            
            for(int j=f[k]*i+1; j<=f[k]*N; j++)
                p[k][i][j]=p[k][i][j-1];
        }
    }
    
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int m, n;
        scanf("%d%d", &m, &n);
        double ans=0;
        
        for(int i=0; i<n; i++)
        {
            char s[32]={0};
            scanf("%s", s);
            ans=max(ans, solve(s, m));
        }
        
        printf("Case #%d: %.10f\n", cases, ans);
    }
}
