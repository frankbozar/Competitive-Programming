#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

struct dinic
{
    struct edge
    {
        int t, c, r, o;
        edge(int _t, int _c, int _r, int _o) : t(_t), c(_c), r(_r), o(_o){}
    };
    
    vector<int> l;
    vector<vector<edge>> e;
    dinic(int n) : e(n+1){}
    
    void add(int u, int v, int w)
    {
        e[u].push_back(edge(v, w, e[v].size(), 1));
        e[v].push_back(edge(u, 0, e[u].size()-1, 0));
    }
    
    edge& rev(const edge& E)
    {
        return e[E.t][E.r];
    }
    
    bool bfs(int s, int t)
    {
        l.assign(e.size(), INF);
        l[s]=1;
        queue<int> Q;
        
        for(Q.push(s); !Q.empty(); Q.pop())
        {
            s=Q.front();
            
            for(const edge& E : e[s])
            {
                if( l[E.t]>l[s]+1 && E.c>0 )
                {
                    l[E.t]=l[s]+1;
                    Q.push(E.t);
                }
            }
        }
        
        return l[t]<INF;
    }
    
    int dfs(int s, int t, int num=INF)
    {
        if( s==t || num==0 )
            return num;
        
        int ans=0;
        
        for(edge& E : e[s])
        {
            if( l[E.t]==l[s]+1 )
            {
                int flow=dfs(E.t, t, min(E.c, num));
                rev(E).c+=flow;
                E.c-=flow;
                ans+=flow;
                num-=flow;
            }
        }
        
        return ans>0 ? ans : l[s]=0;
    }
    
    int operator()(int s, int t)
    {
        int ans=0, tmp;
        
        while( bfs(s, t) )
            while( (tmp=dfs(s, t)) )
                ans+=tmp;
        
        return ans;
    }
};

int id(int x, int y, int n, int k, int t)
{
    return n*n*k+n*x+y+t;
}

bool valid(int x, int y, int n)
{
    return 0<=x && x<n && 0<=y && y<n ;
}

const int step[5][2]={{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {0, 0}};

int main()
{
    for(int n, m, k; scanf("%d%d%d", &n, &m, &k) && (n||m||k); )
    {
        vector<vector<int>> a(n, vector<int>(n));
        
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%d", &a[i][j]);
        
        dinic D(n*n*(k+1)*2+2);
        int s=n*n*(k+1)*2;
        int t=n*n*(k+1)*2+1;
        
        for(int i=0; i<m; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            D.add(s, id(x, y, n, 0, n*n*(k+1)), 1);
        }
        
        for(int x=0; x<n; x++)
            for(int y=0; y<n; y++)
                D.add(id(x, y, n, k, n*n*(k+1)), t, 1);
        
        for(int i=1; i<=k; i++)
        {
            int h;
            scanf("%d", &h);
            
            for(int x=0; x<n; x++)
                for(int y=0; y<n; y++)
                {
                    if( a[x][y]<=h )
                        continue;
                    
                    D.add(id(x, y, n, i, 0), id(x, y, n, i, n*n*(k+1)), 1);
                    
                    for(int d=0; d<5; d++)
                    {
                        int dx=x+step[d][0];
                        int dy=y+step[d][1];
                        
                        if( valid(dx, dy, n) )
                            D.add(id(dx, dy, n, i-1, n*n*(k+1)), id(x, y, n, i, 0), 1);
                    }
                }
        }
        
        printf("%d\n", D(s, t));
    }
}

/*

3 1 3
2 1 2
3 1 3
2 4 2
1 1
0 2 1

3 2 3
1 2 1
2 3 4
1 4 1
1 0
0 1
1 2 3

3 2 3
1 2 1
2 3 4
1 4 1
1 0
0 1
2 3 3

3 2 1
1 2 1
2 3 4
1 4 1
1 0
0 1
2

2 2 1
1 2
2 3
0 1
1 0
2

0 0 0

*/
