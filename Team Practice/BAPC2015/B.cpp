#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int N=3600;
const int INF=1<<30;

int main()
{
    int T;
    
    for(scanf("%d", &T); T>0; T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        vector<int> d(N+1, INF);
        d[0]=0;
        queue<int> Q;
        
        for(Q.push(0); !Q.empty(); Q.pop())
        {
            int u=Q.front();
            
            for(int i=0; i<n; i++)
            {
                int v=u+a[i];
                v=max(v, 0);
                v=min(v, N);
                
                if( d[v]>d[u]+1 )
                {
                    d[v]=d[u]+1;
                    Q.push(v);
                }
            }
        }
        
        for(int i=m; i<=N; i++)
            if( d[i]<INF )
            {
                printf("%d %d\n", d[i], i-m);
                break;
            }
    }
}

/*

2
3 50
-10 10 60
1 50
20

*/
