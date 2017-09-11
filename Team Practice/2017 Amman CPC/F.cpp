#include<cstdio>
#include<map>
#include<set>
#include<queue>
#include<vector>
using namespace std;
const int INF=1<<30;
typedef pair<int, int> data;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m, ans=0;
        scanf("%d%d", &n, &m);
        vector<int> a(n), b(n, INF);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        map<int, int> M;
        
        for(int i=n-1; i>=0; i--)
        {
            if( M.find(a[i])!=M.end() )
                b[i]=M[ a[i] ];
            
            M[ a[i] ]=i;
        }
        
        priority_queue<data> PQ;
        set<int> S;
        
        for(int i=0; i<n; i++)
        {
            if( S.find(a[i])==S.end() )
            {
                if( S.size()==m )
                {
                    S.erase(PQ.top().second);
                    PQ.pop();
                }
                
                ans++;
                S.insert(a[i]);
            }
            
            PQ.push(data(b[i], a[i]));
        }
        
        printf("%d\n", ans);
    }
}
