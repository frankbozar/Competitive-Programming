#include<cstdio>
#include<set>
#include<queue>
#include<vector>
using namespace std;

int f(int x)
{
    return x/(x&-x);
}

int solve(int n, vector<vector<int>>& e, vector<int>& d)
{
    vector<set<int>> l(n+1);
    vector<int> used(n+1, false);
    queue<int> Q;
    
    for(int i=1; i<=n; i++)
        if( d[i]==1 )
            Q.push(i);
    
    for(; !Q.empty(); Q.pop())
    {
        for(int u=Q.front(); !used[u] && d[u]==1 && l[u].size()<2; d[u]--)
        {
            used[u]=true;
            
            for(int v : e[u])
            {
                if( !used[v] )
                {
                    l[v].insert(l[u].empty() ? 1 : *l[u].begin()+1);
                    u=v;
                    break;
                }
            }
        }
    }
    
    int cnt=0, ans=0;
    
    for(int i=1; i<=n; i++)
    {
        if( l[i].size()>2 )
            return -1;
        else if( l[i].size()==2 )
            cnt++;
    }
    
    if( cnt>1 )
        return -1;
    
    for(int i=1; i<=n; i++)
    {
        if( l[i].empty() )
            continue;
        if( l[i].size()==2 )
            return f(*l[i].begin()+*--l[i].end());
        else
            ans=max(ans, *l[i].begin());
    }
    
    return f(ans);
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<vector<int>> e(n+1);
    vector<int> d(n+1, 0);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
        d[u]++, d[v]++;
    }
    
    printf("%d\n", solve(n, e, d));
}

/*

6
1 2
2 3
2 4
4 5
1 6

7
1 2
1 3
3 4
1 5
5 6
6 7


*/
