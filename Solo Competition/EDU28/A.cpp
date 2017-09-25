#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, ans=0;
    scanf("%d", &n);
    vector<int> p(n+1, 0);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &p[i]);
        p[i]+=p[i-1];
    }
    
    for(int i=0; i<=n; i++)
        ans=max(ans, (i-p[i])+(p[n]-p[i]));
    
    printf("%d\n", ans);
}
