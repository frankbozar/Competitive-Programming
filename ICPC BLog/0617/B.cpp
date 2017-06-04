#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

int main()
{
    int n, m, s=0;
    scanf("%d%d", &n, &m);
    vector<int> a(n, 0);
    
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
        s+=a[i];
    }

    sort(a.rbegin(), a.rend());
    lld ans=(m-s)*(lld)n;
    
    for(int i=0; i<n; i++)
        ans+=a[i]*(i+1LL);
    
    printf("%lld\n", ans);
}
