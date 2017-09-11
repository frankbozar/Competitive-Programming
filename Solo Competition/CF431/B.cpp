#include<cstdio>
#include<map>
#include<deque>
#include<vector>
#include<algorithm>
using namespace std;
#define point pair<int,int>
#define x first
#define y second

struct dancer
{
    int p, t, i, ii;
    dancer(int _p, int _t, int _i) : p(_p), t(_t), i(_i), ii(_i){}
    
    bool operator<(const dancer& D) const
    {
        return p<D.p;
    }
};

int main()
{
    int n, w, h;
    scanf("%d%d%d", &n, &w, &h);
    map<int, vector<dancer>> V, H;
    vector<point> ans(n);
    
    for(int i=0; i<n; i++)
    {
        int g, p, t;
        scanf("%d%d%d", &g, &p, &t);
        
        if( g==1 )
        {
            ans[i]=point(p, h);
            V[p].push_back(dancer(p, t, i));
        }
        else//if( g==2 )
        {
            ans[i]=point(w, p);
            H[p-t].push_back(dancer(p, t, i));
        }
    }
    
    map<int, deque<int>> a;
    
    for(auto& it : H)
    {
        sort(it.second.begin(), it.second.end());
        
        for(const dancer& D : it.second)
            a[it.first].push_back(D.i);
    }
    
    for(auto& it : V)
    {
        for(auto& D : it.second)
            swap(D.t, D.p);
        
        sort(it.second.begin(), it.second.end());
        
        for(dancer& D : it.second)
        {
            swap(D.t, D.p);
            
            if( a.find(D.p-D.t)==a.end() )
                continue;
            
            auto& d=a[D.p-D.t];
            d.push_front(D.i);
            D.i=d.back();
            d.pop_back();
        }
    }
    
    vector<point> ans2(n);
    
    for(const auto& it : H)
        for(int i=it.second.size()-1; i>=0; i--)
            ans2[a[it.first][i]]=ans[it.second[i].ii];
    
    for(const auto& it : V)
        for(const dancer& D : it.second)
            ans2[D.i]=ans[D.ii];
    
    for(int i=0; i<n; i++)
        printf("%d %d\n", ans2[i].x, ans2[i].y);
}
