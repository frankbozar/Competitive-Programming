#include<cstdio>
#include<vector>
using namespace std;
vector<vector<int>> cnt, edg;
vector<int> col, siz;

int size(int u, p=-1)
{
    int& ans=siz[u];
    
    if( ans<0 )
    {
        ans=1;
        
        for(int v : edg[u])
            ans+=size(v);
    }
    
    return ans;
}

void dfs()
{
    
    
    
    
    
}

int main()
{
    int n;
    scanf("%d", &n);
    cnt.resize(n);
    edg.resize(n);
    col.resize(n);
    siz.assign(n, -1);
    
    for(int i=0; i<n; i++)
        scanf("%d", &col[i]);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
}