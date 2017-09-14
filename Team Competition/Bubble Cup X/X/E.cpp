#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;

lld pmd(int p)
{
    lld ans=1;
    
    for(lld x=2; p>0; p>>=1)
    {
        if( p&1 )
            ans=ans*x%mod;
        
        x=x*x%mod;
    }
    
    return ans;
}

int main()
{
    int n, l=0;
    scanf("%d", &n);
    vector<int> d(n+1, 0);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        d[u]++;
        d[v]++;
    }
    
    for(int i=1; i<=n; i++)
        l+=d[i]==1;
    
    n-=l;
    printf("%lld\n", (l*pmd(n+1)+n*pmd(n))%mod);
}
