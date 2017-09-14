#include<cstdio>
#include<vector>
using namespace std;
const int N=1<<20;

int f(int x, bool p)
{
    static char s[N];
    
    if( x<0 )
        scanf("%s", s);
    else
        sprintf(s, "%d", x);
    
    int ans=0;
    
    for(int i=0; s[i]!='\0'; i++)
    {
        ans+=s[i]-'0';
        
        if( p && i )
            putchar('+');
        
        if( p )
            putchar(s[i]);
    }
    
    if( p )
        putchar('\n');
    
    return ans;
}

bool sol(const char* s, vector<int>& ans, int sum)
{
    if( *s=='\0' )
    {
        if( f(sum, false)>=10 )
            return false;
        
        for(int i=0; i<ans.size(); i++)
            printf(i==0 ? "%d" : "+%d", ans[i]);
        
        putchar('\n');
         
        f(sum, true);
        return true;
    }
    
    int v=*s-'0';
    ans.push_back(v);
    sum+=v;
    
    if( sol(s+1, ans, sum) )
        return true;
    
    ans.pop_back();
    sum+=ans.back()*9;
    ans.back()=ans.back()*10+v;
    return sol(s+1, ans, sum);
}

char s[N];

int main()
{
    
    scanf("%*d");
    int n=f(-1, true);
    sprintf(s, "%d", n);
    vector<int> ans(1, s[0]-'0');
    
    if( !sol(s+1, ans, ans.back()) )
        for(;;);
    
    /*
    for(int i=1; i<=1000; i++)
    {
        sprintf(s, "%d", i);
        vector<int> ans(1, s[0]-'0');
        
        if( !sol(s+1, ans, ans.back()) )
            printf("%d\n", i);
    }
     */
}
