#include<cstdio>
const int N=20000;

bool check()
{
    int p=0, n;
    
    for(scanf("%d", &n); n>0; n--)
    {
        int d;
        char s[8]={0};
        scanf("%d%s", &d, s);
        
        if( p==0 && s[0]!='S' )
            return false;
        else if( p==N && s[0]!='N' )
            return false;
        else if( s[0]=='S' && (p+=d)>N )
            return false;
        else if( s[0]=='N' && (p-=d)<0 )
            return false;
    }
    
    return p==0;
}

int main()
{
    printf(check() ? "YES\n" : "NO\n");
}
