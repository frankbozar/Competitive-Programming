#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct edge
{
    int u, v, w;
    
    inline void read()
    {
        char s[2];
        scanf("%d%d%s%d", &v, &u, s, &w);
        u+=v;
        v--;
        
        if( s[0]=='g' )
            w=-w, swap(u, v);
        
        w--;
    }
};

inline bool relax(const vector<edge>& e, vector<int>& d)
{
    bool any=false;
    
    for(const edge& E : e)
    {
        if( d[E.v]>d[E.u]+E.w )
        {
            d[E.v]=d[E.u]+E.w;
            any=true;
        }
    }
    
    return any;
}

bool solve(const vector<edge>& e, int n)
{
    vector<int> d(n+2, 0);
    
    for(int i=0; i<n; i++)
        if( !relax(e, d) )
            return false;
    
    return relax(e, d);
}

int main()
{
    for(int n; scanf("%d", &n) && n>0; )
    {
        int m;
        scanf("%d", &m);
        vector<edge> e(m);
        
        for(int i=0; i<m; i++)
            e[i].read();
        
        printf(solve(e, n) ? "successful conspiracy\n" : "lamentable kingdom\n");
    }
}

/*

4 2
1 2 gt 0
2 2 lt 2
1 2
1 0 gt 0
1 0 lt 0
0

*/