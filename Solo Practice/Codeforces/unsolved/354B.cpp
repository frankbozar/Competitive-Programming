#include<cstdio>
#include<algorithm>
using namespace std;
const int N=32;
char s[N][N]={{0}};
int u[N][N]={{0}}, a[N][N]={{0}};

int get(char c)
{
    switch( c )
    {
        case 'a': return 1;
        case 'b': return -1;
        default: return 0;
    }
}

int solve(int x, int y)
{
    if( u[x][y] )
        return a[x][y];
    else
        u[x][y]=1;
    
    if( x==0 && y==0 )
        return a[x][y]=get(s[x][y]);
    else if( x==0 )
        return a[x][y]=get(s[x][y])+solve(x, y-1);
    else if( y==0 )
        return a[x][y]=get(s[x][y])+solve(x-1, y);
    else if( (x+y)&1 )
        return a[x][y]=get(s[x][y])+max(solve(x-1, y), solve(x, y-1));
    else
        return a[x][y]=get(s[x][y])+min(solve(x-1, y), solve(x, y-1));
}

int main()
{
    int n;
    scanf("%d", &n);
    
    for(int i=0; i<n; i++)
        scanf("%s", s[i]);
    
    int ans=solve(n-1, n-1);
    
    if( ans>0 )
        printf("FIRST\n");
    else if( ans<0 )
        printf("SECOND\n");
    else
        printf("DRAW\n");
}
