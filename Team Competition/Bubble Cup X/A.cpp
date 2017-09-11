#include<cstdio>
#include<cstring>
char s[1<<20]={0};

int f(int x=-1)
{
    if( x<0 )
        scanf("%*d%s", s);
    else
        sprintf(s, "%d", x);
    
    int n=strlen(s), sum=0;
    
    for(int i=0; i<n; i++)
    {
        if( i>0 )
            putchar('+');
        
        putchar(s[i]);
        sum+=s[i]-'0';
    }
    
    putchar('\n');
    return sum;
}

int main()
{
    f(f(f()));
}
