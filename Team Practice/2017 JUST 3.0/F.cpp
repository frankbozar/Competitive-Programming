#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;

int f(lld x)
{
    return x<=1 ? 0 : f(x>>1)+(x&1)+1;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<int> a(n+1, 0);
        
        for(int i=1; i<=n; i++)
        {
            lld x;
            scanf("%lld", &x);
            a[i]=a[i-1]+f(x);
        }
        
        for(; m>0; m--)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", a[r]-a[l-1]);
        }
    }
}
