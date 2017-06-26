#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=64;

void solve(char s[N], char t[N])
{
    int n=strlen(s);
    t[1]=s[0];
    
    for(int i=3; i<n; i+=2)
    {
        int d=s[i-1]-t[i-2];
        
        if( d<0 )
            d+=26;
        
        t[i]=d+'A';
    }
    
    t[n-2]=s[n-1];
    
    for(int i=n-4; i>=0; i-=2)
    {
        int d=s[i+1]-t[i+2];
        
        if( d<0 )
            d+=26;
        
        t[i]=d+'A';
    }
    
    if( n&1 )
        sprintf(t, "AMBIGUOUS");
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        char s[N]={0}, t[N]={0};
        scanf("%s", s);
        solve(s, t);
        printf("Case #%d: %s\n", cases, t);
    }
}

/*

3
OMDU
BCB
AOAAAN

*/
