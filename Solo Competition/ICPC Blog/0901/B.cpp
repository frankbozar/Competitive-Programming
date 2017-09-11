#include<cstdio>
const int N=10032;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    if( m>n*n || m<n+n-1 )
    {
        printf("Impossible\n");
        return 0;
    }
    
    int pos=0;
    int id=N;
    
    for(int left=n; m>n+left-1; m--)
    {
        if( pos==0 )
            left--;
        
        printf("%d\n", id);
        pos++;
        
        if( pos==n )
        {
            pos=0;
            id++;
        }
    }
    
    if( pos!=0 )
        id++;
    
    for(; m>n; m--)
        printf("%d\n", id++);
    
    for(int i=0; i<n; i++)
        printf("%d\n", id);
}
