#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
#define data pair<lld,int>
#define v first
#define i second

int main()
{
    int n;
    scanf("%d", &n);
    vector<lld> p(n+1, 0);
    vector<data> a(1);
    lld sum=0, ans=-(1LL<<60);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &p[i]);
        a.push_back(data(p[i], i));
        sum+=p[i]*i;
        p[i]+=p[i-1];
    }
    
    sort(a.begin()+1, a.end());
    
    for(int i=1; i<=n; i++)
        ans=max(ans, sum+a[i].v*(i-a[i].i)+(p[a[i].i-1]-p[i-1]));
    
    printf("%lld\n", ans);
}
