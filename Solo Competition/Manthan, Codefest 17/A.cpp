#include<cstdio>
#include<set>
#include<string>
using namespace std;
char s[1<<20];

int main()
{
    int n;
    set<string> S;
    
    for(scanf("%d", &n); n>0; n--)
    {
        scanf("%s", s);
        printf(S.find(s)==S.end() ? "NO\n" : "YES\n");
        S.insert(s);
    }
}
