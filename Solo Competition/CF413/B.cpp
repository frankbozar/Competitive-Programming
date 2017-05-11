#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2000000000;

int f(vector<vector<int>>& a, int x)
{
    int ans=INF;
    
    for(int i=0; i<7; i++)
        if( (i&x)!=0 && !a[i].empty() )
            ans=min(ans, a[i].back());
    
    for(int i=0; i<7; i++)
        if( (i&x)!=0 && !a[i].empty() && a[i].back()==ans )
            a[i].pop_back();
    
    return ans>=INF ? -1 : ans ;
}

int main()
{
    int n, m;
    scanf("%d", &n);
    vector<int> p(n), a(n, 0);
    
    for(int i=0; i<n; i++)
        scanf("%d", &p[i]);
    
    for(int k=0; k<2; k++)
        for(int i=0; i<n; i++)
        {
            int x;
            scanf("%d", &x);
            a[i]|=1<<(x-1);
        }
    
    vector<vector<int>> b(7);
    
    for(int i=0; i<n; i++)
        b[ a[i] ].push_back(p[i]);
    
    for(int i=0; i<7; i++)
        sort(b[i].rbegin(), b[i].rend());
    
    for(scanf("%d", &m); m>0; m--)
    {
        int x;
        scanf("%d", &x);
        printf(m==1 ? "%d\n" : "%d ", f(b, 1<<(x-1)));
    }
}
