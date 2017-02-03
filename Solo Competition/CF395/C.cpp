#include<cstdio>
#include<set>
#include<vector>
using namespace std;
typedef long long lld;

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

lld solve(set<lld>& S, lld n, lld m, lld s, lld a)
{
    if( n==m )
        return 1;
    
    lld t=((s-a*n)%m+m)%m;
    lld c=n*(n-1)/2%m;
    lld x, y, g=gcd(c, m, x, y);
    x=(x%m+m)%m;
    lld d=x*t%m;
    
    if( t%g!=0 || d==0 )
        return -1;
    
    for(lld p=a, i=0; i<n; i++)
    {
        if( S.find(p)==S.end() )
            return -1;
        
        p=(p+d)%m;
    }
    
    return d;
}

int main()
{
    lld m;
    int n;
    scanf("%lld%d", &m, &n);
    vector<lld> a(n);
    set<lld> S;
    lld s=0;
    
    for(int i=0; i<n; i++)
    {
        scanf("%lld", &a[i]);
        S.insert(a[i]);
        s+=a[i];
    }
    
    s%=m;
    
    for(int i=0; i<n; i++)
    {
        lld d=solve(S, n, m, s, a[i]);
        
        if( d>0 )
        {
            printf("%lld %lld\n", a[i], d);
            return 0;
        }
    }
    
    printf("-1\n");
}
