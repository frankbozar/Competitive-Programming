#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=10;

int C(int n, int m)
{
    return n==m || m==0 ? 1 : C(n-1, m)+C(n-1, m-1);
}

int perm(int n, int x)
{
    return x==0 ? 1 : perm(n-x%N, x/N)*C(n, x%N);
}

int dsum(const char* s)
{
    return *s ? dsum(s+1)+*s-'0' : 0;
}

int dsum(int x)
{
    return x ? dsum(x/N)+x%N : 0;
}

int solve(int n, int x)
{
    if( dsum(x)>n )
        return 1;
    
    char s[N]={0};
    
    for(int d=n+1, c=n-1, t=x; t>0; t/=N)
        for(d--; t%N>0;t--)
            s[c--]=d;
    
    for(int i=0; i<n; i++)
        s[i]+='0';
    
    if( dsum(s)>n )
        return perm(n, x)+1;
    
    int ans=1;
    
    do{
        int y=atoi(s);
        
        if( y!=x )
            ans+=solve(n, y);
    }while( next_permutation(s, s+n) );
    
    return ans;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        char s[N]={0};
        scanf("%s", s);
        printf("Case #%d: %d\n", cases, solve(strlen(s), atoi(s)));
    }
}
