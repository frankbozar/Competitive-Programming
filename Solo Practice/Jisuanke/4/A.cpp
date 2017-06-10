#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, m, k, ans=0;
    scanf("%d%d%d", &n, &m, &k);
    vector<vector<int>> a(2, vector<int>(1, 0));
    a[0].push_back(n+1);
    a[1].push_back(m+1);
    
    for(; k>0; k--)
    {
        int c, d;
        scanf("%d%d", &c, &d);
        a[c].push_back(d);
    }
    
    sort(a[0].begin(), a[0].end());
    sort(a[1].begin(), a[1].end());
    
    for(int i=a[0].size()-1; i>0; i--)
        for(int j=a[1].size()-1; j>0; j--)
            ans+=(a[0][i]-a[0][i-1]-1)*(a[1][j]-a[1][j-1]-1)/2;
    
    printf("%d\n", ans);
}
