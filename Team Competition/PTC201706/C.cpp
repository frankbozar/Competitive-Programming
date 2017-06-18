#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

struct data
{
    int x, y, i;
    
    data(int _x=0, int _y=0, int _i=0) : i(_i)
    {
        int g=gcd(_x, _y);
        x=_x/g;
        y=_y/g;
    }
    
    bool operator<(const data& D) const
    {
        return y*D.x==D.y*x ? i>D.i : y*D.x > D.y*x ;
    }
};

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        vector<data> a;
        
        for(int i=0; i<n; i++)
        {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            a.push_back(data(x1, y2, 1));
            a.push_back(data(x2, y1, -1));
        }
        
        sort(a.begin(), a.end());
        data ans;
        
        for(int p=0, i=0; i<n<<1; i++)
        {
            p+=a[i].i;
            
            if( p>ans.i )
                ans=data(a[i].x, a[i].y, p);
        }
        
        printf("%d/%d %d\n", ans.y, ans.x, ans.i);
    }
}

/*

2
4
5 0 10 5
2 5 5 10
7 10 10 20
0 5 3 12
2
0 0 1 1
0 10 10 20

*/
