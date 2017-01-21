#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;

struct Dinic
{
	struct edge
    {
		int t, c, r;
		edge(int _t, int _c, int _r): t(_t), c(_c), r(_r){}
	};
    
	vector<int> l;
	vector<vector<edge>> e;
	Dinic(int n) : e(n+1){}
    
	void add(int u, int v, int w)
    {
		e[u].push_back(edge(v, w, e[v].size()));
		e[v].push_back(edge(u, 0, e[u].size()-1));
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
				if( E.c>0 && l[E.t]>l[s]+1 )
                {
					l[E.t]=l[s]+1;
					Q.push(E.t);
				}
		}
        
		return l[t]<INF;
	}
    
	int dfs(int s, int t, int num)
    {
		if( s==t || num==0 )
            return num;
        
		int ans=0;
        
		for(edge& E : e[s])
			if( E.c>0 && l[s]+1==l[E.t] )
            {
				int flow=dfs(E.t, t, min(num, E.c));
				rev(E).c+=flow, ans+=flow;
				E.c-=flow, num-=flow;
			}
        
		return ans>0 ? ans : l[s]=0;
	}
    
	int operator()(int s, int t)
    {
		int ans=0, tmp=0;
        
		while( bfs(s, t) )
			while( (tmp=dfs(s, t, INF)) )
				ans+=tmp;
        
		return ans;
	}
};

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int s=0, t=(n<<1)|1;
    Dinic D(t+1);
    
    for(int i=1; i<=n; i++)
        D.add(n+i, i, INF);
    
    for(; m>0; m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        D.add(u, n+v, 1);
        D.add(v, n+u, 1);
    }
    
    for(; k>0; k--)
    {
        int u;
        scanf("%d", &u);
        D.add(s, u, 1);
        D.add(n+u, t, 1);
    }
    
    printf("%d\n", D(s, t)>>1);
}
