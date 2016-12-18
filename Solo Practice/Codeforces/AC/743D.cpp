#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;

struct data
{
    lld a, m, s;
};

data dfs(const vector<int>& w, const vector<vector<int>>& e, int u=1, int p=0)
{
    lld a=-INF, x=-INF, y=-INF, s=w[u];
    
    for(const int v : e[u])
    {
        if( v==p )
            continue;
        
        data tmp=dfs(w, e, v, u);
        a=max(a, tmp.a);
        s+=tmp.s;
        
        if( y<tmp.m )
            y=tmp.m;
        
        if( x<y )
            swap(x, y);
    }
    
    if( y>-INF )
        a=max(a, x+y);
    
    return {a, max(x, s), s};
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<vector<int>> e(n+1);
    vector<int> w(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &w[i]);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    lld ans=dfs(w, e).a;
    
    if( ans<=-INF )
        printf("Impossible\n");
    else
        printf("%lld\n", ans);
}