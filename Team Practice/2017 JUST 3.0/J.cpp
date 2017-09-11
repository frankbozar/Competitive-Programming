#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1<<10;
int a[N], dp[N][N];

int sol(int n, int l, int r)
{
    if( l>=r )
        return 0;
    
    int& ans=dp[l][r];
    
    if( ans==0x3F3F3F3F )
    {
        if( (n-r+l)&1 )
            ans=min(sol(n, l+1, r)-a[l], sol(n, l, r-1)-a[r-1]);
        else
            ans=max(sol(n, l+1, r)+a[l], sol(n, l, r-1)+a[r-1]);
    }
    
    return ans;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        memset(dp, 0x3F, sizeof(dp));
        int n;
        scanf("%d", &n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        printf("%d\n", sol(n, 0, n));
    }
}
