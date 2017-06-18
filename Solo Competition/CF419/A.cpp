#include<cstdio>
#include<algorithm>
using namespace std;
const int N=128, INF=1<<20;
int a[N][N]={{0}};

bool sol(int n, int m)
{
    int t=INF, c[N]={0}, d[N]={0}, ans=0;
    
    for(int j=1; j<=m; j++)
        t=min(t, a[1][j]);
    
    for(int j=1; j<=m; j++)
    {
        c[j]=a[1][j]-t;
        ans+=a[1][j]-t;
    }
    
    t=INF;
    
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            a[i][j]-=c[j];
            
            if( a[i][j]!=a[i][1] )
                return false;
        }
        
        t=min(t, a[i][1]);
    }
    
    for(int i=1; i<=n; i++)
    {
        d[i]=a[i][1]-t;
        ans+=a[i][1]-t;
    }
    
    ans+=min(n, m)*t;
    printf("%d\n", ans);
    
    for(int j=1; j<=m; j++)
        for(; c[j]>0; c[j]--)
            printf("col %d\n", j);
    
    for(int i=1; i<=n; i++)
        for(; d[i]>0; d[i]--)
            printf("row %d\n", i);
    
    if( n<m )
    {
        for(int i=1; i<=n; i++)
            for(int k=0; k<t; k++)
                printf("row %d\n", i);
    }
    else
    {
        for(int j=1; j<=m; j++)
            for(int k=0; k<t; k++)
                printf("col %d\n", j);
    }
    
    return true;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            scanf("%d", &a[i][j]);
    
    if( !sol(n, m) )
        printf("-1\n");
}
