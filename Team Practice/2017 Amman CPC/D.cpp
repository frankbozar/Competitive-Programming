#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;
const int N=1<<18;
lld F[N]={1}, f[N]={1};

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

lld H(int n, int m)
{
    return C(n+m-1, n-1);
}

int main()
{
    for(int i=1; i<N; i++)
    {
        F[i]=F[i-1]*i%mod;
        f[i]=f[i-1]*inv(i)%mod;
    }
    
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%lld\n", (H(b+1, a-b-1)<<1)%mod);
    }
}
