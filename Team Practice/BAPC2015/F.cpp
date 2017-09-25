#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
typedef pair<int, int> data;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m, k, ans=0;
        scanf("%d%d%d", &n, &m, &k);
        vector<int> d(n+1, 0), p(n+1, -1), h(n+1, -1);
        vector<vector<int>> c(n+1), e(n+1);
        
        for(; m>0; m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
            d[u]++;
            d[v]++;
        }
        
        queue<int> Q;
        
        for(int i=1; i<=n; i++)
        {
            if( d[i]==1 )
            {
                h[i]=1;
                Q.push(i);
            }
        }
        
        for(; !Q.empty(); Q.pop())
        {
            int u=Q.front();
            d[u]=0;
            ans++;
            
            for(int v : e[u])
            {
                if( d[v]!=0 )
                {
                    if( --d[v]==1 )
                        Q.push(v);
                    
                    p[u]=v;
                    c[v].push_back(u);
                    h[v]=max(h[v], h[u]+1);
                }
            }
        }
        
        priority_queue<data> PQ;
        
        for(int i=1; i<=n; i++)
            if( h[i]>0 && p[i]<0 )
                PQ.push(data(h[i]-1, i));
        
        for(; !PQ.empty() && k>0; k--)
        {
            int u=PQ.top().second;
            ans-=PQ.top().first;
            PQ.pop();
            
            while( !c[u].empty() )
            {
                int v=0;
                
                for(int x : c[u])
                    if( h[v]<h[x] )
                        v=x;
                
                for(int x : c[u])
                    if( x!=v )
                        PQ.push(data(h[x], x));
                
                u=v;
            }
        }
        
        printf("%d\n", ans);
    }
}

/*

2
6 6 1
1 2
2 3
1 3
1 4
4 5
1 6

11 11 3
1 2
2 3
1 3
1 4
4 5
2 6
3 7
7 8
7 9
8 10
9 11

*/
