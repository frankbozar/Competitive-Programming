#include<cstdio>
#include<vector>
using namespace std;

bool check(const vector<vector<int>>& a, int n, int x)
{
    vector<vector<int>> b(2), c(2);
    
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<n; j++)
        {
            if( a[i][j]<=x )
                continue;
            else
                b[i].push_back(a[i][j]);
        }
    }
    
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
    int n, ans=-1;
    scanf("%d", &n);
    vector<vector<int>> a(2, vector<int>(n));
    
    for(int i=0; i<2; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &a[i][j]);
    
    for(int l=0, r=n+1; l<r; )
    {
        int m=(l+r)>>1;
        
        if( check(a, n, m) )
            r=ans=m;
        else
            l=m+1;
    }
    
    printf("%d\n", ans);
}

/*

5
2 1 8 2 8
9 9 4 1 4

*/