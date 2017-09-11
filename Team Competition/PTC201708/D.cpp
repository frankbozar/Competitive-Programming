
#include<cstdio>
#include<algorithm>

using namespace std;

typedef long long lld;

int main()
{
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        lld n, x, y;
        scanf("%lld%lld%lld", &n, &x, &y);
        lld ans=0;
        for(int i=1; i<n; i++)
        {
            ans+=i*(n-i)*(n-i);
        }
        //printf("~%lld\n", ans);
        ans-=min(n-x, n-y);
        //printf("~~%lld\n", ans);
        ans-=min(n-x, y-1);
        //printf("~%lld\n", ans);
        ans-=min(x-1, n-y);
        //printf("~~%lld\n", ans);
        ans-=min(x-1, y-1);
        //printf("~%lld\n", ans);
        for(int i=2; i<=n-y; i++)
            ans-=max(0LL, min(x, n-i+1)-max(1LL, x+1-i));
        for(int i=2; i<=y-1; i++)
            ans-=max(0LL, min(x, n-i+1)-max(1LL, x+1-i));
        for(int i=2; i<=n-x; i++)
            ans-=max(0LL, min(y, n-i+1)-max(1LL, y+1-i));
        for(int i=2; i<=x-1; i++)
            ans-=max(0LL, min(y, n-i+1)-max(1LL, y+1-i));
        printf("%lld\n", ans);

    }



}

