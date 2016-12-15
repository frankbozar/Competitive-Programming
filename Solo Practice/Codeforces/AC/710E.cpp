#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;

int main()
{
    int n, x, y;
    scanf("%d%d%d", &n, &x, &y);
    vector<lld> a((n<<1)|1, INF);
    a[0]=0;
    
    for(int i=1; i<=n; i++)
    {
        a[i]=min(a[i], a[i-1]+x);
        a[i<<1]=min(a[i<<1], a[i]+y);
        a[(i<<1)-1]=min(a[(i<<1)-1], a[i]+x+y);
    }
    
    printf("%lld\n", a[n]);
}