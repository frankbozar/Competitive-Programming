#include<cstdio>
#include<map>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int N=1<<20, INF=1<<20;
char s[N], t[N];
#define edge pair<int,int>
#define v first
#define w second

struct mm
{
    int n;
    map<string, int> M;
    vector<vector<edge>> e;
    
    mm(int _n) : n(_n+1), e(_n+1)
    {
        M.clear();
        M["English"]=0;
    }
    
    int operator[](const string& s)
    {
        if( M.find(s)!=M.end() )
            return M[s];
        
        int t=M.size();
        return M[s]=t;
    }
    
    void add(const string& s, const string& t, int w)
    {
        int u=(*this)[s];
        int v=(*this)[t];
        e[u].push_back(edge(v, w));
        e[v].push_back(edge(u, w));
    }
    
    vector<int> bfs()
    {
        vector<int> d(n, INF);
        d[0]=0;
        queue<int> Q;
        
        for(Q.push(0); !Q.empty(); Q.pop())
        {
            int u=Q.front();
            
            for(const edge& E : e[u])
            {
                if( d[E.v]>d[u]+1 )
                {
                    d[E.v]=d[u]+1;
                    Q.push(E.v);
                }
            }
        }
        
        return d;
    }
    
    int solve()
    {
        vector<int> d=bfs();
        
        for(int i=0; i<n; i++)
            if( d[i]>=INF )
                return INF;
        
        int ans=0;
        
        for(int u=1; u<n; u++)
        {
            int tmp=INF;
            
            for(const edge& E : e[u])
                if( d[E.v]==d[u]-1 )
                    tmp=min(tmp, E.w);
            
            ans+=tmp;
        }
        
        return ans;
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    mm M(n);
    
    for(int i=0; i<n; i++)
    {
        scanf("%s", s);
        M[s];
    }
    
    for(; m>0; m--)
    {
        int w;
        scanf("%s%s%d", s, t, &w);
        M.add(s, t, w);
    }
    
    int ans=M.solve();
    
    if( ans>=INF )
        printf("Impossible\n");
    else
        printf("%d\n", ans);
}

/*

4 6
Pashto French Amheric Swedish
English Pashto 1
English French 1
English Amheric 5
Pashto Amheric 1
Amheric Swedish 5
French Swedish 1

2 1
A B
English B 1

*/
