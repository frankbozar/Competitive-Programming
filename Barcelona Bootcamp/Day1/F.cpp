#include<cstdio>
#include<cstring>
char s[1<<20]={0};
/*
bool solve(int l, int r, bool d=true)
{
    printf("%d %d %d\n", l, r, d ? 1 : 0);
    
    if( s[l]=='C' && s[r]=='C' )
    {
        return !d;
    }
    else if( s[l]=='C' )
    {
        while( s[r-1]==s[r] )
            r--;
        
        return (s[r]!='A') ^ (s[r-1]=='C') ^ !d ;
        
    }
    else if( s[r]=='C' )
    {
        while( s[l+1]==s[l] )
            l++;
        
        return (s[l]!='A') ^ (s[l+1]=='C') ^ !d ;
        
    }
    else if( s[l]==s[r] )
    {
        return (s[l]!='A') ^ !d ;
    }
    else
    {
        while( s[l+1]==s[l] && s[r-1]==s[r] )
            l++, r--;
        
        return solve(l+1, r-1, !d);
    }
}
*/

bool solve()
{
    int n=strlen(s);
    int c=strchr(s, 'C')-s;
    
    if( c==0 )
        return s[n-1]!='A';
    else if( c==n-1 )
        return s[0]!='A';
    else if( s[0]==s[n-1] )
        return s[0]!='A';
    
    int t='A';
    
    for(int l=c-1, r=c+1; l>=0 && r<n; )
    {
        if( s[0]==t && s[l]==t )
            l--;
        else if( s[n-1]==t && s[r]==t )
            r++;
        else if( s[l]==t )
            l--;
        else if( s[r]==t )
            r++;
        
        t=-t+'A'+'B';
    }
    
    return t=='B';
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        scanf("%s", s);
        printf(solve() ? "Apfelmann\n" : "Bananenfrau\n");
    }
}

/*

3
AAACBB
CABAB
BBBBCBA

*/
