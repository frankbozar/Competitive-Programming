#include<cstdio>
typedef long long lld;
const lld mod=100003;

lld inv(lld x)
{
    lld ans=1;
    
    for(int p=mod-2; p>0; p>>=1)
    {
        if( p&1 )
            ans=ans*x%mod;
        
        x=x*x%mod;
    }
    
    return ans;
}

lld fact(int n)
{
    return n<=1 ? 1 : fact(n-1)*n%mod;
}

lld C(int n, int m)
{
    return fact(n)*inv(fact(m)*fact(n-m)%mod)%mod;
}

lld solve(lld x, lld y)
{
    if( (x^y)&1 || y>x )
        return 0;
    
    lld ans=0;
    
    for(lld t=(x-y)>>1, i=0; i<=t; i++)
    {
        ans+=fact(x-i)*inv(fact(i)*fact(((x+y)>>1)-i)*fact(((x-y)>>1)-i)%mod)%mod;
        //ans+=C(x-i, x-(i<<1))*C(x-(i<<1), t-i)%mod;
    }
    
    return ans%mod;
}

int cnt=0;

lld f(lld x, lld y)
{
    ++cnt;
    
    if( y<0 )
        return f(x, -y);
    else if( (x^y)&1 || y>x )
        return 0;
    else if( x==0 )
        return 1;
    
    lld ans=y==0;
    
    for(lld i=x-1; i>=0; i-=2)
        ans+=f(i, y+1)+f(i, y-1);
    
    return ans%mod;
}

int main()
{
    lld x, y;
    scanf("%lld%lld", &x, &y);
    printf("%lld %lld\n", solve(x, y), f(x, y));
    printf("%d\n", cnt);
}
