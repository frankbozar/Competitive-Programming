#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define ride pair<int,int>
#define p first
#define b second

bool ok(vector<int> a, int n, int m, int& cnt)
{
    cnt=0;
    
    for(int p=0, i=0; i<n; i++)
    {
        if( a[i]>m )
        {
            cnt+=a[i]-m;
            p-=a[i]-m;
            
            if( p<0 )
                return false;
            
            a[i]=m;
        }
        
        p+=m-a[i];
    }
    
    return true;
}

void f(const vector<ride>& a, int n, int m, int k, int& x, int& y)
{
    x=y=0;
    vector<vector<int>> b(2);
    vector<int> c(n, 0);
    
    for(const ride& r : a)
    {
        b[r.b-1].push_back(r.p-1);
        c[r.p-1]++;
    }
    
    for(int l=max(b[0].size(), b[1].size()), r=k+1; l<r; )
    {
        int m=(l+r)>>1, t=0;
        
        if( ok(c, n, m, t) )
            r=x=m, y=t;
        else
            l=m+1;
    }
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        vector<ride> a(k);
        
        for(int i=0; i<k; i++)
            scanf("%d%d", &a[i].p, &a[i].b);
        
        int x, y;
        f(a, n, m, k, x, y);
        printf("Case #%d: %d %d\n", cases, x, y);
    }
}

/*

3

2 2 2
2 1
2 2

2 2 2
1 1
1 2

2 2 2
1 1
2 1

1000 1000 4
3 2
2 1
3 3
3 1

3 3 5
3 1
2 2
3 3
2 2
3 1

*/
