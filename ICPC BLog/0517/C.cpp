#include<cstdio>
typedef long long lld;

lld f(lld x)
{
    if( x<=0 )
        return 0;
    
    lld ans=0;
    
    for(lld i=1; i*i<=x; i++)
        ans+=(x-i*i)/i*2+1;
    
    return ans;
}

int main()
{
    lld l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", f(r)-f(l-1));
}
