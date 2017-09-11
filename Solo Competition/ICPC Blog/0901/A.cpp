#include<cstdio>
typedef long long lld;

bool sol(lld x, lld y, lld z)
{
    return z%(x+y)<=x-1;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        lld x, y, z;
        scanf("%lld%lld%lld", &x, &y, &z);
        printf(sol(x, y, z) ? "Possible\n" : "Impossible\n");
    }
}
