#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
using namespace std;
typedef long long lld;
const int N=60;
vector<map<int, int>> g(N+1);
int cnt=0;

int gn(int a, lld b)
{
    if( a==0 )
        return 0;
    
    b&=(1LL<<a)-1;
    
    if( g[a].find(b)==g[a].end() )
    {
        cnt++;
        
        int t=0;
        
        for(int i=0; i<a; i++)
            if( !(b&(1LL<<i)) )
                t|=1<<gn(a-i-1, b|(1LL<<i));
        
        g[a][b]=__builtin_ctz(~t);
    }
    
    return g[a][b];
}

int main()
{
    int n, ans=0;
    
    for(scanf("%d", &n); n>0; n--)
    {
        int x;
        scanf("%d", &x);
        ans^=(int)ceil((sqrt((x<<3)+9)-3)/2);
    }
    
    printf(ans ? "NO\n" : "YES\n");
}
