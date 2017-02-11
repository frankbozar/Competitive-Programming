#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        sort(a.rbegin(), a.rend());
        lld ans=0;
        
        for(int i=0; i<n && a[i]-i>0; i++)
            ans+=a[i]-i;
        
        printf("%lld\n", ans);
    }
}

/*

1
6
0 9 9 1 7 5

*/
