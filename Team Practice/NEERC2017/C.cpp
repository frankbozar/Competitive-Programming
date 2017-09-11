#include<cstdio>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
#define data pair<int,int>
#define r first
#define i second
vector<vector<int>> e;
vector<int> dfn, low, com, siz, deg, ans;
stack<int> S;

void dfs(int u, int d=0)
{
    dfn[u]=low[u]=++d;
    S.push(u);
    
    for(int v : e[u])
    {
        if( !dfn[v] )
            dfs(v, d);
        
        if( !com[v] )
            low[u]=min(low[u], low[v]);
    }
    
    if( d==low[u] )
    {
        for(bool flag=true; flag; S.pop())
        {
            flag=S.top()!=u;
            com[S.top()]=u+1;
        }
    }
}

int main()
{
    freopen("codecoder.in", "rb", stdin);
    freopen("codecoder.out", "wb", stdout);
    int n;
    scanf("%d", &n);
    vector<data> a, b;
    
    for(int i=0; i<n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        a.push_back(data(x, i));
        b.push_back(data(y, i));
    }
    
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    e.resize(n);
    dfn.assign(n, 0);
    low.assign(n, 0);
    com.assign(n, 0);
    
    for(int i=1; i<n; i++)
    {
        e[ a[i-1].i ].push_back(a[i].i);
        e[ b[i-1].i ].push_back(b[i].i);
    }
    
    for(int i=0; i<n; i++)
        if( !dfn[i] )
            dfs(i);
    
    e.clear();
    e.resize(n);
    siz.assign(n, 0);
    deg.assign(n, 0);
    ans.assign(n, 0);
    
    for(int i=0; i<n; i++)
    {
        com[i]--;
        siz[ com[i] ]++;
    }
    
    for(int i=1; i<n; i++)
    {
        if( com[ a[i].i ]!=com[ a[i-1].i ] )
        {
            e[ com[ a[i].i ] ].push_back(com[ a[i-1].i ]);
            deg[ com[ a[i-1].i ] ]++;
        }
        
        if( com[ b[i].i ]!=com[ b[i-1].i ] )
        {
            e[ com[ b[i].i ] ].push_back(com[ b[i-1].i ]);
            deg[ com[ b[i-1].i ] ]++;
        }
    }
    
    queue<int> Q;
    
    for(int i=0; i<n; i++)
        if( i==com[i] && deg[i]==0 )
            Q.push(i);
    
    for(int sum=0; !Q.empty(); Q.pop())
    {
        int u=Q.front();
        sum+=siz[u];
        ans[u]=sum;
        
        for(int v : e[u])
            if( --deg[v]==0 )
                Q.push(v);
    }
    
    for(int i=0; i<n; i++)
        printf("%d\n", ans[ com[i] ]-1);
}
