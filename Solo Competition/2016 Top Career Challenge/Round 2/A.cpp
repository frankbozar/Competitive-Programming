#include<cstdio>
#include<vector>
using namespace std;

#include<cstdlib>
typedef long long lld;

int solution(vector<vector<int>>& a)
{
    if( a.empty() || a.front().empty() )
        return 0;
    
    int n=a.size();
    int m=a.front().size();
    lld ans=0;
    
    for(int p=0, l=0, r=m, u=0, d=n; l<r && u<d; p=(p+1)&3)
    {
        switch( p )
        {
            case 0:
                for(int i=l; i<r; i++)
                    ans+=a[u][i];
                
                u++, d--;
                break;
                
            case 1:
                for(int i=u; i<d; i++)
                    ans+=a[i][r-1];
                
                l++, r--;
                break;
                
            case 2:
                for(int i=l; i<r; i++)
                    ans+=a[d-1][i];
                
                u++, d--;
                break;
                
            case 3:
                for(int i=u; i<d; i++)
                    ans+=a[i][l];
                
                l++, r--;
                
            default:
                break;
        }
    }
    
    return abs(ans)>100000000 ? -1 : ans ;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> a(n, vector<int>(m));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            scanf("%d", &a[i][j]);
    
    printf("%d\n", solution(a));
}

/*

7 8
5  3  8  9  4  1  3 -2
4  6  0  3  6  4  2  1
4 -5  3  1  9  5  6  6
3  7  5  3  2  8  9  4
5  3 -3  6  3  2  8  0
5  7  5  3  3 -9  2  2
0  4  3  2  5  7  5  4

*/