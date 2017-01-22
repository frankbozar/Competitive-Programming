#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=1<<20;

int solve(int n, int m, int k)
{
    if( n<=k || m<=k )
        return -1;
    
    if( n<m )
        swap(n, m);
    
    int ans=INF;
    int w=k*2+1;
    int t=(2*k+2)/k;
    int h=t*k+1;
    
    if( min(w, h)<=m && max(w, h)<=n )
        ans=min(ans, t+1);
    
    w=2*k+3;
    t=max((m+k-1)/k, 2);
    
    if( w<=n && k<n )
        ans=min(ans, t);
    
    return ans>=INF ? -1 : ans ;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        printf("Case #%d: %d\n", cases, solve(n, m, k));
    }
}

/*

5
2 2 1
4 5 1
6 6 1
6 6 2
773632 635271 223841

*/
