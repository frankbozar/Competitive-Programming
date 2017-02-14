#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=0x3FFFFFFF;

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), val, lvl, rvl, ans=INF;
        node(int _val) : val(_val), lvl(_val), rvl(_val){}
    } *root=NULL;
    
    static void pull(node* p)
    {
        if( p==NULL )
            return ;
        
        p->lvl=p->rvl=p->val;
        p->ans=INF;
        
        if( p->l!=NULL )
        {
            p->lvl=p->l->lvl;
            p->ans=min(p->ans, p->l->ans);
            p->ans=min(p->ans, p->val-p->l->rvl);
        }
        
        if( p->r!=NULL )
        {
            p->rvl=p->r->rvl;
            p->ans=min(p->ans, p->r->ans);
            p->ans=min(p->ans, p->r->lvl-p->val);
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
    
    static void split(node* p, int k, node*& l, node*& r)
    {
         if( p==NULL )
             l=r=NULL;
        else if( p->val<k )
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
    
    void insert(int x)
    {
        node *l, *r;
        split(root, x, l, r);
        root=merge(l, new node(x));
        root=merge(root, r);
    }
    
    void erase(int x)
    {
        node *l, *r;
        split(root, x, l, r);
        erase(r);
        root=merge(l, r);
    }
    
    static void erase(node*& p)
    {
        if( p->l==NULL )
            p=p->r;
        else
            erase(p->l);
        
        pull(p);
    }
};

int k;

struct query
{
    int l, r, i;
    query(int _l, int _r, int _i) : l(_l), r(_r), i(_i){}
    
    bool operator<(const query& Q) const
    {
        return l/k==Q.l/k ? r<Q.r : l<Q.l ;
    }
};

int main()
{
    int n, m;
    scanf("%d", &n);
    vector<int> a(n);
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    scanf("%d", &m);
    vector<query> Q;
    
    for(int i=0; i<m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        Q.push_back(query(l-1, r, i));
    }
    
    k=sqrt(n);
    sort(Q.begin(), Q.end());
    vector<int> ans(m);
    treap T;
    
    for(int l=0, r=0, i=0; i<m; i++)
    {
        for(; r<Q[i].r; r++)
            T.insert(a[r]);
            
        for(; l>Q[i].l; l--)
            T.insert(a[l-1]);
        
        for(; l<Q[i].l; l++)
            T.erase(a[l]);
        
        for(; r>Q[i].r; r--)
            T.erase(a[r-1]);
        
        ans[ Q[i].i ]=T.root->ans;
    }
    
    for(int i=0; i<m; i++)
        printf("%d\n", ans[i]);
}

/*

8
3 1 4 1 5 9 2 6
4
1 8
1 3
4 8
5 7

*/
