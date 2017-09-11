#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;
vector<vector<int>> e;
vector<lld> d;

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

lld sol(int p, int u)
{
    lld& ans=d[u];
    
    if( ans<0 )
    {
        ans=1;
        
        for(int v : e[u])
            if( v!=p )
                ans=ans*sol(u, v)%mod;
        
        if( e[u].size()!=1 || e[u].front()!=p )
            ans=ans*2%mod;
    }
    
    return ans;
}

void dfs(lld& ans, lld a, int p, int u)
{
    a=a*sol(p, u)%mod;
    ans+=a;
    
    if( p==0 && e[u].size()==1 )
        a=a*inv(2)%mod;
    
    for(int v : e[u])
        if( v!=p )
            dfs(ans, a*inv(sol(u, v))%mod, u, v);
}

int main()
{
    int n;
    scanf("%d", &n);
    e.resize(n+1);
    d.assign(n+1, -1);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    lld ans=0;
    dfs(ans, 1, 0, 1);
    printf("%lld\n", ans%mod);
}
