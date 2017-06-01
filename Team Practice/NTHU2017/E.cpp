#include<cstdio>

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int a, m;
        scanf("%d %d",&a, &m);
        m/=gcd(a+1, m);
        printf((m&1) ? "YES\n" : "NO\n");
    }
}
