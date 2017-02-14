#include<cstdio>

int solve(int k, int a, int b)
{
    int p=a/k;
    int q=b/k;
    
    if( p==0 && b%k!=0 )
        return -1;
    else if( q==0 && a%k!=0 )
        return -1;
    else
        return p+q;
}

int main()
{
    int k, a, b;
    scanf("%d%d%d", &k, &a, &b);
    printf("%d\n", solve(k, a, b));
}
