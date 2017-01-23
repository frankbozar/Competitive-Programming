#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
using namespace std;
typedef long long lld;
const lld mod=1000000007;

struct matrix
{
    lld a[2][2];
    
    matrix(int p=0, int q=0, int r=0, int s=0)
    {
        a[0][0]=p%mod;
        a[0][1]=q%mod;
        a[1][0]=r%mod;
        a[1][1]=s%mod;
    }
    
    matrix operator*(const matrix& M) const
    {
        matrix p;
        p.a[0][0]=(a[0][0]*M.a[0][0]+a[0][1]*M.a[1][0])%mod;
        p.a[0][1]=(a[0][0]*M.a[0][1]+a[0][1]*M.a[1][1])%mod;
        p.a[1][0]=(a[1][0]*M.a[0][0]+a[1][1]*M.a[1][0])%mod;
        p.a[1][1]=(a[1][0]*M.a[0][1]+a[1][1]*M.a[1][1])%mod;
        return p;
    }
    
    matrix operator+(const matrix& M) const
    {
        matrix p;
        p.a[0][0]=(a[0][0]+M.a[0][0])%mod;
        p.a[0][1]=(a[0][1]+M.a[0][1])%mod;
        p.a[1][0]=(a[1][0]+M.a[1][0])%mod;
        p.a[1][1]=(a[1][1]+M.a[1][1])%mod;
        return p;
    }
    
    matrix operator^(int n) const
    {
        matrix p(1, 0, 0, 1);
        
        for(matrix t=*this; n>0; n>>=1)
        {
            if( n&1 )
                p=p*t;
            
            t=t*t;
        }
        
        return p;
    }
};

matrix fib(const int n)
{
    return matrix(1, 1, 1, 0)^n;
}

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), siz=1;
        matrix m, sm, add;
        
        node(int n) : add(1, 0, 0, 1)
        {
            m=sm=fib(n-1);
        }
    } *root=NULL;
    
    static int size(const node* p)
    {
        return p==NULL ? 0 : p->siz ;
    }
    
    static matrix get(const node* p)
    {
        return p==NULL ? matrix() : p->sm ;
    }
    
    static void set(node* p, matrix n)
    {
        if( p!=NULL )
        {
            p->add=p->add*n;
            p->m=p->m*n;
            p->sm=p->sm*n;
        }
    }
    
    static void pull(node* p)
    {
        if( p!=NULL )
        {
            p->siz=size(p->l)+1+size(p->r);
            p->sm=get(p->l)+p->m+get(p->r);
        }
    }
    
    static void push(node* p)
    {
        if( p!=NULL )
        {
            set(p->l, p->add);
            set(p->r, p->add);
            p->add=matrix(1, 0, 0, 1);
        }
    }
    
    static node* merge(node *l, node* r)
    {
        if( l==NULL )
            return r;
        else if( r==NULL )
            return l;
        else if( l->pri>r->pri )
        {
            push(l);
            l->r=merge(l->r, r);
            pull(l);
            return l;
        }
        else
        {
            push(r);
            r->l=merge(l, r->l);
            pull(r);
            return r;
        }
    }
    
    static void split(node* p, const int k, node*& l, node*& r)
    {
        push(p);
        
        if( p==NULL )
            l=r=NULL;
        else if( size(p->l)+1<=k )
        {
            l=p;
            split(l->r, k-size(p->l)-1, l->r, r);
            pull(l);
        }
        else
        {
            r=p;
            split(r->l, k, l, r->l);
            pull(r);
        }
    }
    
    void append(int n)
    {
        root=merge(root, new node(n));
    }
    
    void modify(int x, int y, int n)
    {
        node *l, *r;
        split(root, y, root, r);
        split(root, x-1, l, root);
        set(root, fib(n));
        root=merge(l, root);
        root=merge(root, r);
    }
    
    int query(int x, int y)
    {
        node *l, *r;
        split(root, y, root, r);
        split(root, x-1, l, root);
        int ans=root->sm.a[0][0];
        root=merge(l, root);
        root=merge(root, r);
        return ans;
    }
} T;

int main()
{
    int n, m;
    
    for(scanf("%d%d", &n, &m); n>0; n--)
    {
        int x;
        scanf("%d", &x);
        T.append(x);
    }
    
    for(; m>0; m--)
    {
        int o;
        scanf("%d", &o);
        
        if( o==1 )
        {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            T.modify(l, r, x);
        }
        else//if( o==2 )
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", T.query(l, r));
        }
    }
}

/*

5 4
1 1 2 1 1
2 1 5
1 2 4 2
2 2 4
2 1 5

*/
