#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;

int main()
{
    int n;
    scanf("%d", &n);
    vector<lld> a(n+1, 0);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &a[i]);
        a[i]+=a[i-1];
    }
    
    lld ans=-INF;
    int d[3]={0, 0, 0};
    
    for(int i=0; i<=n; i++)
    {
        int p=0, q=0;
        lld u=-INF, v=-INF;
        
        for(int j=0; j<=i; j++)
        {
            lld tmp=(a[j]-a[0])-(a[i]-a[j]);
            
            if( u<tmp )
                u=tmp, p=j;
        }
        
        for(int j=i; j<=n; j++)
        {
            lld tmp=(a[j]-a[i])-(a[n]-a[j]);
            
            if( v<tmp )
                v=tmp, q=j;
        }
        
        if( ans<u+v )
            ans=u+v, d[0]=p, d[1]=i, d[2]=q;
    }
    
    printf("%d %d %d\n", d[0], d[1], d[2]);
}
