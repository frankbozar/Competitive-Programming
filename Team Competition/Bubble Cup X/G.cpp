#include<cstdio>
#include<map>
#include<set>
#include<string>
using namespace std;

void sol(set<string>& S, const string& s, const char* t)
{
    if( *t=='\0' )
    {
        S.insert(s);
        return ;
    }
    else if( *t!='?' )
    {
        sol(S, s+*t, t+1);
        return ;
    }
    
    sol(S, s, t+1);
    
    for(char c='a'; c<='e'; c++)
        sol(S, s+c, t+1);
}

int main()
{
    char s[128];
    int n, m;
    scanf("%d%d", &n, &m);
    map<string, int> M;
    
    for(; n>0; n--)
    {
        scanf("%s", s);
        M[s]++;
    }
    
    for(; m>0; m--)
    {
        scanf("%s", s);
        set<string> T;
        sol(T, "", s);
        int ans=0;
        
        for(const string& t : T)
            ans+=M[t];
        
        printf("%d\n", ans);
    }
}
