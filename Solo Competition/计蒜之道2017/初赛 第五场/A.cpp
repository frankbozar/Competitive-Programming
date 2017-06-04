#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, m;
    vector<int> a(1, 0);
    
    for(scanf("%d%d", &n, &m); m>0; m--)
    {
        int x;
        scanf("%d", &x);
        
        if( x>0 )
            a.push_back(x);
    }
    
    m=a.size();
    sort(a.rbegin(), a.rend()-1);
    
    for(int i=1; i<m; i++)
        a[i]+=a[i-1];
    
    for(int i=2; i<m; i++)
        a[i]-=i-1;
    
    a[0]=1;
    int ans=lower_bound(a.begin(), a.end(), n)-a.begin();
    
    if( ans>=m )
        printf("Impossible\n");
    else
        printf("%d\n", ans);
}
