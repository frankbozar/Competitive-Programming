#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
typedef pair<lld,int> data;
const lld INF=1LL<<60;

struct edge
{
    int t, c, l, o;
};

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<vector<edge>> e(n+1);
        
        for(; m>0; m--)
        {
            int s, t, c, l, o;
            scanf("%d%d%d%d%d", &s, &t, &c, &l, &o);
            e[s].push_back({t, c, l, o});
        }
        
        vector<lld> d(n+1, INF);
        d[0]=0;
        priority_queue<data> PQ;
        
        for(PQ.push({0, 0}); !PQ.empty(); )
        {
            int u=PQ.top().second;
            lld w=-PQ.top().first;
            PQ.pop();
            
            if( d[u]<w )
                continue;
            
            for(const edge& E : e[u])
            {
                w=d[u]+d[u]/E.c*E.l+E.o;
                
                if( d[E.t]>w )
                {
                    d[E.t]=w;
                    PQ.push({-w, E.t});
                }
            }
        }
        
        printf("%lld\n", d[n]);
    }
}

/*

1
3 3
0 1 1 0 2
1 2 1 0 1
2 3 1 0 1

*/
