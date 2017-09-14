#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
using namespace std;

const int N=1000;

vector<vector<int>> edg;
vector<int> dfn, low, com, siz, in;
stack<int> S;
int d;
void scc(int u)
{
    dfn[u]=low[u]=++d;
    S.push(u);
    for(int v: edg[u])
    {

        if(!dfn[v])
            scc(v);
        if(!com[v])
            low[u]=min(low[u], low[v]);
    }
    if(low[u]==dfn[u])
    {
        for(int flag=1; flag; )
        {
            flag=S.top()!=u;
            com[S.top()]=u+1;
            S.pop();
        }

    }

}



int main()
{
    int T;

    for(scanf("%d", &T); T>0; T--)
    {
        int n;
        scanf("%d", &n);
        edg.clear();
        edg.resize(n);
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                int t;
                scanf("%d", &t);
                if(t==1)
                {
                    edg[i].push_back(j);
                }

            }
        }
        dfn=low=com=siz=in=vector<int>(n+1, 0);
        d=0;
        for(int i=0; i<n; i++)
            if(!dfn[i])
                scc(i);
        vector<set<int>> E(n+1);
        for(int i=0; i<n; i++)
        {
            siz[com[i]]++;
            for(int j: edg[i])
            {
                if(com[i]!=com[j])
                    in[com[j]]=1;
            }
        }
        int ans=0;
        for(int i=1; i<=n; i++)
            if(!in[i])
            ans+=siz[i];
        printf("%d\n", ans);
    }

}


/*

2
3
0 1 1
-1 0 1
-1 -1 0
3
0 1 -1
-1 0 1
1 -1 0

*/


