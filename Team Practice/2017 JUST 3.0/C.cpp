#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=0x7FFFFFFFFFFFFFFFLL;
#define data pair<lld,lld>
#define c first
#define p second

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        lld k, n, m, x, s, ans=INF;
        scanf("%lld%lld%lld%lld%lld", &k, &n, &m, &x, &s);
        vector<data> a(n+1, data(0, x)), b(m+1, data(0, 0));
        
        for(int i=1; i<=n; i++)
            scanf("%lld", &a[i].p);
        
        for(int i=1; i<=n; i++)
            scanf("%lld", &a[i].c);
        
        for(int i=1; i<=m; i++)
            scanf("%lld", &b[i].p);
        
        for(int i=1; i<=m; i++)
            scanf("%lld", &b[i].c);
        
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        
        for(int i=1; i<=n; i++)
            a[i].p=min(a[i].p, a[i-1].p);
        
        for(int i=1; i<=m; i++)
            b[i].p=max(b[i].p, b[i-1].p);
        
        for(int j=m, i=0; i<=n; i++)
        {
            for(; j>=0 && a[i].c+b[j].c>s; j--);
            
            if( j<0 )
                break;
            
            if( k<=b[j].p )
                ans=0;
            else
                ans=min(ans, (k-b[j].p)*min(a[i].p, x));
        }
        
        printf("%lld\n", ans);
    }
}
