#include<cstdio>
#include<stack>
#include<vector>
using namespace std;
vector<vector<int>> edg;
vector<int> dfn, low, com;
stack<int> S;
int d;
bool ans;

void scc(int u)
{
    dfn[u]=low[u]=++d;
    S.push(u);
    
    for(int v : edg[u])
    {
        if( !dfn[v] )
            scc(v);
        
        if( !com[v] )
            low[u]=min(low[u], low[v]);
    }
    
    if( dfn[u]==low[u] )
    {
        for(bool flag=true; flag; S.pop())
        {
            (S.top()==u ? flag : ans)=false;
            com[S.top()]=u+1;
        }
    }
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        edg.clear();
        edg.resize(n+1);
        dfn.assign(n+1, 0);
        low.assign(n+1, 0);
        com.assign(n+1, 0);
        d=0;
        ans=true;
        
        for(; m>0; m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            edg[u].push_back(v);
            
            if( u==v )
                ans=false;
        }
        
        for(int i=1; i<=n; i++)
            if( !dfn[i] )
                scc(i);
        
        printf(ans ? "VALID\n" : "INVALID\n");
    }
}

/*

1
4 5
1 3
2 3
2 4
3 4
4 3

*/
