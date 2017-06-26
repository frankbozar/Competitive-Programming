#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long lld;
const int N=18;

struct ST{
    int (*f)(int, int);
	int n, a[N][1<<N];
    void init(int _n, bool _t){
        f= _t ? [](int x, int y){return max(x, y);} : [](int x, int y){return min(x, y);} ;
        n=_n;
        memset(a, _t ? 0x00 : 0x10, sizeof(a));
		for(int i=0; i<n; i++)
            scanf("%d", &a[0][i]);
		for(int u=1; u<=lg(n); u++){
			int u2=1<<u, u3=u2>>1;
			for(int i=0; i+u2<=n; i++)
                a[u][i]=f(a[u-1][i], a[u-1][i+u3]);
		}
	}
	int query(int l, int r) const{
        int x=lg(r-l), x2=1<<x;
		return f(a[x][l], a[x][r-x2]);
	}
	static int lg(int x){
		return 30-__builtin_clrsb(x);
	}
} s, t;

int main()
{
    int n;
    scanf("%d", &n);
    s.init(n, 1);
    t.init(n, 0);
    lld ans=0;
    
    for(int i=1; i<=n; i++)
    {
        int p=-1, q=-1;
        
        for(int l=0, r=i; l<r; )
        {
            int m=(l+r)>>1;
            
            if( s.query(m, i)<t.query(m, i) )
                r=m;
            else
                l=p=m+1;
        }
        
        for(int l=0, r=i; l<r; )
        {
            int m=(l+r)>>1;
            
            if( s.query(m, i)>t.query(m, i) )
                l=m+1;
            else
                r=q=m;
        }
        
        if( p>=q && q>=0 )
            ans+=p-q;
    }
    
    printf("%lld\n", ans);
}
