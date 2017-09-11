#include<cstdio>
#include<vector>
using namespace std;

double dfs(const vector<vector<int>>& e, int u=1, int p=0)
{
    int cnt=0;
    double ans=0;
    
    for(int v : e[u])
    {
        if( v==p )
            continue;
        
        ans+=1+dfs(e, v, u);
        cnt++;
    }
    
    if( cnt>0 )
        ans/=cnt;
    
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<vector<int>> e(n+1);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    printf("%.10f\n", dfs(e));
}
