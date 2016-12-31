#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int INF=1<<20;

lld lcm(lld a, lld b)
{
    return a*b/__gcd(a, b);
}

lld solve(const vector<int>& a, const int n)
{
    vector<vector<int>> d(n+1, vector<int>(n+1, INF));
    lld ans=1;
    
    for(int i=1; i<=n; i++)
        d[i][ a[i] ]=1;
    
    for(int k=1; k<=n; k++)
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
    
    for(int i=1; i<=n; i++)
    {
        if( d[i][i]>=INF )
            return -1;
        
        ans=lcm(ans, d[i][i]&1 ? d[i][i] : d[i][i]>>1);
    }
    
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    
    printf("%lld\n", solve(a, n));
}