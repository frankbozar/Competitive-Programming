#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct Point2D
{
    int x, y;
};

bool operator<(const Point2D& P, const Point2D& Q)
{
    return P.x==Q.x ? P.y<Q.y : P.x<Q.x ;
}

int operator*(const Point2D& P, const Point2D& Q)
{
    return P.x*Q.y-P.y*Q.x;
}

Point2D operator-(const Point2D& P, const Point2D& Q)
{
    Point2D D;
    D.x=P.x-Q.x;
    D.y=P.y-Q.y;
    return D;
}

int solution(vector<Point2D>& p)
{
    int n=p.size(), k=0;
    vector<Point2D> h(n<<1);
    sort(p.begin(), p.end());
    
    for(int i=0; i<n; i++)
    {
        for(; k>=2 && (h[k-1]-h[k-2])*(p[i]-h[k-1])<=0; k--);
        h[k++]=p[i];
    }
    
    for(int t=k, i=n-2; i>=0; i--)
    {
        for(; k>t && (h[k-1]-h[k-2])*(p[i]-h[k-1])<=0; k--);
        h[k++]=p[i];
    }
    
    return k-1;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<Point2D> a(n);
    
    for(int i=0; i<n; i++)
        scanf("%d%d", &a[i].x, &a[i].y);
    
    printf("%d\n", solution(a));
}

/*

6
3 2
6 3
2 5
5 2
1 1
4 4

*/