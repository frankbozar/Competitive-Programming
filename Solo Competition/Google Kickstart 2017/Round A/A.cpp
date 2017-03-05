#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld mod=1000000007;

lld mbs(lld x)
{
    return (x%mod+mod)%mod;
}

lld pmd(lld x, lld p)
{
    lld ans=1;
    
    for(x=mbs(x); p>0; p>>=1)
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

lld pro(lld a=1, lld b=1, lld c=1, lld d=1, lld e=1, lld f=1)
{
    a=mbs(a);
    b=mbs(b);
    c=mbs(c);
    d=mbs(d);
    e=mbs(e);
    f=mbs(f);
    a=a*b%mod;
    c=c*d%mod;
    e=e*f%mod;
    return a*c%mod*e%mod;
}

lld sum(lld n, lld p, lld a)
{
    switch( p )
    {
        case 0:
            return pro(a, n);
        case 1:
            return pro(a, n, n+1, inv(2));
        case 2:
            return pro(a, n, n+1, (n<<1)|1, inv(6));
        case 3:
            return pro(a, n, n, n+1, n+1, inv(4));
        default:
            return 0;
    }
}

lld solve(lld n, lld m)
{
    if( n>m )
        swap(n, m);
    
    lld t1=0;
    t1+=sum(n/2, 0, pro(6, n, m));
    t1+=sum(n/2, 1, 1-9*n-9*m+pro(6, n, m));
    t1+=sum(n/2, 2, 15-9*n-9*m);
    t1+=sum(n/2, 3, 14);
    t1=pro(t1, 2, inv(6));
    
    lld t2=0;
    t2+=sum(n-1, 0, pro(3, n, n, m)-pro(n, n, n)+pro(3, n, m)+n);
    t2+=sum(n-1, 1, pro(-6, n, m)-3*n-3*m-1);
    t2+=sum(n-1, 2, 3*n+3*m+3);
    t2+=sum(n-1, 3, -2);
    t2-=sum(n/2, 0, pro(3, n, n, m)-pro(n, n, n)+pro(3, n, m)+n);
    t2-=sum(n/2, 1, pro(-6, n, m)-3*n-3*m-1);
    t2-=sum(n/2, 2, 3*n+3*m+3);
    t2-=sum(n/2, 3, -2);
    t2=pro(t2, 2, inv(6));
    
    lld t3=0;
    t3+=sum(n/2, 0, n*m);
    t3+=sum(n/2, 1, -2*n-2*m);
    t3+=sum(n/2, 2, 4);
    t3+=sum(n-1, 0, n*m);
    t3+=sum(n-1, 1, -n-m);
    t3+=sum(n-1, 2, 1);
    
    return mbs(t1+t2-t3);
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        lld n, m;
        scanf("%lld%lld", &n, &m);
        printf("Case #%d: %lld\n", cases, solve(n, m));
    }
}

/*

4
2 4
3 4
4 4
1000 500

*/
