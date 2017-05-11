#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define data pair<int,int>
#define x first
#define w second

struct seg
{
    int l, r, w;
    
    void read()
    {
        scanf("%d%d%d", &l, &r, &w);
    }
    
    bool operator<(const seg& S) const
    {
        return r<S.r;
    }
};

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), key, val, mvl, add=0;
        node(int _key, int _val) : key(_key), val(_val), mvl(_val){}
    } *root=NULL;
    
    static int get(const node* p)
    {
        return p==NULL ? 0 : p->mvl ;
    }
    
    static void set(node* p, int x)
    {
        if( p!=NULL )
        {
            p->val+=x;
            p->mvl+=x;
            p->add+=x;
        }
    }
    
    static void push(node* p)
    {
        if( p!=NULL )
        {
            set(p->l, p->add);
            set(p->r, p->add);
            p->add=0;
        }
    }
    
    static void pull(node* p)
    {
        if( p!=NULL )
        {
            p->mvl=p->val;
            p->mvl=max(p->mvl, get(p->l));
            p->mvl=max(p->mvl, get(p->r));
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
    
    static void split(node* p, int k, node*& l, node*& r)
    {
        push(p);
        
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
    
    int query(const seg& S)
    {
        root=merge(root, new node(S.r, 0));
        node *l, *r;
        split(root, S.l, l, r);
        set(r, S.w);
        root=merge(l, r);
        return get(root);
    }
    
    int query() const
    {
        return get(root);
    }
    
    void clear()
    {
        root=NULL;
    }
};

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        vector<seg> a(n);
        vector<data> c;
        
        for(int i=0; i<n; i++)
        {
            a[i].read();
            c.push_back(data(a[i].l, a[i].w));
            c.push_back(data(a[i].r+1, -a[i].w));
            swap(a[i].l, a[i].r);
            a[i].l=-a[i].l;
            a[i].r=-a[i].r;
        }
        
        sort(a.begin(), a.end());
        vector<data> b(n+1);
        treap T;
        
        for(int i=0; i<n; i++)
        {
            b[i+1].w=T.query(a[i]);
            swap(a[i].l, a[i].r);
            a[i].l=-a[i].l;
            a[i].r=-a[i].r;
            b[i+1].x=a[i].l;
        }
        
        sort(c.begin(), c.end());
        sort(a.begin(), a.end());
        T.clear();
        int ans=0;
        
        for(int tmp=0, i=0, j=0, k=n; i<n<<1; i++)
        {
            tmp+=c[i].w;
            
            for(; j<n && a[j].r<c[i].x; j++)
                T.query(a[j]);
            
            for(; k>0 && b[k].x<=c[i].x ; k--)
                ;
            
            ans=max(ans, tmp+T.query()+b[k].w);
        }
        
        printf("%d\n", ans);
    }
}

/*

1

7
0 1 1
1 3 2
2 5 4
4 10 1
4 6 2
7 8 2
10 11 1

*/
