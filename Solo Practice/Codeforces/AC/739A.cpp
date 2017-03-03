#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;

int main()
{
    int n, m, ans=INF;
    scanf("%d%d", &n, &m);
    
    for(int i=0; i<m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        ans=min(ans, r-l+1);
    }
    
    printf("%d\n", ans);
    
    for(int i=0; i<n; i++)
        printf(i==n-1 ? "%d\n" : "%d ", i%ans);
}
