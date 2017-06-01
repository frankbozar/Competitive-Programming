#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

struct data
{
    int i, *v;
    data(int _i=0, int* _v=NULL) : i(_i), v(_v){}
    
    bool operator<(const data& D) const
    {
        return *v>*D.v;
    }
};

int main()
{
    int n, m, ans=0;
    scanf("%d%d", &n, &m);
    vector<int> a(n), b(n+1), c(n+1), l(n+1), r(n+1);
    priority_queue<data> PQ;
    
    for(int i=0; i<=n; i++)
        c[i]=l[i]=r[i]=i;
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    for(int i=1; i<n; i++)
    {
        b[i]=a[i]-a[i-1];
        PQ.push(data(i, &b[i]));
    }
    
    for(data D; m>0; m--)
    {
        do{
            D=PQ.top();
            PQ.pop();
        }while( c[D.i]!=D.i );
        
        ans+=b[D.i];
        int p=c[ l[D.i]-1 ];
        int q=c[ r[D.i]+1 ];
        b[D.i]=b[p]+b[q]-b[D.i];
        l[D.i]=l[p];
        r[D.i]=r[q];
        c[p]=c[q]=D.i;
        c[ l[D.i] ]=c[ r[D.i] ]=D.i;
        
        if( 0<l[D.i] && r[D.i]<n )
            PQ.push(D);
    }
    
    printf("%d\n", ans);
}
