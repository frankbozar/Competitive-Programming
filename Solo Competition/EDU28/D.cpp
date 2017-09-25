#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

struct pixel
{
    int x, y, t;
    
    void read()
    {
        scanf("%d%d%d", &x, &y, &t);
    }
    
    bool operator<(const pixel& P) const
    {
        return t<P.t;
    }
};

int main()
{
    int n, m, k, q, ans=-1;
    scanf("%d%d%d%d", &n, &m, &k, &q);
    vector<pixel> p(q);
    
    for(int i=0; i<q; i++)
        p[i].read();
    
    sort(p.begin(), p.end());
    vector<set<int>> S(n+2);
    
    for(int i=1; i<=n+1; i++)
        for(int j=0; j<=m+1; j++)
            S[i].insert(j);
    
    for(const pixel& P : p)
    {
        S[P.x].erase(P.y);
        int u=max(1, P.x-k+1);
        multiset<int> L, R;
        
        for(int i=0; i<k; i++)
        {
            L.insert(*--S[u+i].upper_bound(P.y));
            R.insert(*S[u+i].lower_bound(P.y));
        }
        
        for(; u+k<=n+1; u++)
        {
            if( *R.begin()-*L.rbegin()>k )
                ans=P.t;
            
            L.erase(L.find(*--S[u].upper_bound(P.y)));
            R.erase(R.find(*S[u].lower_bound(P.y)));
            L.insert(*--S[u+k].upper_bound(P.y));
            R.insert(*S[u+k].lower_bound(P.y));
        }
        
        if( ans>=0 )
            break;
    }
    
    printf("%d\n", ans);
}
