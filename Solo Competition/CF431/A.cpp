#include<cstdio>
const int N=1<<10;

int f(int x)
{
    return x*(x-1)>>1;
}

void sol(int n)
{
    if( n==0 )
        putchar('a');
    
    for(char c='a'; n>0; c++)
    {
        int x=N;
        for(; f(x)>n; x--);
        n-=f(x);
        
        for(int i=0; i<x; i++)
            putchar(c);
    }
    
    putchar('\n');
}

int main()
{
    int n;
    scanf("%d", &n);
    sol(n);
}
