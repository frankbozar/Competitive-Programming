#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int N=1<<20;

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), siz=1, key;
        node(int _key) : key(_key){}
    } *root[N];
    
    int n;
    
    treap()
    {
        memset(this, 0, sizeof(treap));
    }
    
    static int size(const node* p)
    {
        return p==NULL ? 0 : p->siz ;
    }
    
    static void pull(node* p)
    {
        if( p!=NULL )
            p->siz=size(p->l)+1+size(p->r);
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
    
    static node* merge_s(node* l, node* r)
    {
        if( l==NULL )
            return r;
        else if( r==NULL )
            return l;
        else if( l->pri>r->pri )
        {
            l=new node(*l);
            l->r=merge_s(l->r, r);
            pull(l);
            return l;
        }
        else
        {
            r=new node(*r);
            r->l=merge_s(l, r->l);
            pull(r);
            return r;
        }
    }
    
    static void split(node* p, int k, node*& l, node*& r)
    {
        if( p==NULL )
            l=r=NULL;
        else if( p->key<=k )
        {
            l=p;
            split(l->r, k, l->r, r);
            pull(l);
        }
        else
        {
            r=p;
            split(r, k, l, r->l);
            pull(r);
        }
    }
    
    static void split_s(node* p, int k, node*& l, node*& r)
    {
        if( p==NULL )
            l=r=NULL;
        else if( p->key<=k )
        {
            l=new node(*p);
            split_s(l->r, k, l->r, r);
            pull(l);
        }
        else
        {
            r=new node(*p);
            split_s(r, k, l, r->l);
            pull(r);
        }
    }
    
    void insert(int x)
    {
        node *l, *r;
        split_s(root[n++], x, l, r);
        root[n]=merge_s(l, new node(x));
        root[n]=merge_s(root[n], r);
    }
    
    lld query(int x, int y, int s)
    {
        node *l, *r;
        int ans;
        
        if( s==0 )
        {
            split(root[x], y, l, r);
            ans=size(l);
        }
        else
        {
            split(root[x], y-1, l, r);
            ans=size(r);
        }
        
        root[x]=merge(l, r);
        return ans;
    }
} S, T;

lld count(const vector<int>& a, int l, int r, int d, int u)
{
    if( l==r && d==u && a[l]==d )
        return a.size()-2;
    
    lld ans=0;
    return ans;
}

lld solve(const vector<int>& a, int l, int r, int d, int u)
{
    lld ans=0;
    ans+=count(a, l, l, d, d);
    ans+=count(a, r, r, d, d);
    ans+=count(a, l, l, u, u);
    ans+=count(a, r, r, u, u);
    ans-=count(a, l, l, u, d);
    ans-=count(a, r, r, u, d);
    ans-=count(a, l, r, u, u);
    ans-=count(a, l, r, d, d);
    ans+=count(a, l, r, d, u);
    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n+1);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
        S.insert(a[i]);
    }
    
    for(int i=n; i>0; i--)
        T.insert(a[i]);
    
    for(; m>0; m--)
    {
        int l, d, r, u;
        scanf("%d%d%d%d", &l, &d, &r, &u);
        printf("%lld\n", solve(a, l, r, d, u));
    }
}
