#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<40;
#define x first
#define y second

int main()
{
    int n;
    map<lld, lld> M;
    M[0]=INF;
    M[INF]=0;
    
    for(scanf("%d", &n); n>0; n--)
    {
        lld x, y;
        scanf("%lld%lld", &x, &y);
        lld ans=0;
        
        for(auto it=M.lower_bound(x); it->y<y; )
        {
            auto jt=it--;
            lld h=y-jt->y;
            lld w=min(x, jt->x)-it->x;
            ans+=h*w;
            
            if( jt->x<=x )
                M.erase(jt);
        }
        
        if( ans>0 )
            M[x]=y;
        
        printf("%lld\n", ans);
    }
}
