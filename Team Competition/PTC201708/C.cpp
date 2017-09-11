#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
typedef long long lld;

lld C(int n, int m)
{
    if( m<0 || n<m )
        return 0;
    else if( m==0 || n==m )
        return 1;
    
    static vector<vector<lld>> c(32, vector<lld>(32, -1));
    
    if( c[n][m]<0 )
        c[n][m]=C(n-1, m-1)+C(n-1, m);
    
    return c[n][m];
}

vector<int> count(const char* s)
{
    vector<int> c(26, 0);
    
    for(; *s; s++)
        c[*s-'a']++;
    
    return c;
}

lld solve(const vector<int>& c)
{
    int n=0;
    
    for(int x : c)
        n+=x;
    
    lld ans=1;
    
    for(int x : c)
    {
        ans*=C(n, x);
        n-=x;
    }
    
    return ans;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        char s[32]={0};
        scanf("%s", s);
        int n=strlen(s);
        vector<int> c=count(s);
        lld ans=0;
        
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<s[i]-'a'; j++)
            {
                if( c[j]==0 )
                    continue;
                
                c[j]--;
                ans+=solve(c);
                c[j]++;
            }
            
            c[ s[i]-'a' ]--;
        }
        
        printf("%lld\n", ans);
    }
}

/*

5
abc
success
failure
aaaaaaaaaaaaaaaaaaaa
tsrqponmlkjihgfedcba

*/
