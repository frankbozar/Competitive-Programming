#include<cstdio>
#include<cstring>
typedef long long lld;
int a[1<<5];
lld d[1<<20];

lld sol(int n, int v)
{
    lld& ans=d[v];

    if( ans<0 )
    {
        int i=__builtin_popcount(v);
        ans=0;

        for(int j=0; j<n; j++)
            if( (~(v|a[i])>>j)&1 )
                ans+=sol(n, v|(1<<j));
    }

    return ans;
}

int main()
{
    int N;

    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        memset(a, 0x00, sizeof(a));
        memset(d, 0xFF, sizeof(d));
        d[(1<<n)-1]=1;

        for(; m>0; m--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            a[x-1]|=1<<(y-1);
        }

        printf("%lld\n", sol(n, 0));
    }
}
