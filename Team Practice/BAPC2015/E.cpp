
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int INF=0x3FFFFFFF;

struct Bit
{
    int n;
    vector<int> a;
    Bit(int _n):a(n+1, INF){}
    void add(int x, int val)
    {
        for(; x<=n; x+=x&-x)
            a[x]=min(a[x], val);
    }
    int que(int x)
    {
        int res=INF;
        for(; x>=1; x-=x&-x)
            res=min(res, a[x]);
        return res;
    }
};

int main()
{
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        int n;
        scanf("%d", &n);
        vector<vector<int>> v(n, vector<int>(4));
        for(int i=0; i<n; i++)
        {
            scanf("%d%d%d", &v[i][0], &v[i][1], &v[i][2]);
            v[i][3]=i;
        }
        vector<int> dead(n, 0);
        for(int z=0; z<3; z++)
        {
            Bit bit(n);
            sort(v.begin(), v.end());
            for(int i=0; i<n; i++)
            {
                int t=bit.que(v[i][1]);
                if(t<=v[i][2])
                    dead[v[i][3]]=1;
                bit.add(v[i][1], v[i][2]);
            }
            for(int i=0; i<n; i++)
                swap(v[i][0], v[i][1]), swap(v[i][0], v[i][2]);
        }
        int ans=0;
        for(int i=0; i<n; i++)
            ans+=dead[i]==0;
        printf("%d\n", ans);
        
    }
    
    
    
    
}

/*
 

3
3
2 3 2
3 2 3
1 1 1
3
1 2 3
2 3 1
3 1 2
10
1 7 10
3 9 7
2 2 9
5 10 8
4 3 5
7 5 2
6 1 3
9 6 6
8 4 4
10 8 1


*/
