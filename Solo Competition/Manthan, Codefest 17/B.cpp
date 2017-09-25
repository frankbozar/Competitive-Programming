#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<62;

int main()
{
    int n;
    scanf("%d", &n);
    vector<lld> a(3, 0), b(n+1, 0), d(n+1, 0);
    d[0]=-INF;
    
    for(int i=0; i<3; i++)
        scanf("%lld", &a[i]);
    
    for(int i=1; i<=n; i++)
        scanf("%lld", &b[i]);
    
    for(int k=0; k<3; k++)
        for(int i=1; i<=n; i++)
            d[i]=max(d[i]+a[k]*b[i], d[i-1]);
    
    printf("%lld\n", d[n]);
}
