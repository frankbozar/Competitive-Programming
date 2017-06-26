#include<cstdio>
#include<set>
#include<string>
#include<algorithm>
using namespace std;
const int N=64;
char s[N][N];

bool solve(int n)
{
    for(int k=0; k<2; k++)
    {
        int c[N]={0};
        set<string> S;
        
        for(int i=0; i<n; i++)
        {
            S.insert(s[i]);
            int p=0;
            
            for(int j=0; j<n; j++)
                p+=s[i][j]=='X';
            
            c[p]++;
        }
        
        if( c[1]!=1 || c[2]!=n-1 || S.size()!=(n+1)>>1 )
            return false;
        
        for(int i=0; i<n; i++)
            for(int j=i+1; j<n; j++)
                swap(s[i][j], s[j][i]);
    }
    
    return true;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n;
        scanf("%d", &n);
        
        for(int i=0; i<n; i++)
            scanf("%s", s[i]);
        
        printf("Case #%d: %s\n", cases, solve(n) ? "POSSIBLE" : "IMPOSSIBLE");
    }
}

/*

2

3
..X
XX.
XX.

3
...
XXX
XX.

*/
