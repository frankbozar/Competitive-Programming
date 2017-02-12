#include<cstdio>
#include<vector>
using namespace std;
#define edge pair<int,int>
#define u first
#define v second

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    
    if( k==1 )
    {
        printf("-1\n");
        return 0;
    }
    
    vector<edge> ans;
    
    for(int u=1; u<=n; u++)
    {
        for(int i=1; i<=k>>1; i++)
        {
            int v=(u+i-1)%n+1;
            ans.push_back(edge(u, v));
        }
    }
    
    if( k&1 )
    {
        for(int u=1; u<=(n+1)>>1; u++)
        {
            int v=(u+((n+1)>>1)-1)%n+1;
            ans.push_back(edge(u, v));
        }
    }
    
    printf("%lu\n", ans.size());
    
    for(const edge& e : ans)
        printf("%d %d\n", e.u, e.v);
    
    for(int i=1; i<=n; i++)
        printf(i==n ? "%d\n" : "%d ", i);
}
