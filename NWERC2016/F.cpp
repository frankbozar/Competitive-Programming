#include<cstdio>
#include<vector>
using namespace std;

bool check(const vector<vector<int>>& a, int n, int x)
{
    vector<vector<int>> b(2);
    
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<n; j++)
        {
            if( a[i][j]<=x )
                continue;
            else if( !b[i].empty() && b[i].back()==a[i][j] )
                b[i].pop_back();
            else
                b[i].push_back(a[i][j]);
        }
    }
    
    return b[0]==b[1];
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