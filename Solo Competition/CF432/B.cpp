#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int N=1<<21;

int main()
{
    int n;
    lld x, y;
    scanf("%d%lld%lld", &n, &x, &y);
    vector<lld> a(N, 0), b(N, 0);
    
    for(int i=0; i<n; i++)
    {
        int v;
        scanf("%d", &v);
        a[v]++;
    }
    
    for(int i=1; i<N; i++)
    {
        b[i]=b[i-1]+a[i]*i;
        a[i]=a[i-1]+a[i];
    }
    
    lld ans=x*n;
    vector<bool> isp(N, true);
    
    for(int i=2; i<N>>1; i++)
    {
        if( !isp[i] )
            continue;
        
        lld tmp=0;
        
        for(int j=0; tmp<ans && j+i<N; j+=i)
        {
            isp[j]=false;
            int m=max(0LL, i-x/y-1)+j;
            lld cx=a[m]-a[j];
            lld cy=(a[j+i-1]-a[m])*(j+i)-(b[j+i-1]-b[m]);
            
            if( cy>(ans-tmp)/y )
            {
                tmp=ans;
                break;
            }
            
            tmp+=cx*x+cy*y;
        }
        
        ans=min(ans, tmp);
    }
    
    printf("%lld\n", ans);
}
