#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

void dfs(const vector<vector<int>>& e, vector<int>& d, int u, int p=0, int h=0)
{
    d[u]=h;
    
    for(int v : e[u])
        if( v!=p )
            dfs(e, d, v, u, h+1);
}

int main()
{
    int n, x, y=1, ans=0;
    scanf("%d%d", &n, &x);
    vector<vector<int>> e(n+1);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    vector<int> a(n+1), b(n+1);
    dfs(e, a, x);
    dfs(e, b, y);
    
    for(int i=1; i<=n; i++)
        if( a[i]<b[i] )
            ans=max(ans, b[i]);
    
    printf("%d\n", ans<<1);
}
