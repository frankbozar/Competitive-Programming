#include<cstdio>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<20;
typedef bitset<N> set;

int main()
{
    vector<vector<int>> d(N);
    
    for(int i=1; i<N; i++)
        for(int j=i; j<N; j+=i)
            d[j].push_back(i);
    
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    sort(a.begin(), a.end());
    vector<int> cnt(N, 0);
    set tmp, ans;
    
    for(int l=0, r=1, i=0; i<n; i++)
    {
        for(; r<=a[i]; r++)
            for(int t : d[r])
                if( cnt[t]++==0 )
                {
                    tmp[t]=true;
                    
                    if( i==0 )
                        ans[t]=true;
                }
        
        for(; r-l>m+1; l++)
            for(int t : d[l])
                if( --cnt[t]==0 )
                    ans[t]=tmp[t]=false;
    }
    
    for(int i=N-1; i>0; i--)
        if( ans[i] )
        {
            printf("%d\n", i);
            break;
        }
}
