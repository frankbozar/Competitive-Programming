#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=16;
int a[N][N][N], b[N][N][N];

int solve(int h, int x, int y)
{
    int& ans=b[h][x][y];
    
    if( ans<0 )
    {
        if( h<1 || x>10 || y>10 )
            ans=0;
        else
        {
            ans=max(ans, solve(h-1, x, y));
            ans=max(ans, solve(h, x, y+1));
            ans=max(ans, solve(h, x+1, y));
            ans+=a[h][x][y];
        }
    }
    
    return ans;
}

int main()
{
    freopen("commandos.in", "rb", stdin);
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        memset(a, 0x00, sizeof(a));
        memset(b, 0xFF, sizeof(b));
        int n;
        
        for(scanf("%d", &n); n>0; n--)
        {
            int f, x, y, h;
            scanf("%d%d%d%d", &f, &x, &y, &h);
            a[f][x][y]+=h;
        }
        
        printf("%d\n", solve(10, 1, 1));
    }
}
