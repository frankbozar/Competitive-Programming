#include<cstdio>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
typedef bitset<16> bs;

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int N=1<<m;
    vector<lld> a(N, 0);
    
    for(int i=0; i<N; i++)
        if( bs(i).count()>=k )
            a[i]=1;
    
    for(int i=m; i<n; i++)
    {
        vector<lld> b(N, 0);
        
        for(int j=0; j<N; j++)
        {
            if( a[j]<=0 )
                continue;
            
            b[(j>>1)|(1<<(m-1))]+=a[j];
            
            if( bs(j>>1).count()>=k )
                b[j>>1]+=a[j];
        }
        
        a=b;
    }
    
    lld ans=0;
    
    for(lld x : a)
        ans+=x;
    
    printf("%lld\n", ans);
}
