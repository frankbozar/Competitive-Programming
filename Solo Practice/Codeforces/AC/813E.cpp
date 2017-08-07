#include<cstdio>
#include<cstdlib>
#include<deque>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<17;

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), siz=1, key;
        node(int _key) : key(_key){}
    } *root[N]={0};
    
    int v=0;
    
    static int size(const node* p)
    {
        return p==NULL ? 0 : p->siz ;
    }
    
    static void pull(node* p)
    {
        if( p!=NULL )
            p->siz=size(p->l)+1+size(p->r);
    }
    
    static node* merge(node* l, node * r)
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
    
    static node* merge_p(node* l, node * r)
    {
        if( l==NULL )
            return r;
        else if( r==NULL )
            return l;
        else if( l->pri>r->pri )
        {
            l=new node(*l);
            l->r=merge_p(l->r, r);
            pull(l);
            return l;
        }
        else
        {
            r=new node(*r);
            r->l=merge_p(l, r->l);
            pull(r);
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
            pull(l);
        }
        else
        {
            r=p;
            split(r->l, k, l, r->l);
            pull(r);
        }
    }
    
    static void split_p(node* p, int k, node*& l, node*& r)
    {
        if( p==NULL )
            l=r=NULL;
        else if( p->key<k )
        {
            l=new node(*p);
            split_p(l->r, k, l->r, r);
            pull(l);
        }
        else
        {
            r=new node(*p);
            split_p(r->l, k, l, r->l);
            pull(r);
        }
    }
    
    void append(int x)
    {
        node *l, *r;
        split_p(root[v], x, l, r);
        node* p=merge_p(l, new node(x));
        root[++v]=merge_p(p, r);
    }
    
    int query(int a, int b)
    {
        node *l, *r;
        split(root[b], a, l, r);
        int ans=(b-a+1)-size(r);
        root[b]=merge(l, r);
        return ans;
    }
};

int main()
{
    int n, m, k, p=0;
    scanf("%d%d", &n, &m);
    vector<deque<int>> Q(N, deque<int>(1, 0));
    treap T;
    
    for(int i=1; i<=n; i++)
    {
        int x;
        scanf("%d", &x);
        Q[x].push_back(i);
        T.append(Q[x].front());
        
        if( Q[x].size()>m )
            Q[x].pop_front();
    }
    
    for(scanf("%d", &k); k>0; k--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l=(l+p)%n+1;
        r=(r+p)%n+1;
        
        if( l>r )
            swap(l, r);
        
        p=T.query(l, r);
        printf("%d\n", p);
    }
}
