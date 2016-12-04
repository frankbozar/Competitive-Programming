#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, s=0;
    scanf("%d", &n);
    vector<pair<int, int>> a(n);
    
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i].first);
        a[i].second=i+1;
        s+=a[i].first;
    }
    
    sort(a.rbegin(), a.rend());
    
    if( a[0].first<<1>s )
    {
        printf("impossible\n");
        return 0;
    }
    
    for(int i=0; i<n; i++)
        printf(i==n-1 ? "%d\n" : "%d ", a[i].second);
}