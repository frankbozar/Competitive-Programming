#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1000000000000;

int main()
{
    vector<lld> a;
    
    for(lld i=1; i*i<=INF; i+=2)
        for(int j=0; i*i<<j<=INF; j++)
            a.push_back(i*i<<j);
    
    sort(a.begin(), a.end());
    
    for(lld n; scanf("%lld", &n) && n>0; )
        printf("%lld\n", n-(upper_bound(a.begin(), a.end(), n)-a.begin()));
}
