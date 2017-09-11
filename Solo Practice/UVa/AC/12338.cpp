#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld mod=1000000007;
const lld pri=31;
char s[1<<20];

int main()
{
    int ncases;
    scanf("%d", &ncases);
    
    for(int cases=1; cases<=ncases; cases++)
    {
        printf("Case %d:\n", cases);
        int n;
        scanf("%d", &n);
        vector<vector<int>> h(n+1, vector<int>(1, 0));
        
        for(int i=1; i<=n; i++)
        {
            scanf("%s", s);
            
            for(int j=0; s[j]; j++)
                h[i].push_back((h[i].back()*pri+s[j]-'a')%mod);
        }
        
        for(scanf("%d", &n); n>0; n--)
        {
            int x, y, ans=0;
            scanf("%d%d", &x, &y);
            
            for(int l=0, r=min(h[x].size(), h[y].size()); l<r; )
            {
                int m=(l+r)>>1;
                
                if( h[x][m]==h[y][m] )
                    l=m+1, ans=m;
                else
                    r=m;
            }
            
            printf("%d\n", ans);
        }
    }
}

/*

2

5
daffodilpacm
daffodiliupc
distancevector
distancefinder
distinctsubsequence
4
1 2
1 5
3 4
4 5

2
acm
icpc
2
1 2
2 2

*/
