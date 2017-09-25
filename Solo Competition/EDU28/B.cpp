#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

int sol(const vector<lld>& a, int n, int m, lld t)
{
    lld s=0;
    
    for(int i=0; i<m; i++)
        s+=a[i];
    
    int ans=0;
    
    for(int i=0; i<=n && s*i<=t; i++)
    {
        int cnt=(m+1)*i;
        lld r=t-s*i;
        
        for(int j=0; j<m && r>=a[j]; j++)
        {
            int c=min(r/a[j], (lld)(n-i));
            r-=a[j]*c;
            cnt+=c;
        }
        
        ans=max(ans, cnt);
    }
    
    return ans;
}

int main()
{
    int n, m;
    lld t;
    scanf("%d%d%lld", &n, &m, &t);
    vector<lld> a(m);
    
    for(int i=0; i<m; i++)
        scanf("%lld", &a[i]);
    
    sort(a.begin(), a.end());
    printf("%d\n", sol(a, n, m, t));
}
