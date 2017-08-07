#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

lld gcd(lld a, lld b)
{
    return b==0 ? a : gcd(b, a%b);
}

vector<lld> plist(lld n)
{
    vector<bool> isp(n, true);
    vector<lld> p;
    
    for(lld i=2; i<n; i++)
        if( isp[i] )
        {
            p.push_back(i);
            
            for(lld j=i*i; j<n; j+=i)
                isp[j]=false;
        }
    
    return p;
}

multiset<lld> fact(lld x)
{
    static const vector<lld> pri=plist(1<<20);
    multiset<lld> p;
    
    for(int i=0; pri[i]*pri[i]<=x; i++)
        for(; x%pri[i]==0; x/=pri[i])
            p.insert(pri[i]);
    
    if( x>1 )
        p.insert(x);
    
    return p;
}

lld f(lld a, lld b)
{
    lld ans=0;
    
    for(multiset<lld> p=fact(a); b>0; )
    {
        lld g=gcd(a, b), t=0;
        a/=g;
        b/=g;
        
        for(lld x : fact(g))
            p.erase(p.find(x));
        
        for(lld x : p)
            t=max(t, (b-1)/x*x);
        
        ans+=b-t;
        b=t;
    }
    
    return ans;
}

int main()
{
    lld a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld\n", f(a, b));
}
