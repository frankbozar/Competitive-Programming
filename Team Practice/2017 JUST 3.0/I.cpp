#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, s, t;
        scanf("%d%d%d", &n, &s, &t);
        vector<vector<int>> a(n+1, vector<int>(10, 0));
        
        for(int i=1; i<=n; i++)
        {
            char s[32]={0};
            scanf("%s", s);
            
            for(int j=0; s[j]!='\0'; j++)
                a[i][ s[j]-'0' ]++;
        }
        
        vector<int> d(n+1, INF);
        d[s]=0;
        queue<int> Q;
        
        for(Q.push(s); !Q.empty(); Q.pop())
        {
            s=Q.front();
            
            for(int i=1; i<=n; i++)
            {
                int c=0;
                
                for(int j=0; j<10; j++)
                    c+=min(a[s][j], a[i][j]);
                
                if( d[i]>d[s]+1 && c==17 )
                {
                    d[i]=d[s]+1;
                    Q.push(i);
                }
            }
        }
        
        printf("%d\n", d[t]>=INF ? -1 : d[t]);
    }
}
