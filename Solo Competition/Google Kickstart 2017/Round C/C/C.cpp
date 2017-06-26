#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=64;
char s[3][N];
int a[N][N][N];

int solve(int n, int p, int q)
{
    if( p<0 || q<0 )
        return -N;
    else if( n==0 )
        return p==0 && q==0 ? 0 : -N ;
    
    int& ans=a[n][p][q];
    
    if( ans==-1 )
    {
        const char* c="FT";
        
        for(int i=0; i<2; i++)
            ans=max(ans, solve(n-1, p-(s[1][n-1]==c[i]), q-(s[2][n-1]==c[i]))+(s[0][n-1]==c[i]));
        
        if( ans<0 )
            ans=-N;
    }
    
    return ans;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m, p, q;
        scanf("%d%d", &n, &m);
        
        if( n==1 )
        {
            scanf("%s%s%d", s[1], s[0], &p);
            strcpy(s[2], s[1]);
            q=p;
        }
        else
        {
            scanf("%s%s%s%d%d", s[1], s[2], s[0], &p, &q);
        }
        
        memset(a, 0xFF, sizeof(a));
        printf("Case #%d: %d\n", cases, solve(m, p, q));
    }
}

/*

3

1 2
TF
FF
1

1 3
TTT
TTF
0

2 3
TTF
FTF
TTT
1 2

*/
