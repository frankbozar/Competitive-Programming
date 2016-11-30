#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;

int solve(const vector<int>& d, const vector<vector<int>>& f,
          const vector<bool>& A, const vector<bool>& B,
          vector<vector<int>>& a, int u=1)
{
    int ans=INF;
    
    for(int v : f[u])
    {
        ans=min(ans, solve(d, f, A, B, a, v));
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
    vector<vector<int>> e(n+1), f(n+1);
    vector<bool> A(n+1, false), B(n+1, false);
    
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
        e[i].resize(l);
        
        for(int j=0; j<l; j++)
            scanf("%d", &e[i][j]);
    }
    
    queue<int> Q;
    vector<int> d(n+1, INF);
    d[1]=0;
    
    for(Q.push(1); !Q.empty(); Q.pop())
    {
        int u=Q.front();
        
        for(int v : e[u])
        {
            if( d[v]>d[u]+1 )
            {
                d[v]=d[u]+1;
                Q.push(v);
            }
            
            if( d[v]==d[u]+1 )
                f[u].push_back(v);
        }
    }
    
    vector<vector<int>> a(n+1, vector<int>(2, INF));
    int ans=solve(d, f, A, B, a);
    
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