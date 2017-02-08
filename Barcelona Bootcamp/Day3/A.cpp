#include<cstdio>
#include<vector>
using namespace std;

struct bit
{
    int n;
    vector<int> a;
    bit(int _n) : n(_n), a(n+1, 0){}
    
    void add(int x, int v)
    {
        for(; x<=n; x+=x&-x)
            a[x]+=v;
    }
    
    int query(int x)
    {
        int ans=0;
        
        for(; x>0; x-=x&-x)
            ans+=a[x];
        
        return ans;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> p(n<<1), ans(n+1, -1);
    vector<vector<int>> a(n+1);
    
    for(int i=0; i<n<<1; i++)
    {
        scanf("%d", &p[i]);
        a[ p[i] ].push_back(i);
    }
    
    bit b(n<<2);
    
    for(int i=1; i<=n; i++)
    {
        b.add(a[i][0]+1, 1);
        b.add(a[i][1]+1, -1);
        b.add(a[i][0]+(n<<1)+1, 1);
        b.add(a[i][1]+(n<<1)+1, -1);
    }
    
    for(int i=0; i<n<<1; i++)
    {
        if( i==a[ p[i] ][0] )
        {
            ans[ p[i] ]=b.query(a[ p[i] ][1])-b.query(i+1);
            b.add(a[ p[i] ][0]+1, -2);
            b.add(a[ p[i] ][1]+1, 2);
            b.add(a[ p[i] ][0]+(n<<1)+1, -2);
            b.add(a[ p[i] ][1]+(n<<1)+1, 2);
        }
        else
        {
            b.add(a[ p[i] ][0]+1, 2);
            b.add(a[ p[i] ][1]+1, -2);
            b.add(a[ p[i] ][0]+(n<<1)+1, 2);
            b.add(a[ p[i] ][1]+(n<<1)+1, -2);
        }
    }
    
    for(int i=1; i<=n; i++)
        printf("%d\n", ans[i]);
}

/*

5
1 2 3 1 4 2 5 5 3 4

*/
