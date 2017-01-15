#include<cstdio>
#include<string>
#include<set>
using namespace std;
char s[1024];

bool solve(int n, int m , int k)
{
    n-=k;
    m-=k;
    n+=k-(k>>1);
    m+=k>>1;
    return n>m;
}

int main()
{
    int n, m, k=0;
    scanf("%d%d", &n, &m);
    set<string> S;
    
    for(int i=0; i<n; i++)
    {
        scanf("%s", s);
        S.insert(s);
    }
    
    for(int i=0; i<m; i++)
    {
        scanf("%s", s);
        
        if( S.find(s)!=S.end() )
            k++;
    }
    
    printf(solve(n, m, k) ? "YES\n" : "NO\n");
}
