#include<cstdio>
#include<vector>
using namespace std;

struct point
{
    int x, y;
    
    void read()
    {
        scanf("%d%d", &x, &y);
    }
    
    point operator-(const point& P) const
    {
        return {x-P.x, y-P.y};
    }
    
    bool operator!=(const point& P) const
    {
        return x!=P.x || y!=P.y ;
    }
};

bool check(vector<point>& p, int n)
{
    if( n&1 )
        return false;
    
    for(int i=0; i<n/2; i++)
        if( (p[i+1]-p[i])!=(p[i+n/2]-p[i+n/2+1]) )
            return false;
    
    return true;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<point> p(n+1);
    
    for(int i=0; i<n; i++)
        p[i].read();
    
    p[n]=p[0];
    printf(check(p, n) ? "yes\n" : "no\n");
}

/*

4
0 0
0 1
1 1
1 0

3
0 0
0 1
1 0

4
2 0
-2 0
-1 1
1 1

6
0 1
2 3
3 3
5 1
4 0
1 0

6
0 1
2 3
3 3
4 2
2 0
1 0

*/
