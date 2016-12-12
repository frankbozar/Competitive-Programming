#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<40;

struct BF
{
    struct edge
    {
        int u, v, w;
        edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w){}
    };
    
    int n;
    vector<edge> e;
    BF(int _n) : n(_n){}
    
    void add(int u, int v, int w)
    {
        e.push_back(edge(u, v, w));
    }
    
    double karp_mmc()
    {
        vector<vector<lld>> d(n+1, vector<lld>(n, INF));
        d[0].assign(n, 0);
        
        for(int i=1; i<=n; i++)
            for(const edge& E : e)
                d[i][E.v]=min(d[i][E.v], d[i-1][E.u]+E.w);
        
        double ans=INF;
        
        for(int i=0; i<n; i++)
        {
            double tmp=-INF;
            
            if( d[n][i]>=INF )
                continue;
            
            for(int j=0; j<n; j++)
                tmp=max(tmp, (d[n][i]-d[j][i])/(double)(n-j));
            
            ans=min(ans, tmp);
        }
        
        return ans;
    }
};

int main()
{
    for(int ncase, cases=scanf("%d", &ncase); cases<=ncase; cases++)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        BF bf(n+1);
        
        for(; m>0; m--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            bf.add(u, v, w);
        }
        
        double ans=bf.karp_mmc();
        
        if( ans>=INF )
            printf("Case #%d: No cycle found.\n", cases);
        else
            printf("Case #%d: %.2f\n", cases, ans);
    }
}

/*

2

2 1
1 2 1

2 2
1 2 2
2 1 3

*/