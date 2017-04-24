#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<10;
char s[N];
int a[N][N]={{0}};
int n, m, sx=0, sy=0, tx=0, ty=0;

bool ok(int px, int py, int qx, int qy)
{
    if( px>qx )
        swap(px, qx);
    
    if( py>qy )
        swap(py, qy);
    
    return a[qx][qy]-a[px-1][qy]-a[qx][py-1]+a[px-1][py-1]==0;
}

bool solve()
{
    for(int i=1; i<=n; i++)
        if( ok(sx, sy, i, sy) && ok(i, sy, i, ty) && ok(i, ty, tx, ty) )
            return true;
    
    for(int i=1; i<=m; i++)
        if( ok(sx, sy, sx, i) && ok(sx, i, tx, i) && ok(tx, i, tx, ty) )
            return true;
    
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%s", &s[1]);
        
        for(int j=1; j<=m; j++)
        {
            if( s[j]=='*' )
                a[i][j]=1;
            else if( s[j]=='S' )
                sx=i, sy=j;
            else if( s[j]=='T' )
                tx=i, ty=j;
            
            a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
        }
    }
    
    printf(solve() ? "YES\n" : "NO\n");
}
