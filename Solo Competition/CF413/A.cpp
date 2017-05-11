#include<cstdio>

int f(int n, int t, int k)
{
    for(int i=0; ; i++)
        if( i/t*k>=n )
            return i;
}

int f(int n, int t, int k, int d)
{
    for(int i=0; ; i++)
        if( i<=d && i/t*k>=n )
            return i;
        else if( i>d && i/t*k+(i-d)/t*k>=n )
            return i;
}

int main()
{
    int n, t, k, d;
    scanf("%d%d%d%d", &n, &t, &k, &d);
    printf(f(n, t, k)>f(n, t, k, d) ? "YES\n" : "NO\n");
}
