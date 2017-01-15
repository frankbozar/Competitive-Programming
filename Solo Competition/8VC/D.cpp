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
    
    vector<bool> in;
    treap(int n) : in(n, false){}
    
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
    
    int query(int n, int m, int& p)
    {
        
        
        
        if( u>v )
            swap(u, v);
        
        node *l, *r;
        split(root, u+1, l, root);
        split(root, v, root, r);
        int ans=size(root);
        
        if( !in[u] )
        {
            root=merge(new node(u), root);
            in[u]=true;
        }
        
        if( !in[v] )
        {
            root=merge(root, new node(v));
            in[v]=true;
        }
        
        root=merge(l, root);
        root=merge(root, r);
        return ans;
    }
    
    static void show(const node* p)
    {
        if( p!=NULL )
        {
            show(p->l);
            printf("%d ", p->key);
            show(p->r);
        }
    }
    
    void show() const
    {
        show(root);
        printf("\n");
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    lld cnt=1;
    treap T(n);
    
    for(int p=0, i=1; i<=n; i++)
    {
        cnt+=T.query(n, m, p)+1;
        printf(i==n ? "%lld\n" : "%lld ", cnt);
    }
}
