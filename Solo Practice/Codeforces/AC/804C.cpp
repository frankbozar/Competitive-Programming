#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, m, k=1;
    scanf("%d%d", &n, &m);
    vector<vector<int>> a(n+1), e(n+1);
    vector<int> ans(m+1, 0), t(m+1, 0);
    
    for(int i=1; i<=n; i++)
    {
        int l;
        scanf("%d", &l);
        a[i].resize(l);
        k=max(k, l);
        
        for(int j=0; j<l; j++)
            scanf("%d", &a[i][j]);
    }
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    queue<int> Q;
    
    for(Q.push(1); !Q.empty(); Q.pop())
    {
        int u=Q.front(), i=1;
        
        for(int x : a[u])
            t[ ans[x] ]=1;
        
        for(int x : a[u])
        {
            while( t[i] )
                i++;
            
            if( !ans[x] )
                t[ ans[x]=i ]=1;
        }
        
        for(int x : a[u])
            t[ ans[x] ]=0;
        
        for(int v : e[u])
            if( a[v].empty() || a[v].front()>=0 )
                Q.push(v);
        
        a[u].assign(1, -1);
    }
    
    printf("%d\n", k);
    
    for(int i=1; i<=m; i++)
        printf(i==m ? "%d\n" : "%d ", ans[i]==0 ? 1 : ans[i]);
}
