#include<cstdio>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;

struct query
{
    int l, r, i, a;
    
    query(int _i) : i(_i), a(INF)
    {
        scanf("%d%d", &l, &r);
        l--, r--;
    }
    
    void flip()
    {
        swap(l, r);
    }
    
    bool operator<(const query& Q)
    {
        return r==Q.r ? l<Q.l : r<Q.r ;
    }
    
    void set(int x)
    {
        a=min(a, x);
    }
};

void solve(const vector<int>& a, vector<query>& q)
{
    int n=a.size();
    int m=q.size();
    
    
    
    
    
    
    
    
}

int main()
{
    int n, m;
    scanf("%d", &n);
    vector<int> a(n);
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    scanf("%d", &m);
    vector<query> q;
    
    for(int i=0; i<m; i++)
        q.push_back(query());
    
    solve(a, q);
    
    for(int i=0; i<m; i++)
        q[i].flip();
    
    solve(vector<int>(a.rbegin(), a.rend()), q);
    vector<int> b(m);
    
    for(int i=0; i<m; i++)
        b[ q[i].i ]=q[i].a;
    
    for(int i=0; i<m; i++)
        printf("%d\n", b[i]);
}
