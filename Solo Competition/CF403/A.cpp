#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

void dfs(const vector<vector<int>>& e, vector<int>& c, int& ans, int u=1, int p=0)
{
    int col=1;
    
    for(int v : e[u])
    {
        if( v==p )
            continue;
        
        while( col==c[u] || col==c[p] )
            col++;
        
        ans=max(ans, c[v]=col++);
    }
    
    for(int v : e[u])
        if( v!=p )
            dfs(e, c, ans, v, u);
}

int main()
{
    int n, ans=0;
    scanf("%d", &n);
    vector<vector<int>> e(n+1);
    vector<int> c(n+1, 0);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    c[1]=1;
    dfs(e, c, ans);
    printf("%d\n", ans);
    
    for(int i=1; i<=n; i++)
        printf(i==n ? "%d\n" : "%d ", c[i]);
}
