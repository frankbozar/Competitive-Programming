#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;

vector<lld> plist(int n=1<<20)
{
    vector<bool> isp(n, true);
    vector<lld> p;
    
    for(lld i=2; i<n; i++)
    {
        if( isp[i] )
        {
            p.push_back(i);
            
            for(lld j=i*i; j<n; j+=i)
                isp[j]=false;
        }
    }
    
    return p;
}

lld phi(lld n)
{
    const static vector<lld> p=plist();
    vector<pair<lld, lld>> d;
    lld ans=1;
    
    for(int i=0; p[i]*p[i]<=n; i++)
    {
        lld k;
        
        for(k=1; n%p[i]==0; k*=p[i])
            n/=p[i];
        
        if( k!=1 )
            ans*=k-k/p[i];
    }
    
    return n==1 ? ans : ans*(n-1) ;
}

int main()
{
    lld n, m;
    scanf("%lld%lld", &n, &m);
    
    for(m=(m+1)>>1; m>0 && n>1; m--)
        n=phi(n);
    
    printf("%lld\n", n%mod);
}
