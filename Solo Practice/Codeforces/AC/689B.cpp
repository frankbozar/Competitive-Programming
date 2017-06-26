#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n+1), d(n+2, n+1);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    
    d[1]=0;
    queue<int> Q;
    
    for(Q.push(1); !Q.empty(); Q.pop())
    {
        int u=Q.front();
        
        if( d[u-1]>d[u]+1 && u-1>=1 )
        {
            d[u-1]=d[u]+1;
            Q.push(u-1);
        }
        
        if( d[u+1]>d[u]+1 && u+1<=n )
        {
            d[u+1]=d[u]+1;
            Q.push(u+1);
        }
        
        if( d[ a[u] ]>d[u]+1 )
        {
            d[ a[u] ]=d[u]+1;
            Q.push(a[u]);
        }
    }
    
    for(int i=1; i<=n; i++)
        printf(i==n ? "%d\n" : "%d ", d[i]);
}
