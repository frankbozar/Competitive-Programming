#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long double lld;

struct vec
{
    lld d;
    int i;
    vec(lld _x, lld _y, int _i) : d(atan2(_y, _x)), i(_i){}
    
    bool operator<(const vec& V) const
    {
        return d<V.d;
    }
};

int main()
{
    int n, ans=1;
    scanf("%d", &n);
    vector<vec> a;
    
    for(int i=1; i<=n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        a.push_back(vec(x, y, i));
    }
    
    sort(a.begin(), a.end());
    a.push_back(a.front());
    a.back().d+=atan(1)*8;
    
    for(int i=2; i<=n; i++)
        if( a[ans].d-a[ans-1].d>a[i].d-a[i-1].d )
            ans=i;
    
    printf("%d %d\n", a[ans].i, a[ans-1].i);
}
