#include<cstdio>
#include<set>
#include<vector>
using namespace std;

struct data
{
    int u, v, i;
    data(int _u=0, int _v=0, int _i=0) : u(_u), v(_v), i(_i){}
    
    bool operator<(const data& D) const
    {
        return u+v==D.u+D.v ? u<D.u : u+v<D.u+D.v ;
    }
};

bool sol(int n, vector<int>& u, vector<int>& v, vector<int>& p, vector<int>& b)
{
    multiset<data> S;
    
    for(int i=0; i<n; i++)
        S.insert(data(u[i], v[i], i));
    
    for(; S.size()>1; )
    {
        auto it=--S.end();
        data D=*it;
        S.erase(it);
        it=S.find(data(D.u-1, D.v+1));
        
        if( it==S.end() )
            return false;
        
        b[D.i]=0;
        b[it->i]=1;
        p[D.i]=p[it->i]=n;
        S.erase(it);
        S.insert(data(D.u-1, D.v, n++));
    }
    
    const data& D=*S.begin();
    return D.u+D.v==0;
}

void print(const vector<int>& p, const vector<int>& b, int u, bool init=false)
{
    if( p[u]>=0 )
    {
        print(p, b, p[u]);
        printf("%d", b[u]);
    }
    
    if( init )
        printf("\n");
}

int main()
{
    freopen("huffman.in", "rb", stdin);
    freopen("huffman.out", "wb", stdout);
    
    for(int n; scanf("%d", &n) && n>0; )
    {
        vector<int> u(n), v(n), p(n<<1, -1), b(n<<1);
        
        for(int i=0; i<n; i++)
            scanf("%d%d", &u[i], &v[i]);
        
        if( !sol(n, u, v, p, b) )
            printf("No\n");
        else
        {
            printf("Yes\n");
            
            for(int i=0; i<n; i++)
                print(p, b, i, true);
        }
    }
}
