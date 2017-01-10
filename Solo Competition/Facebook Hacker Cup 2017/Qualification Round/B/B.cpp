#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int solve(vector<int>& a, int n)
{
    sort(a.rbegin(), a.rend());
    int ans=0;
    
    for(int l=0, r=n; a[l]*(r-l)>=50; l++)
    {
        r-=49/a[l];
        ans++;
    }
    
    return ans;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n;
        scanf("%d", &n);
        vector<int> a(n+1, 0);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        printf("Case #%d: %d\n", cases, solve(a, n));
    }
}
