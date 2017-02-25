#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld mod=1000003;

lld pmd(lld x, lld p)
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

lld inv(lld x)
{
    return pmd(x, mod-2);
}

lld cnt(lld x)
{
    lld ans=0;
    
    for(x>>=1; x>0; x>>=1)
        ans+=x;
    
    return ans;
}

lld fct(lld a, lld k)
{
    lld ans=1;
    
    for(lld i=0; i<k; i++)
        ans=ans*(a-i+mod)%mod;
    
    return ans;
}

int main()
{
    lld n, k;
    scanf("%lld%lld", &n, &k);
    
    if( n<=60 && 1LL<<n<k )
    {
        printf("1 1\n");
        return 0;
    }
    
    lld a=pmd(2, n);
    lld b=pmd(a, k);
    lld c=cnt(k-1)+n;
    lld d=k>=mod ? 0 : fct(a, k);
    lld C=inv(pmd(2, c));
    lld A=(b-d+mod)*C%mod;
    lld B=b*C%mod;
    printf("%lld %lld\n", A, B);
}

/*

3 2
1 3
4 3

*/
