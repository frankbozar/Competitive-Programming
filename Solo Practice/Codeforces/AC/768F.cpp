#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;
const int N=3000001;
vector<lld> F(N, 1), f(N, 1);

lld inv(lld x)
{
    lld ans=1;
    
    for(lld p=mod-2; p>0; p>>=1)
    {
        if( p&1 )
            ans=ans*x%mod;
        
        x=x*x%mod;
    }
    
    return ans;
}

lld C(int n, int m)
{
    return F[n]*f[m]%mod*f[n-m]%mod;
}

lld count(lld n, lld m, lld k)
{
    if( m==0 )
        return 0;
    
    n-=k*m;
    return n<0 ? 0 : C(n+m-1, m-1)%mod;
}

lld count(int n, int m, int k, int i, int j)
{
    return count(n, i, 1)*count(m, j, k)%mod;
}

lld solve(int n, int m, int k)
{
    lld ans=0;
    
    for(int i=1; i<=max(n, m); i++)
    {
        ans+=count(n, m, k, i, i)<<1;
        ans+=count(n, m, k, i, i-1);
        ans+=count(n, m, k, i-1, i);
        ans%=mod;
    }
    
    return ans;
}

int main()
{
    for(int i=1; i<=N; i++)
    {
        F[i]=F[i-1]*i%mod;
        f[i]=f[i-1]*inv(i)%mod;
    }
    
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    
    if( n==0 )
        printf("%d\n", m>k ? 1 : 0);
    else if( m==0 )
        printf("1\n");
    else
    {
        lld p=solve(n, m, k+1);
        lld q=solve(n, m, 1);
        printf("%lld\n", p*inv(q)%mod);
    }
}
