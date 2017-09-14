#include<cstdio>
typedef long long lld;
const int N=1001001;
lld F[N]={1}, f[N]={1}, v[N]={0}, ans[N]={0};

lld pmd(lld x, lld p, lld mod)
{
    lld ans=1;
    
    for(; p>0; p>>=1)
    {
        if( p&1 )
            ans=ans*x%mod;
        
        x=x*x%mod;
    }
    
    return ans;
}

lld inv(lld x, lld mod)
{
    return pmd(x, mod-2, mod);
}

lld count(lld x, lld mod)
{
    lld ans=0;
    
    do{
        x/=mod;
        ans+=x;
    }while( x>=mod );
    
    return ans;
}

lld C(lld n, lld m, lld mod)
{
    if( count(n, mod)-count(m, mod)-count(n-m, mod)>0 )
        return 0;
    else
        return F[n]*f[m]%mod*f[n-m]%mod;
}

lld init(lld a, lld q)
{
    lld mod=1;
    
    for(lld p=a; p!=1; p=p*a%q)
        mod++;
    
    for(int i=1; i<mod; i++)
        v[i]=inv(i, mod);
    
    for(int i=1; i<N; i++)
    {
        int k=i;
        for(; k%mod==0; k/=mod);
        F[i]=F[i-1]*k%mod;
        f[i]=f[i-1]*v[k]%mod;
    }
    
    return mod;
}

int main()
{
    lld n, m, a, q;
    scanf("%lld%lld%lld%lld", &n, &m, &a, &q);
    lld mod=init(a, q);
    
    for(int i=0; i<n; i++)
    {
        if( i<=m )
            ans[i+1]=(ans[i]+C(m, i, mod))%mod;
        else
            ans[i+1]=ans[i];
    }
    
    for(int i=0; i<n; i++)
        printf(i==n-1 ? "%lld\n" : "%lld ", pmd(a, ans[n-i], q));
}
