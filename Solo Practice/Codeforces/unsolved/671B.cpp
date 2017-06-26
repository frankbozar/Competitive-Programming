#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

int main()
{
    int n;
    lld m;
    scanf("%d%lld", &n, &m);
    vector<lld> a(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%lld", &a[i]);
    
    sort(a.begin(), a.end());
    
    for(int l=1, r=n; k>0 && a[1]!=a[n]; )
    {
        for(; a[l]==a[0]; l++);
        for(; a[r]==a[n]; r--);
        
        
    }
    
    printf("%lld\n", a[n]-a[1]);
}
