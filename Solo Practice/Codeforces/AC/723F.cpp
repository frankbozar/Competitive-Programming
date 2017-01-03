#include<cstdio>
#include<vector>
using namespace std;
#define edge pair<int,int>
#define u first
#define v second

struct set
{
    vector<int> p;
    set(int n) : p(n+1, -1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    bool join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x==y )
            return false;
        
        p[x]=y;
        return true;
    }
    
    bool same(int x, int y)
    {
        return find(x)==find(y);
    }
};

int main()
{
    int n, m, u, v, p, q;
    scanf("%d%d", &n, &m);
    vector<edge> e(m), ans;
    set S(n+1);
    
    for(edge& E : e)
        scanf("%d%d", &E.u, &E.v);
    
    scanf("%d%d%d%d", &u, &v, &p, &q);
    
    for(const edge& E : e)
        if( u!=E.u && u!=E.v && v!=E.u && v!=E.v && S.join(E.u, E.v) )
            ans.push_back(E);
    
    vector<int> U(n+1, 0), V(n+1, 0);
    
    for(const edge& E : e)
    {
        if( E==edge(u, v) || E==edge(v, u) )
            continue;
        else if( u==E.u || u==E.v )
            U[S.find(E.u+E.v-u)]=E.u+E.v-u;
        else if( v==E.u || v==E.v )
            V[S.find(E.u+E.v-v)]=E.u+E.v-v;
    }
    
    vector<int> c;
    
    for(int i=1; i<=n; i++)
    {
        if( U[i] && V[i] )
            c.push_back(i);
        else if( U[i] )
        {
            p--;
            ans.push_back(edge(u, U[i]));
        }
        else if( V[i] )
        {
            q--;
            ans.push_back(edge(v, V[i]));
        }
    }
    
    if( p<=0 || q<=0 )
    {
        printf("No\n");
        return 0;
    }
    
    if( c.empty() )
        ans.push_back(edge(u, v));
    else
    {
        int k=c.size(), i=0;
        
        if( p+q<k+1 )
        {
            printf("No\n");
            return 0;
        }
        
        for(; i<min(k, p); i++)
            ans.push_back(edge(u, U[ c[i] ]));
        
        for(i--; i<k; i++)
            ans.push_back(edge(v, V[ c[i] ]));
    }
    
    printf("Yes\n");
    
    for(const edge& E : ans)
        printf("%d %d\n", E.u, E.v);
}
