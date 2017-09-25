#include<cstdio>

int f(int n, int m, int p, int i)
{
    for(; i<=n; i++)
        p=(p+m)%i;
    
    return p;
}
/*
int g(int n, int m, int k)
{
    int ans=0;
    
    for(int i=n; i>=k; i--)
    {
        ans+=
        
        
    }
    
    
    
}
*/
int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        int a[1<<20]={0}, p=0;
        
        for(int i=1; i<=n; i++)
        {
            for(int k=m; ; p=(p+1)%n)
            {
                k-=!a[p];
                
                if( k==0 )
                    break;
            }
            
            printf("%d %d %d %d %d %d\n", n, m, i, p, f(n, m, n-i, n-i+1), f(n, m, (m-1)%(n-i+1), n-i+2));
            a[p]=1;
            p=(p+1)%n;
        }
    }
}

/*

3
10 2
13 10
30000 54321

*/
