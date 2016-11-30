#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;
vector<int> d;
vector<vector<int>> a, e, f;
vector<bool> A, B;

int solve(int u=1)
{
    int ans=INF;
    
    for(int v : e[u])
    {
        ans=min(ans, solve(v));
        a[u][0]=min(a[u][0], a[v][0]+1);
        a[u][1]=min(a[u][1], a[v][1]+1);
    }
    
    if( A[u] )
        a[u][0]=0;
    
    if( B[u] )
        a[u][1]=0;
    
    ans=min(ans, d[u]+a[u][0]+a[u][1]);
    return ans;
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    e.resize(n+1);
    f.resize(n+1);
    A.assign(n+1, false);
    B.assign(n+1, false);
    
    for(int i=0; i<m; i++)
    {
        int x;
        scanf("%d", &x);
        A[x]=true;
    }
    
    for(int i=0; i<k; i++)
    {
        int x;
        scanf("%d", &x);
        B[x]=true;
    }
    
    for(int i=1; i<=n; i++)
    {
        int l;
        scanf("%d", &l);
        f[i].resize(l);
        
        for(int j=0; j<l; j++)
            scanf("%d", &f[i][j]);
    }
    
    queue<int> Q;
    d.assign(n+1, INF);
    d[1]=0;
    
    for(Q.push(1); !Q.empty(); Q.pop())
    {
        int u=Q.front();
        
        for(int v : f[u])
        {
            if( d[v]>d[u]+1 )
            {
                d[v]=d[u]+1;
                Q.push(v);
            }
            
            if( d[v]==d[u]+1 )
                e[u].push_back(v);
        }
    }
    
    a.assign(n+1, vector<int>(2, INF));
    int ans=solve();
    
    if( ans>=INF )
        printf("impossible\n");
    else
        printf("%d\n", ans);
}

/*

3 1 1
2
3
1 2
2 3 1
1 1

3 1 1
2
3
1 2
1 1
2 1 2

*/