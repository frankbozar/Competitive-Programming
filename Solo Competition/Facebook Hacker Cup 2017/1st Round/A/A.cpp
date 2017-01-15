#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=0x3FFFFFFF;

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m, ans=0;
        scanf("%d%d", &n, &m);
        vector<vector<int>> a(n, vector<int>(m+1, INF));
        vector<int> c(n, 0);
        
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
                scanf("%d", &a[i][j]);
            
            sort(a[i].begin(), a[i].end());
            int p=-1, v=INF;
            
            for(int j=0; j<=i; j++)
            {
                int t=(c[j]<<1)+a[j][ c[j] ]+1;
                
                if( v>t )
                {
                    v=t;
                    p=j;
                }
            }
            
            c[p]++;
            ans+=v;
        }
        
        printf("Case #%d: %d\n", cases, ans);
    }
}

/*

5

3 2
1 1
100 100
10000 10000

5 1
1
2
3
4
5

5 5
1 2 3 4 5
2 3 4 5 1
3 4 5 1 2
4 5 1 2 3
5 1 2 3 4

5 5
1 1 1 1 1
2 2 2 2 2
3 3 3 3 3
4 4 4 4 4
5 5 5 5 5

10 4
7 15 12 6
15 3 19 18
10 9 10 14
12 14 8 8
5 3 5 11
9 14 19 11
12 6 20 9
18 13 12 15
14 14 10 20
11 19 12 11

*/
