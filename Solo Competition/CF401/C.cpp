#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

int main()
{
    int n, m, k;
    scanf("%d%d", &n, &m);
    vector<vector<int>> a(n+1, vector<int>(m+1, 0));
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            scanf("%d", &a[i][j]);
    
    vector<int> b(n+1, 0);
    
    for(int j=1; j<=m; j++)
    {
        for(int i=1; i<=n; )
        {
            a[i-1][j]=0;
            int k=i;
            for(; k<=n && a[k-1][j]<=a[k][j]; k++);
            
            for(; i<k; i++)
                b[i]=max(b[i], k-1);
        }
    }
    
    for(scanf("%d", &k); k>0; k--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf(b[l]>=r ? "Yes\n" : "No\n");
    }
}
