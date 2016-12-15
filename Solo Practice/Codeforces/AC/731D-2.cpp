#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;

struct treap
{
    struct node
    {
        int pri, key;
        node *l, *r;
        
        node(int _key)
        {
            pri=rand();
            key=_key;
            l=r=NULL;
        }
    } *root;
    
    treap(int n)
    {
        root=NULL;
        
        for(int i=0; i<n; i++)
            root=merge(root, new node(i));
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
            return l;
        }
        else
        {
            r->l=merge(l, r->l);
            return r;
        }
    }
    
    static void split(node* p, int k, node*& l, node*& r)
    {
        if( p==NULL )
            l=r=NULL;
        else if( p->key<k )
        {
            l=p;
            split(l->r, k, l->r, r);
        }
        else
        {
            r=p;
            split(r->l, k, l, r->l);
        }
    }
    
    void query(int a, int b)
    {
        node *l, *r;
        split(root, b, root, r);
        split(root, a, l, root);
        root=merge(l, r);
    }
    
    int query() const
    {
        if( root==NULL )
            return -1;
        
        for(node *p=root; ; p=p->l)
            if( p->l==NULL )
                return p->key;
    }
};

void solve(const vector<int>& a, const vector<int>& b, int c, treap& T)
{
    for(int n=a.size(), m=b.size(), i=0; ; i++)
    {
        if( i>=n )
            break;
        else if( i>=m )
        {
            T.query(0, c);
            break;
        }
        else if( a[i]<b[i] )
        {
            T.query(c-b[i]+1, c-a[i]+1);
            break;
        }
        else if( a[i]>b[i] )
        {
            T.query(0, c-a[i]+1);
            T.query(c-b[i]+1, c);
            break;
        }
    }
}

int main()
{
    int n, c;
    scanf("%d%d", &n, &c);
    vector<vector<int>> a(n);
    treap T(c);
    
    for(int i=0; i<n; i++)
    {
        int l;
        scanf("%d", &l);
        a[i].resize(l);
        
        for(int j=0; j<l; j++)
            scanf("%d", &a[i][j]);
    }
    
    for(int i=1; i<n; i++)
        solve(a[i-1], a[i], c, T);
    
    printf("%d\n", T.query());
}