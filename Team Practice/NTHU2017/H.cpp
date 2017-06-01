#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<50;

struct data
{
    lld v;
    data* p;
    data(int _v, data* _p) : v(_v), p(_p){}
};

int main()
{
    for(int n; scanf("%d", &n)!=EOF; )
    {
        vector<lld> a(n+1, INF);
        vector<data*> b(n+1, NULL), c;
        
        for(int i=0; i<n; i++)
        {
            lld x;
            scanf("%lld", &x);
            int j=lower_bound(a.begin(), a.end(), x)-a.begin();
            a[j]=x;
            b[j]=new data(x, j==0 ? NULL : b[j-1]);
            c.push_back(b[j]);
        }
        
        for(int i=n; i>=0; i--)
        {
            if( b[i]!=NULL )
            {
                a.clear();
                
                for(data* p=b[i]; p!=NULL; p=p->p)
                    a.push_back(p->v);
                
                for(; !a.empty(); a.pop_back())
                    printf("%lld ", a.back());
                
                printf("\n");
                break;
            }
        }
        
        for(; !c.empty(); c.pop_back())
            delete c.back();
    }
}
