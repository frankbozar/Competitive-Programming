#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int N=1<<10;
char s[N][N];

int solve(int n, int m, int x, int y)
{
    int A=0, B=0, a=N, b=N;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            if( s[i][j]=='A' )
            {
                A++;
                a=min(a, abs(x-i)+abs(y-j));
            }
            else if( s[i][j]=='B' )
            {
                B++;
                b=min(b, abs(x-i)+abs(y-j));
            }
        }
    
    if( s[x][y]=='A' )
        return b==1 ? B : B ;
    else
        return a==1 ? A : A ;
}

int main()
{
    for(int n, m; scanf("%d%d", &n, &m)!=EOF; )
    {
        for(int i=0; i<n; i++)
            scanf("%s", s[i]);
        
        int k;
        scanf("%d", &k);
        
        for(int c=1; c<=k; c++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            printf("Case %d: %d\n", c, solve(n, m, x-1, y-1));
        }
    }
}
