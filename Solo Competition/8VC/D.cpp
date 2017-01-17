#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), key, siz=1;
        node(int _key) : key(_key){}
    } *root=NULL;
    
    static int size(const node* p)
    {
        return p==NULL ? 0 : p->siz ;
    }
    
    static void pull(node* p)
    {
        if( p!=NULL )
            p->siz=size(p->l)+1+size(p->r);
    }
    
    static void split(node* p, int k, node*& l, node*& r)
    {
        if( p==NULL )
            l=r=NULL;
        else if( p->key<k )
        {
            l=p;
            split(l->r, k, l->r, r);
            pull(l);
        }
        else
        {
            r=p;
            split(r->l, k, l, r->l);
            pull(r);
        }
    }
    
    static node* merge(node* l, node* r)
    {
        if( l==NULL )
            return r;
        else if( r==NULL )
            return l;
        else if( l->pri>r->pri )
        {
            l->r=merge(l->r, r);
            pull(l);
            return l;
        }
        else
        {
            r->l=merge(l, r->l);
            pull(r);
            return r;
        }
    }
    
    int query(int p, int q)
    {
        int u=min(p, q);
        int v=max(p, q);
        node *l, *r, *x, *y;
        split(root, u, l, root);
        split(root, u+1, x, root);
        split(root, v+1, root, r);
        split(root, v, root, y);
        int ans= p<q ? size(root) : size(l)+size(r);
        x=merge(x, new node(u));
        y=merge(new node(v), y);
        l=merge(l, x);
        r=merge(y, r);
        root=merge(l, root);
        root=merge(root, r);
        return ans;
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    m=min(m, n-m);
    lld cnt=1;
    treap T;
    
    for(int p=0, i=1; i<=n; i++)
    {
        int q=(p+m)%n;
        cnt+=T.query(p, q)+1;
        p=q;
        printf(i==n ? "%lld\n" : "%lld ", cnt);
    }
}
