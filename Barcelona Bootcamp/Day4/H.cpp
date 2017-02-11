#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, s, t, maxh=0;
        scanf("%d%d%d", &n, &s, &t);
        vector<vector<int>> e(n+1);
        
        for(int i=1; i<n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        
        vector<int> path(n+1, 0), depth(n+1, INF), used(n+1, 0), pred(n+1, -1), branch(n+1, -1);
        depth[t]=0;
        queue<int> Q;
        
        for(Q.push(t); !Q.empty(); Q.pop())
        {
            int u=Q.front();
            maxh=max(maxh, depth[u]);
            
            for(int v : e[u])
            {
                if( depth[v]>depth[u]+1 )
                {
                    depth[v]=depth[u]+1;
                    pred[v]=u;
                    Q.push(v);
                }
            }
        }
        
        if( s==t )
        {
            printf("%d\n", maxh);
            continue;
        }
        
        int a=0, b=0;
        
        for(int u=s; u!=t; u=pred[u])
        {
            path[u]=1;
            a++;
        }
        
        for(Q.push(t); !Q.empty(); Q.pop())
        {
            int u=Q.front();
            b=max(b, depth[u]);
            branch[u]=1;
            
            for(int v : e[u])
            {
                if( path[v] )
                    branch[v]=0;
                else if( branch[v]<0 )
                    Q.push(v);
            }
        }
        
        vector<pair<int, int>> val;
        
        for(int i=1; i<=n; i++)
            if( branch[i]!=1 )
            {
                val.push_back({depth[i], i});
                
                if( !path[i] )
                    b=max(b, depth[i]);
            }
        
        sort(val.rbegin(), val.rend());
        int m=val.size(), node=0;
        val.push_back({0, 0});
        int ans=a+b;
        
        for(int i=0; i<m; i++)
        {
            for(int u=val[i].second; u>0 && !used[u]; u=pred[u])
            {
                used[u]=1;
                node++;
            }
            
            ans=min(ans, node*2-a+val[i+1].first);
        }
        
        printf("%d\n", ans);
    }
}

/*

1
4 2 3
1 2
1 3
1 4

*/
