#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
typedef pair<int, int> data;
const int N=101010;

int main()
{
    vector<int> isp(N, 1);
    
    for(lld p=0, i=2; i<N; i++)
    {
        if( !isp[i] )
            isp[i]=p;
        else
        {
            isp[i]=p=i;
            
            for(lld j=i*i; j<N; j+=i)
                isp[j]=0;
        }
    }
    
    int n;
    scanf("%d", &n);
    vector<int> a(n+1, 0), p(n+1, 0);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
        p[ a[i] ]=i;
    }
    
    vector<pair<int, int>> ans;
    
    for(int i=1; i<=n; i++)
    {
        while( p[i]!=i )
        {
            int t=p[i]-isp[ p[i]-i+1 ]+1;
            ans.push_back(data(t, p[i]));
            a[ p[i] ]=a[t];
            p[ a[t] ]=p[i];
            a[t]=i;
            p[i]=t;
        }
    }
    
    printf("%lu\n", ans.size());
    
    for(const data& t : ans)
        printf("%d %d\n", t.first, t.second);
}
