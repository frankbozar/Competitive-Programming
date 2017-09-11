#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

struct point
{
    int x, y, z;
    point(int _x=0, int _y=0, int _z=0) : x(_x), y(_y), z(_z){}
    
    bool operator<(const point& P) const
    {
        return x!=P.x ? x<P.x : y!=P.y ? y<P.y : z<P.z ;
    }
    
    void read()
    {
        scanf("%d%d%d", &x, &y, &z);
    }
};

struct djs
{
    set<point> S;
    vector<int> p;
    bool cyc=false;
    djs() : p(1<<20, -1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    void join(int x, int y)
    {
        point P(min(x, y), max(x, y));
        
        if( x==y || S.find(P)!=S.end() )
            return ;
        else
            S.insert(P);
        
        x=find(x);
        y=find(y);
        
        if( x==y )
            cyc=true;
        else
            p[x]=y;
    }
};


int main()
{
    int n;
    scanf("%d", &n);
    map<point, int> M, N;
    djs S, T;
    
    for(int i=0; i<n; i++)
    {
        point p, q;
        p.read();
        q.read();
        int u, v, s, t;
        
        if( M.find(p)!=M.end() )
            u=M[p];
        else
        {
            u=M.size();
            M[p]=u;
        }
        
        if( M.find(q)!=M.end() )
            v=M[q];
        else
        {
            v=M.size();
            M[q]=v;
        }
        
        p.z=q.z=0;
        
        if( N.find(p)!=N.end() )
            s=N[p];
        else
        {
            s=N.size();
            N[p]=s;
        }
        
        if( N.find(q)!=N.end() )
            t=N[q];
        else
        {
            t=N.size();
            N[q]=t;
        }
        
        S.join(u, v);
        T.join(s, t);
    }
    
    if( S.cyc )
        printf("True closed chains\n");
    else
        printf("No true closed chains\n");
    
    if( T.cyc )
        printf("Floor closed chains\n");
    else
        printf("No floor closed chains\n");
}

/*

4
12 12 8 10 5 11
12 12 8 4 14 21
12 12 8 12 20 8
4 14 21 10 5 21

4
1 1 1 2 2 2
2 2 2 1 5 5
9 4 4 9 4 2
9 4 4 9 9 4

3
50 50 50 100 100 100
100 100 100 50 50 90
50 50 90 50 50 50

3
1 1 5 1 3 7
1 3 7 4 4 5
4 4 5 1 1 5

*/
