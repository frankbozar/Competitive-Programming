#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;
lld b[1<<20][2]={{0, -INF}};

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        lld ans=-INF;
        
        for(int i=1; i<=n; i++)
        {
            lld x;
            scanf("%lld", &x);
            b[i][0]=max(b[i-1][1]+x, 0LL);
            b[i][1]=max(b[i-1][0]+x, x);
            ans=max(ans, b[i][1]);
        }
        
        printf("%lld\n", ans);
    }
}

/*

1
4
8 -7 9 1

*/
