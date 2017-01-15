#include<cstdio>
#include<cstdlib>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=0x3FFFFFFF;
#define point pair<int,int>
#define x first
#define y second

int operator-(const point& P, const point& Q)
{
    return P.x>Q.x || P.y>Q.y ? INF : max(Q.x-P.x, Q.y-P.y) ;
}

void read(vector<point>& P, vector<int>& X, vector<int>& Y)
{
    set<int> x, y;
    
    for(point& p : P)
    {
        scanf("%d%d", &p.x, &p.y);
        x.insert(p.x);
        y.insert(p.y);
    }
    
    X.assign(x.begin(), x.end());
    Y.assign(y.begin(), y.end());
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, r, ans=0;
        scanf("%d%d", &n, &r);
        vector<point> P(n);
        vector<int> X, Y;
        read(P, X, Y);
        
        for(int x1 : X) for(int x2 : X) for(int y1 : Y) for(int y2 : Y)
        {
            point a(x1, y1);
            point b(x2, y2);
            int cnt=0;
            
            for(const point& p : P)
                if( a-p<=r || b-p<=r )
                    cnt++;
            
            ans=max(ans, cnt);
        }
        
        printf("Case #%d: %d\n", cases, ans);
    }
}

/*

5

7 3
1 5
2 3
2 1
5 1
6 3
4 4
4 5

4 1
0 0
0 2
10 0
10 2

4 2
0 0
0 2
10 0
10 2

7 3
8 5
3 6
9 2
4 5
3 2
1 8
2 8

7 6
8 5
3 6
9 2
4 5
3 2
1 8
2 8

*/
