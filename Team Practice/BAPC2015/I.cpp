#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;

lld gcd(lld a, lld b, lld& x, lld& y)
{
    if( b==0 )
    {
        x=1, y=0;
        return a;
    }
    
    lld g=gcd(b, a%b, y, x);
    y-=x*(a/b);
    return g;
}

void sol(lld n, lld& a, lld& b)
{
    a=1, b=n-1;
    
    for(lld f[2]={1, 1}; f[0]+f[1]<=n; f[1]+=f[0], f[0]=f[1]-f[0])
    {
        lld x, y;
        gcd(f[0], f[1], x, y);
        x*=n;
        y*=n;
        
        if( x<=0 )
        {
            lld t=(f[1]-x)/f[1];
            x+=t*f[1];
            y-=t*f[0];
        }
        
        {
            lld t=(x-1)/f[1];
            x-=t*f[1];
            y+=t*f[0];
        }
        
        if( y<x )
            continue;
        
        {
            lld t=(y-x)/(f[1]+f[0]);
            x+=t*f[1];
            y-=t*f[0];
        }
        
        if( b>y )
            b=y, a=x;
        else if( b==y )
            a=min(a, x);
    }
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        lld n, a, b;
        scanf("%lld", &n);
        sol(n, a, b);
        printf("%lld %lld\n", a, b);
    }
}

/*

5
89
123
1000
1573655
842831057

*/
