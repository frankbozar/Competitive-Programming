#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;

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

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n+1, 0), b(n+1, 0), c(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    
    lld ans=1;
    
    for(int i=1; i<=n; i++)
    {
        for(int p=0, u=i; ; u=a[u])
        {
            if( b[u]==i )
            {
                ans=ans*(pmd(2, p-c[u])+mod-2)%mod;
                ans=ans*pmd(2, c[u])%mod;
                break;
            }
            else if( b[u]!=0 )
            {
                ans=ans*pmd(2, p)%mod;
                break;
            }
            else
            {
                b[u]=i;
                c[u]=p++;
            }
        }
    }
    
    printf("%lld\n", ans);
}
