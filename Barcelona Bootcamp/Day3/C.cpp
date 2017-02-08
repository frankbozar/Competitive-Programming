#include<cmath>
#include<cstdio>
#include<cstring>
typedef long long lld;
lld dp[25][25][25][25];

lld solve(int a, int b, int c, int d)
{
    if( a<0 || b<0 )
        return 0;
    else if( a==0 && b==0 )
        return 1;
    
    lld& ans=dp[a][b][c][d];
    
    if( ans<0 )
    {
        ans=0;
        
        for(int i=c; i<=c; i++)
            for(int j=0; j<d; j++)
                if( i+j>0 )
                    for(int k=1; k*i<=a && k*j<=b; k++)
                        ans+=solve(a-k*i, b-k*j, i, j);
        
        for(int i=0; i<c; i++)
            for(int j=0; j<=b; j++)
                if( i+j>0 )
                    for(int k=1; k*i<=a && k*j<=b; k++)
                        ans+=solve(a-k*i, b-k*j, i, j);
    }
    
    return ans;
}

lld solve(lld n)
{
    int k=24;
    
    for(; k>0; k--)
        if( fabs(pow(round(pow(n, 1.0/k)), k)-n)<1e-3 )
            break;
    
    memset(dp, -1, sizeof(dp));
    return solve(k, k, k, k);
}

int main()
{
    lld n;
    scanf("%lld", &n);
    printf("%lld\n", solve(n));
}
