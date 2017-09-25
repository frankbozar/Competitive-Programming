#include<cstdio>
#include<cstring>
typedef long long lld;
lld cc[64][64];
lld dp[16][64][1024];

lld C(int n, int m)
{
    if( n<m || m<0 )
        return 0;
    else if( n==m || m==0 )
        return 1;
    
    lld& ans=cc[n][m];
    
    if( ans<0 )
        ans=C(n-1, m-1)+C(n-1, m);
    
    return ans;
}

lld f(int b, int n, int p)
{
    if( n==0 )
        return p==0;
    else if( b<=0 )
        return 0;
    
    lld& ans=dp[b][n][p];
    
    if( ans<0 )
    {
        ans=0;
        
        for(int i=(p>>b)&1; i<=n; i+=2)
            ans+=f(b-1, n-i, p^((i&1)<<b))*C(n, i);
    }
    
    return ans;
}

lld f(int b, int n, int p, int t)
{
    lld ans=0;
    
    for(int i=p&1; i<=n; i+=2)
        ans+=f(b, n-i, p^(i&1))*C(n-(t>0&&i>0), i);
    
    return ans;
}

lld f(int b, lld n)
{
    if( n<=0 )
        return 0;
    
    lld ans=0;
    int a[64]={0}, l=0, p=0;
    
    for(lld m=n; m>0; m/=b)
        a[l++]=m%b;
    
    for(int i=2; i<l; i+=2)
        ans+=f(b-1, i, 0, 1);
    
    for(int m=l; m-->0; p^=1<<a[m])
        for(int i=m==l-1; i<a[m]; i++)
            ans+=f(b-1, m, p^(1<<i), 0);
    
    return ans+(p==0);
}

int main()
{
    memset(cc, 0xFF, sizeof(cc));
    memset(dp, 0xFF, sizeof(dp));
    int n;
    
    for(scanf("%d", &n); n>0; n--)
    {
        lld b, l, r;
        scanf("%lld%lld%lld", &b, &l, &r);
        printf("%lld\n", f(b, r)-f(b, l-1));
    }
}
