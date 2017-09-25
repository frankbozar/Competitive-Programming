#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const int N=1<<20;

lld f(lld x)
{
    return x*x;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<vector<int>> a(N);
    
    for(int i=0; i<n; i++)
    {
        int x;
        scanf("%d", &x);
        a[x].push_back(i);
    }
    
    lld cnt=0;
    
    for(int i=0; i<N; i++)
    {
        if( a[i].empty() )
            continue;
        
        int m=a[i].size();
        cnt+=f(n);
        cnt-=f(a[i][0]);
        cnt-=f(n-a[i][m-1]-1);
        
        for(int j=1; j<m; j++)
            cnt-=f(a[i][j]-a[i][j-1]-1);
    }
    
    printf("%f\n", cnt/(double)f(n));
}
