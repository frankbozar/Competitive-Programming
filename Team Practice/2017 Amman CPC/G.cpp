#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;

lld gcd(lld a, lld b)
{
    return b==0 ? a : gcd(b, a%b);
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, ans=0;
        scanf("%d", &n);
        vector<lld> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%lld", &a[i]);
        
        for(int i=0; i<n; i++)
        {
            ans++;
            lld s=a[i], l=a[i];
            
            for(int j=i+1; j<n; j++)
            {
                lld p=a[j]/gcd(l, a[j]);
                
                if( l>INF/p )
                    break;
                
                l*=p;
                s+=a[j];
                
                if( s%l==0 )
                    ans++;
            }
        }
        
        printf("%d\n", ans);
    }
}
