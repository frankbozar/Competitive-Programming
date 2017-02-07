#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long lld;
const int N=1<<20;

struct user
{
    int i, p, a, b;
};

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), key;
        lld lft=0, val=0, alt=0, add=0, mvl=0, ans=0;
        node(int _key) : key(_key){}
    } *root=NULL;
    
    void insert(int n)
    {
        node *l, *r;
        split(root, n, l, r);
        root=merge(l, new node(n));
        root=merge(root, r);
    }
    
    static void pull(node* p)
    {
        if( p==NULL )
            return ;
        
        p->mvl=p->val+p->lft;
        p->ans=p->val;
        
        if( p->l!=NULL )
        {
            p->mvl=max(p->mvl, p->l->mvl);
            p->ans=max(p->ans, p->l->ans);
        }
        
        if( p->r!=NULL )
        {
            p->mvl=max(p->mvl, p->r->mvl);
            p->ans=max(p->ans, p->r->ans);
        }
    }
    
    static void push(node* p)
    {
        if( p==NULL )
            return ;
        
        seta(p->l, p->add, p->alt);
        seta(p->r, p->add, p->alt);
        p->add=p->alt=0;
    }
    
    static void seta(node* p, lld x, lld y)
    {
        if( p==NULL )
            return ;
        
        p->lft+=x;
        
        if( p->val<p->val+p->lft )
        {
            p->val+=p->lft;
            p->lft=0;
        }
        
        p->lft+=y;
        p->alt+=x;
        
        if( p->add<p->add+p->alt )
        {
            p->add+=p->alt;
            p->alt=0;
        }
        
        p->alt+=y;
        p->ans=max(p->ans, max(p->val, p->mvl+x));
        p->mvl+=x+y;
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
        if( p==NULL )
            l=r=NULL;
        else if( p->key<k )
        {
            l=p;
            push(l);
            split(l->r, k, l->r, r);
            pull(l);
        }
        else
        {
            r=p;
            push(r);
            split(r->l, k, l, r->l);
            pull(r);
        }
    }
    
    void add(int x, int a, int b)
    {
        node *l, *r;
        split(root, a, l, root);
        split(root, b+1, root, r);
        seta(root, x, 0);
        root=merge(l, root);
        root=merge(root, r);
    }
    
    lld ask(int a, int b)
    {
        node *l, *r;
        split(root, a, l, root);
        split(root, b+1, root, r);
        lld ans=root->ans;
        root=merge(l, root);
        root=merge(root, r);
        return ans;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    vector<vector<user>> a(N);
    vector<lld> ans(n);
    treap T;
    
    for(int i=0; i<n; i++)
    {
        int r;
        user u;
        u.i=i;
        scanf("%d%d%d%d", &r, &u.p, &u.a, &u.b);
        a[r].push_back(u);
        T.insert(u.a);
        T.insert(u.b);
    }
    
    for(int i=1; i<N; i++)
    {
        for(const user& U : a[i-1])
            T.add(U.p, U.a, U.b);
        
        for(const user& U : a[i])
            ans[U.i]=T.ask(U.a, U.b)+U.p;
    }
    
    for(int i=0; i<n; i++)
        printf("%lld\n", ans[i]);
}

/*

4
15 22 2 5
13 -7 5 8
9 -5 3 7
12 13 5 6

*/
