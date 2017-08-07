#include<cstdio>
typedef long long lld;

lld f(lld x, lld p)
{
    x%=p*3;
    x++;
    lld ans=(x%p)*(x/p);
    
    for(lld i=1; i<x/p; i++)
        ans+=i*p;
    
    return ans%3*p;
}

lld f(lld x)
{
    if( x<=0 )
        return 0;
    
    lld ans=0;
    
    for(lld p=1; p<=1LL<<40; p*=3)
        ans+=f(x, p);
    
    return ans;
}

lld s(lld x, lld y)
{
    lld ans=0;
    
    for(lld p=1; x>0 || y>0; p*=3)
    {
        ans+=(x%3-y%3+3)%3*p;
        x/=3;
        y/=3;
    }
    
    return ans;
}

int main()
{
    lld l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", s(f(r), f(l-1)));
}
