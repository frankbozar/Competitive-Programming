#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
char s[1<<21];
const char b='|';

int solve()
{
    int n=strlen(s), ans=n-1;
    
    for(int i=n-1; i>=0; i--)
    {
        s[(i<<1)|1]=s[i];
        s[(i+1)<<1]=b;
    }
    
    s[0]=b;
    s[(n<<1)|1]='\0';
    vector<int> p((n+1)<<1, 1);
    
    for(int l=(n<<1)|1, c=0, r=0, n=0, m=0, i=1; i<l; i++)
    {
        int j=(c<<1)-i;
        
        if( i>r )
            p[i]=0, n=i+1, m=i-1;
        else if( p[j]<r-i )
            p[i]=p[j], m=-1;
        else
            p[i]=r-i, n=r+1, m=(i<<1)-n;
        
        while( n<l && m>=0 && s[m]==s[n] )
            p[i]++, n++, m--;
        
        if( i+p[i]>r )
            c=i, r=i+p[i];
        
        if( p[i]==i )
            ans=min(ans, (l>>1)-p[i]);
    }
    
    return ans;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        scanf("%s", s);
        printf("%d\n", solve());
    }
}

/*

4
aacecaaa
abcd
aba
abbacd

*/
