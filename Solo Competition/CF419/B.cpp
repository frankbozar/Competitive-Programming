#include<cstdio>
typedef long long lld;
const lld mod=1000000007;
const int N=1<<20;

lld labs(lld x)
{
    return (x%mod+mod)%mod;
}

lld inv(lld x)
{
    lld ans=1;
    x=(x%mod+mod%mod);
    
    for(lld p=mod-2; p>0; p>>=1)
    {
        if( p&1 )
            ans=ans*x%mod;
        
        x=x*x%mod;
    }
    
    return ans;
}

lld f(lld a[], int n)
{
    for(int t=0; n>1; n--)
        for(int i=1; i<n; i++)
        {
            a[i-1]+=(t^=1) ? a[i] : -a[i] ;
            a[i-1]=labs(a[i-1]);
        }
    
    return a[0];
}

lld g(lld a[], int n)
{
    lld ans=0, C=1;
    
    for(int x=n>>1, y=0, i=0; i<n; i+=2, y++)
    {
        ans+=a[i]*C%mod;
        C=C*(x-y)%mod*inv(y+1)%mod;
    }
    
    return ans%mod;
}

lld a[N];

int main()
{
    int n;
    scanf("%d", &n);
    
    for(int i=0; i<n; i++)
    {
        scanf("%lld", &a[i]);
        a[i]=labs(a[i]);
        b[i]=a[i];
    }
    
    if( n>8 )
    {
        int m=(((n-1)>>2)<<2)|1;
        
        for(int i=0; i<n-m+1; i++)
            a[i]=g(a+i, m);
        
        n-=m-1;
    }
    
    printf("%lld\n", f(a, n));
}
