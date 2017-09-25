#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int sol(vector<int>& a, int n, int m)
{
    int ans=0;
    sort(a.begin(), a.end());
    
    for(int l=0, r=n-1; l<=r; )
    {
        if( m>a[l] )
            m-=a[l++], ans++;
        else if( l==r || ans==0 )
            break;
        else
            m+=a[r--], ans--;
    }
    
    return ans;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int m, n;
        scanf("%d%d", &m, &n);
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        printf("Case #%d: %d\n", cases, sol(a, n, m));
    }
}
