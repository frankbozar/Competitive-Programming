#include<cstdio>
#include<set>
#include<map>
using namespace std;
typedef long long lld;
const lld INF=1LL<<50;

int main()
{
    int n;
    lld m, ans=0, sum=0, x;
    scanf("%d%lld", &n, &m);
    map<lld, lld> M;
    
    for(int i=1; i<=n; i++)
    {
        M[sum]++;
        scanf("%lld", &x);
        sum+=x;
        set<lld> S;
        
        for(x=1; S.find(x)==S.end() && -INF<=x && x<=INF; x*=m)
        {
            S.insert(x);
            
            if( M.find(sum-x)!=M.end() )
                ans+=M[sum-x];
        }
    }
    
    printf("%lld\n", ans);
}
