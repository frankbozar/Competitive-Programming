#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

bool check(const vector<vector<lld>>& a, int n, lld x)
{
    vector<vector<lld>> b(2), c(2);
    
    for(int i=0; i<2; i++)
        for(int j=0; j<n; j++)
            if( a[i][j]>x )
                b[i].push_back(a[i][j]);
    
    for(int i=0; i<2; i++)
    {
        n=b[i].size();
        b[i].push_back(-1);
        
        for(int j=0; j<n; j++)
        {
            if( b[i][j]==b[i][j+1] )
                j++;
            else
                c[i].push_back(b[i][j]);
        }
    }
    
    return c[0]==c[1];
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<vector<lld>> a(2, vector<lld>(n));
    lld ans=0;
    
    for(int i=0; i<2; i++)
        for(int j=0; j<n; j++)
        {
            scanf("%lld", &a[i][j]);
            ans=max(ans, a[i][j]);
        }
    
    for(int l=0, r=ans; l<r; )
    {
        int m=(l+r)>>1;
        
        if( check(a, n, m) )
            r=ans=m;
        else
            l=m+1;
    }
    
    printf("%lld\n", ans);
}

/*

5
2 1 8 2 8
9 9 4 1 4

8
7 7 15 15 2 2 4 4
5 5 3 3 9 9 1 1

*/