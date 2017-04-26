#include<cstdio>
typedef long long lld;

lld C(lld n, lld m)
{
    if( m>n )
        return 0;
    else if( m==0 || m==n )
        return 1;
    else
        return C(n-1, m-1)+C(n-1, m);
}

int main()
{
    freopen("popcorn.in", "rb", stdin);
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        printf("%lld\n", C(n, m));
    }
}
