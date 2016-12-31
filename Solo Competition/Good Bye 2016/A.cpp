#include<cstdio>

int solve(int n, int m)
{
    for(int i=n; i>0; i--)
        if( 5*i*(i+1)/2<=m )
            return i;
    
    return 0;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d\n", solve(n, 240-m));
}
