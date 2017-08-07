#include<cmath>
#include<cstdio>
using namespace std;
typedef long long lld;
typedef long double llf;

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b) ;
}

bool sol(lld a, lld b)
{
    lld t=round(cbrt((llf)a*b));
    lld g=gcd(a, b);
    return  t*t*t==a*b && g%(a*b/g/g)==0 ;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf(sol(a, b) ? "Yes\n" : "No\n");
    }
}

/*

6
2 4
75 45
8 8
16 16
247 994
1000000000 1000000

*/
