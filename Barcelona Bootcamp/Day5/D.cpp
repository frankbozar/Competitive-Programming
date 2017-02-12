#include<cstdio>
typedef long long lld;
const lld mod=1000000007;

lld count(lld n, lld x)
{
    lld t=x>>(n+1);
    x&=(1LL<<(n+1))-1;
    lld ans=t<<n;
    
    if( x>(1LL<<n) )
        ans+=x-(1LL<<n);
    
    return ans;
}

lld solve(lld n, lld l, lld r)
{
    lld ans=0;
    
    for(lld i=0; i<n; i++)
        ans=((ans<<1)+count(i, r)-count(i, l))%mod;
    
    return ans;
}

int main()
{
    int n, m;
    
    for(scanf("%d%d", &n, &m); m>0; m--)
    {
        lld l, r;
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", solve(n, l, r+1));
    }
}

/*

3 1
3 3

2 2
0 3
0 1

25 1
17 239

*/
