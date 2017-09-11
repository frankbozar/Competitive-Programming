#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld N=1001001;
lld mod, F[N]={1}, f[N]={1}, ans[N]={0};

lld pmd(lld x, lld p, lld m)
{
    lld ans=1;
    
    for(; p>0; p>>=1)
    {
        if( p&1 )
            ans=ans*x%m;
        
        x=x*x%m;
    }
    
    return ans;
}

lld inv(lld x, lld m)
{
    return pmd(x, m-2, m);
}

lld C(lld n, lld m)
{
    return F[n]*f[m]%mod*f[n-m]%mod;
}

void phi(lld a, lld q)
{
    mod=1;
    
    for(lld p=a; p!=1; p=p*a%q)
        mod++;
}

int main()
{
    lld n, m, a, q;
    scanf("%lld %lld %lld %lld", &n, &m, &a, &q);
    phi(a, q);
    
    for(int i=1; i<N; i++)
    {
        F[i]=F[i-1]*i%mod;
        f[i]=f[i-1]*inv(i, mod)%mod;
    }
    
    for(int i=0; i<n; i++)
    {
        if( i<=m )
            ans[i+1]=(ans[i]+C(m, i))%mod;
        else
            ans[i+1]=ans[i];
    }
    
    for(int i=0; i<n; i++)
        printf(i==n-1 ? "%lld\n" : "%lld ", pmd(a, ans[n-i], q));
}

