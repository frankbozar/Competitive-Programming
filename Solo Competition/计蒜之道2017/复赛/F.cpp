#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
const int N=18;
typedef bitset<N> bs;
typedef long long lld;
const lld mod=1000000007;

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

int a[N], n, m;
int d[1<<N][N+1];
int g[1<<N]={0};

lld f(int x, int t)
{
    bs b(x);
    
    if( t>(int)b.count() )
        return 0;
    else if( t==0 )
        return x==0;
    
    int& ans=d[x][t];
    
    if( ans<0 )
    {
        lld tmp=0;
        
        for(int i=0; i<n; i++)
        {
            if( !b[i] )
                continue;
            
            int c=0;
            
            for(int j=i; j<n; j++)
            {
                if( !b[j] )
                    continue;
                
                c|=1<<j;
                
                if( g[c]<m )
                    break;
                
                tmp+=f(x^c, t-1);
            }
        }
        
        ans=tmp%mod;
    }
    
    return ans;
}

int main()
{
    memset(d, 0xFF, sizeof(d));
    scanf("%d%d", &n, &m);
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    for(int i=1; i<1<<n; i++)
        g[i]=gcd(a[__builtin_ctz(i)], g[i^(i&-i)]);
    
    lld ans=0;
    
    for(int i=1; i<=n; i++)
        ans+=f((1<<n)-1, i)*i;
    
    printf("%lld\n", ans%mod);
}

/*

18 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

*/
