#include<cstdio>

void sol(int n)
{
    if( n==0 )
    {
        printf("? / ? / ?\n");
        return ;
    }
    
    printf("a = ? max ?\n");
    
    for(char i='b'; i<='o'; i++)
        printf("%c = %c max %c\n", i, i-1, i-1);
    
    printf("p = o / o\n");
    
    for(char i='q'; i<='z'; i++)
        printf("%c = %c + %c\n", i, i-1, i-1);
    
    for(int init=1, i=0; n>0; n>>=1, i++)
    {
        if( n&1 )
        {
            if( !init )
                printf(" + ");
            
            init=0;
            printf("%c", i+'p');
        }
    }
    
    printf("\n");
}

int main()
{
    freopen("java2016.in", "rb", stdin);
    freopen("java2016.out", "wb", stdout);
    int n;
    scanf("%d", &n);
    sol(n);
}
