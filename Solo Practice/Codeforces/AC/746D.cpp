#include<cstdio>

inline void print(int t)
{
    putchar(t==0 ? 'B' : 'G');
}

inline void print(int t, int n, int& m)
{
    if( m>0 )
        n++, m--;
    
    for(; n>0; n--)
        print(t);
}

void solve(int k, int a, int b, int t=0)
{
    if( a>b )
    {
        solve(k, b, a, 1);
        return ;
    }
    else if( (b+a)/(a+1)>k )
    {
        printf("NO\n");
        return ;
    }
    
    int n=b/(a+1), m=b%(a+1);
    print(t, n, m);
    
    for(int i=0; i<a; i++)
    {
        print(t^1);
        print(t, n, m);
    }
    
    putchar('\n');
}

int main()
{
    int n, k, a, b;
    scanf("%d%d%d%d", &n, &k, &a, &b);
    solve(k, a, b);
}