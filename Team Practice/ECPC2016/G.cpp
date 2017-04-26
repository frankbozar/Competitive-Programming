#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long lld;

const lld p=1000000007;
const int N=1000000;

lld f[N+2], in[N+2];

lld pm(lld a, lld b)
{
    a%=p, b%=p;
    return b==0?1:(b&1?a:1)*pm(a*a%p, b>>1)%p;
}

lld com(lld a, lld b)
{
    return f[a]*in[b]%p*in[a-b]%p;
}

int main()
{
    freopen("galactic.in", "rb", stdin);
    
    f[0]=1;
    f[1]=1;
    for(int i=1; i<N+2; i++)
        f[i]=i*f[i-1]%p;
    in[0]=0;
    in[1]=1;
    for(int i=2; i<N+2; i++)
        in[i]=pm(f[i], p-2);
    
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        
        lld n, k;
        scanf("%lld%lld", &n, &k);
        if(k>n)
        {
            printf("0\n");
            continue;
        }
        lld ans=pm(k, n);
        for(int i=1; i<=k; i++)
        {
            ans=(ans+(i&1?-1:1)*com(k, i)*pm(k-i, n)%p+p)%p;
        }
        printf("%lld\n", ans);
    }
}
