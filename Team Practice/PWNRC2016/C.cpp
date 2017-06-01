#include<cstdio>
#include<cstring>
const int N=1<<20;
char s[N], t[N];

int main()
{
    scanf("%s%s", s, t);
    int n=strlen(s), m=strlen(t);
    
    for(int i=0; i<n; i++)
    {
        int d=s[i]-t[i];
        
        if( d<0 )
            d+=26;
        
        d+='A';
        putchar(d);
        t[m++]=d;
    }
    
    putchar('\n');
}
