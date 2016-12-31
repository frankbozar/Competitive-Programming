#include<cstdio>
#include<cstring>
const int d[8][2]={{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}}, N=320;
int a[N][N][32][8], b[N][N], t[32], n, ans=0;

void ok(int x=N>>1, int y=N>>1, int k=0, int p=0)
{
    p&=7;
    
    if( k>=n || a[x][y][k][p] )
        return ;
    
    a[x][y][k][p]=1;
    
    for(int i=0; i<t[k]; i++)
    {
        x+=d[p][0];
        y+=d[p][1];
        
        if( b[x][y]==0 )
        {
            b[x][y]=1;
            ans++;
        }
    }
    
    ok(x, y, k+1, p+1);
    ok(x, y, k+1, p+7);
}

int main()
{
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(t, 0, sizeof(t));
    scanf("%d", &n);
    
    for(int i=0; i<n; i++)
        scanf("%d", &t[i]);
    
    ok();
    printf("%d\n", ans);
}
