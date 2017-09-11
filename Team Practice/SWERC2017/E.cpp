#include<cctype>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<10;
const int M=1000003;
const char* an="1234567890qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";

int convert(int c)
{
    switch( c )
    {
        case '0':
            return 'o';
        case '1':
            return 'i';
        case '3':
            return 'e';
        case '5':
            return 's';
        case '7':
            return 't';
        default:
            return tolower(c);
    }
}

int type(char c)
{
    if( 'a'<=c && c<='z' )
        return 1;
    else if( 'A'<=c && c<='Z' )
        return 2;
    else
        return 4;
}

struct actrie
{
    struct node
    {
        int cnt, d;
        node *fl, *dl, *nx[128];
    } a[N];
    
    int n;
    node* root;
    
    actrie()
    {
        memset(this, 0, sizeof(actrie));
        root=a;
    }
    
    void insert(const char* s)
    {
        node* p=root;
        
        for(; *s; s++)
        {
            node*& t=p->nx[convert(*s)];
            if( !t ) t=&a[++n];
            p=t;
        }
        
        p->cnt++;
    }
    
    void build()
    {
        queue<node*> Q;
        
        for(Q.push(root); !Q.empty(); Q.pop())
        {
            node* now=Q.front();
            
            for(int i=0; i<128; i++)
            {
                node*& t=now->nx[i];
                node* fn=now->fl;
                
                if( t )
                {
                    for(; fn && !fn->nx[i]; fn=fn->fl);
                    t->fl= fn ? fn->nx[i] : root ;
                    t->dl= t->fl->cnt ? t->fl : t->fl->dl ;
                    t->d=now->d+1;
                    Q.push(t);
                }
            }
        }
    }
    
    bool black(int x) const
    {
        return a[x].cnt || a[x].dl;
    }
    
    int next(int x, int y) const
    {
        y=convert(y);
        const node* now=&a[x];
        for(; now && !now->nx[y]; now=now->fl);
        return now ? now->nx[y]-a : 0 ;
    }
} T;

int main()
{
    int l, r, n, ans=0;
    
    for(scanf("%d%d%d", &l, &r, &n); n>0; n--)
    {
        char s[32];
        scanf("%s", s);
        T.insert(s);
    }
    
    T.build();
    vector<vector<int>> d(N, vector<int>(8, 0));
    d[0][0]=1;
    
    for(int k=1; k<=r; k++)
    {
        vector<vector<int>> p(N, vector<int>(8, 0));
        
        for(int i=0; i<=T.n; i++)
            for(int j=0; j<8; j++)
                for(const char* s=an; *s; s++)
                {
                    int u=T.next(i, *s);
                    int v=j|type(*s);
                    p[u][v]+=d[i][j];
                    
                    if( p[u][v]>=M )
                        p[u][v]-=M;
                }
        
        swap(d, p);
        
        for(int i=0; i<=T.n; i++)
        {
            if( T.black(i) )
                for(int j=0; j<8; j++)
                    d[i][j]=0;
            
            if( k>=l )
                ans+=d[i][7];
            
            if( ans>=M )
                ans-=M;
        }
    }
    
    printf("%d\n", ans);
}

/*

3 5
9
swerc
icpc
fbi
cia
bio
z
hi
no
yes

*/
