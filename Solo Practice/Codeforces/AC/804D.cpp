#include<cstdio>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;
typedef pair<int, int> data;

int bfs(const vector<vector<int>>& e, vector<int>& r, vector<int>& l, vector<int>& a, int s)
{
    a[s]=0;
    queue<data> Q;
    int u;
    
    for(Q.push(data(s, 0)); !Q.empty(); Q.pop())
    {
        u=Q.front().first;
        r[u]=s;
        
        for(int v : e[u])
        {
            if( v==Q.front().second )
                continue;
            
            a[v]=a[u]+1;
            Q.push(data(v, u));
        }
    }
    
    l[s]=a[u];
    return u;
}

double sol(const vector<vector<data>>& d, int u, int v, int l)
{
    int n=d[u].size()-1;
    int m=d[v].size()-1;
    double s=0;
    
    for(int i=0; i<n; i++)
    {
        int j=lower_bound(d[v].begin(), d[v].end(), data(l-d[u][i].first, 0))-d[v].begin();
        s+=j*(double)l;
        s+=d[v][j].second+(m-j)*(d[u][i].first+1.0);
    }
    
    return s/(n*(double)m);
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<vector<int>> e(n+1);
    vector<vector<data>> d(n+1);
    vector<int> r(n+1, 0), l(n+1), a(n+1), b(n+1);
    
    for(; m>0; m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    for(int i=1; i<=n; i++)
    {
        if( r[i]>0 )
            continue;
        
        int u=bfs(e, r, l, a, i);
        int v=bfs(e, r, l, a, u);
        int t=bfs(e, r, l, b, v);
    }
    
    for(int i=1; i<=n; i++)
        d[ r[i] ].push_back(data(max(a[i], b[i]), i));
    
    for(int i=1; i<=n; i++)
    {
        sort(d[i].begin(), d[i].end());
        d[i].push_back(data(INF, 0));
        
        for(int j=d[i].size()-2; j>=0; j--)
            d[i][j].second=d[i][j].first+d[i][j+1].second;
    }
    
    for(map<data, double> M; k>0; k--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u=r[u];
        v=r[v];
        
        if( u==v )
            printf("-1\n");
        else
        {
            if( d[u].size()>d[v].size() )
                swap(u, v);
            
            if( M.find(data(u, v))==M.end() )
                M[data(u, v)]=sol(d, u, v, max(l[u], l[v]));
            
            printf("%f\n", M[data(u, v)]);
        }
    }
}
