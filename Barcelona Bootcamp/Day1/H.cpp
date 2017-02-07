#include<cstdio>

int main()
{
    int n;
    scanf("%d", &n);
    
    if( n<4 )
        printf("-1\n");
    else
    {
        printf("4 2 3 1");
        
        for(int i=5; i<=n; i++)
            printf(" %d", i);
        
        printf("\n");
    }
}
