#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;

vector<int> bfs(const vector<vector<int>>& e, queue<int>& Q)
{
    vector<int> d(e.size(), INF);
    
    for(; !Q.empty(); Q.pop())
    {
        int u=Q.front();
        
        if( d[u]>=INF )
            d[u]=0;
        
        for(int v : e[u])
        {
            if( d[v]>d[u]+1 )
            {
                d[v]=d[u]+1;
                Q.push(v);
            }
        }
    }
    
    return d;
}

int main()
{
    int n, m, k, ans=INF;
    scanf("%d%d%d", &n, &m, &k);
    vector<vector<int>> e(n+1), f(n+1);
    queue<int> A, B, C;
    
    for(; m>0; m--)
    {
        int x;
        scanf("%d", &x);
        B.push(x);
    }
    
    for(; k>0; k--)
    {
        int x;
        scanf("%d", &x);
        C.push(x);
    }
    
    for(int i=1; i<=n; i++)
    {
        int l;
        
        for(scanf("%d", &l); l>0; l--)
        {
            int j;
            scanf("%d", &j);
            e[i].push_back(j);
            f[j].push_back(i);
        }
    }
    
    A.push(1);
    vector<int> a=bfs(e, A);
    vector<int> b=bfs(f, B);
    vector<int> c=bfs(f, C);
    
    for(int i=1; i<=n; i++)
        ans=min(ans, a[i]+b[i]+c[i]);
    
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