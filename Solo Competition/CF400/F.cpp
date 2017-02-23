#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

struct edge
{
    int u, v;
    edge(int _u, int _v) : u(min(_u, _v)), v(max(_u, _v)){}
    
    bool operator<(const edge& E) const
    {
        return u==E.u ? v<E.v : u<E.u ;
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<set<int>> a(n+1);
    map<edge, int> E;
    
    for(int i=1; i<=n; i++)
    {
        int u=i, v=i%n+1;
        E[edge(u, v)]=0;
        a[u].insert(v);
        a[v].insert(u);
    }
    
    for(; m>0; m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        E[edge(u, v)]=0;
        a[u].insert(v);
        a[v].insert(u);
    }
    
    vector<vector<int>> b;
    
    for(int i=1; i<=n; i++)
    {
        if( a[i].empty() )
            continue;
        
        vector<int> t;
        set<int> used;
        
        for(int u=i; used.find(u)==used.end(); )
        {
            int v;
            
            for(auto it=a[u].begin(); it!=a[u].end(); ++it)
                if( used.find(*it)==used.end() )
                {
                    v=*it;
                    break;
                }
            
            if( ++E[edge(u, v)]== (u%n+1==v || v%n+1==u) ? 1 : 2 )
            {
                a[u].erase(v);
                a[v].erase(u);
            }
            
            u=v;
            used.insert(u);
        }
        
        b.push_back(vector<int>(used.begin(), used.end()));
        
        
        for(int x : b.back())
            printf("%d ", x);
        printf("\n");
    }
}
