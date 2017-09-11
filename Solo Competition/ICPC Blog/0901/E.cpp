#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;

int sol1(int n, int m)
{
    if( n<0 || m<0 )
        return 0;
    else if( n==0 )
        return m==0;
    
    static const int mod=100003;
    static const int N=1<<11;
    static vector<vector<int>> a(N, vector<int>(N, -1));
    int& ans=a[n][m];
    
    if( ans<0 )
    {
        ans=sol1(n-2, m-1)<<1;
        ans+=sol1(n-2, m-2);
        ans+=sol1(n-1, m);
        ans+=sol1(n-2, m);
        ans%=mod;
    }
    
    return ans;
}

int sol2(int n, int m)
{
    if( n<0 || m<0 )
        return 0;
    else if( n==0 )
        return m==0;
    
    static const int mod=100019;
    static const int N=1<<11;
    static vector<vector<int>> a(N, vector<int>(N, -1));
    int& ans=a[n][m];
    
    if( ans<0 )
    {
        ans=sol2(n-2, m-1)<<1;
        ans+=sol2(n-2, m-2);
        ans+=sol2(n-1, m);
        ans+=sol2(n-2, m);
        ans%=mod;
    }
    
    return ans;
}

int main()
{
    int N;
    
    for(int i=0; i<=10; i++)
        for(int j=0; j<=10; j++)
            printf("%3d %3d %10d\n", i, j, sol1(i, j));
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m, p;
        scanf("%d%d%d", &n, &m, &p);
        lld x=sol1(n+m, n);
        lld y=sol2(n+m, n);
        
        
        
    }
}
