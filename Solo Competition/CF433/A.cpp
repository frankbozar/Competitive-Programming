#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
#define data pair<lld,int>
#define c first
#define i second

void sol(vector<data>& a, int n, int m)
{
    sort(a.rbegin(), a.rend());
    lld ans=0;
    vector<int> t(n);
    set<int> S;
    
    for(int i=1; i<=n; i++)
        S.insert(m+i);
    
    for(const data& D : a)
    {
        lld x=*S.lower_bound(D.i);
        S.erase(x);
        ans+=(x-D.i)*D.c;
        t[D.i-1]=x;
    }
    
    printf("%lld\n", ans);
    
    for(int i=0; i<n; i++)
        printf(i==n-1 ? "%d\n" : "%d ", t[i]);
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<data> a(n);
    
    for(int i=0; i<n; i++)
    {
        scanf("%lld", &a[i].c);
        a[i].i=i+1;
    }
    
    sol(a, n, m);
}
