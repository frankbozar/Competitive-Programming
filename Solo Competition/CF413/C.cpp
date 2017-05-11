#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<20;
#define data pair<int,int>
#define p first
#define b second

int main()
{
    int n, c[2], ans=0;
    vector<vector<int>> d(2, vector<int>(N, 0));
    vector<vector<data>> a(2);
    
    for(scanf("%d%d%d", &n, &c[0], &c[1]); n>0; n--)
    {
        int b, p;
        char t;
        scanf("%d%d %c", &b, &p, &t);
        a[t=='C' ? 0 : 1].push_back(data(p, b));
    }
    
    for(int k=0; k<2; k++)
    {
        sort(a[k].rbegin(), a[k].rend());
        
        for(int i=1; i<N; i++)
        {
            d[k][i]=d[k][i-1];
            
            for(; !a[k].empty() && a[k].back().p==i; a[k].pop_back())
            {
                int t=min(max(c[k]-i, 0), i);
                
                if( d[k][t]>0 )
                    ans=max(ans, a[k].back().b+d[k][t]);
                
                d[k][i]=max(d[k][i], a[k].back().b);
            }
        }
    }
    
    if( d[0][ c[0] ]>0 && d[1][ c[1] ]>0 )
        ans=max(ans, d[0][ c[0] ]+d[1][ c[1] ]);
    
    printf("%d\n", ans);
}
