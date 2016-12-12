#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const double INF=1e10;
const double EPS=1e-8;

struct BF
{
    struct edge
    {
        int u, v, w;
        edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w){}
    };
    
    int n;
    vector<edge> e;
    vector<double> d;
    BF(int _n) : n(_n){}
    
    void add(int u, int v, int w)
    {
        e.push_back(edge(u, v, w));
    }
    
    bool relax(const double r)
    {
        bool any=false;
        
        for(const edge& E : e)
            if( d[E.v]>d[E.u]+E.w-r )
            {
                d[E.v]=d[E.u]+E.w-r;
                any=true;
            }
        
        return any;
    }
    
    bool neg_cycle(const double x)
    {
        d.assign(n, 0);
        
        for(int i=0; i<n; i++)
            if( !relax(x) )
                return false;
        
        return relax(x);
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
        
        double ans=INF;
        
        for(double l=-INF, r=INF; r-l>EPS; )
        {
            double m=(l+r)/2;
            
            if( bf.neg_cycle(m) )
                ans=r=m;
            else
                l=m;
        }
        
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