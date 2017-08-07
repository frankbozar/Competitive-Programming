#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int INF=1000000000;

struct point
{
    lld x, y;
    point(lld _x=0, lld _y=0) : x(_x), y(_y){}
    
    point operator+(const point& P) const
    {
        return point(x+P.x, y+P.y);
    }
    
    point operator-(const point& P) const
    {
        return point(x-P.x, y-P.y);
    }
};

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), key;
        point val=0, avl=0;
        node(lld _key) : key(_key){}
    } *root[1<<20];
    
    int n;
    
    void init(const set<int>& a)
    {
        memset(this, 0, sizeof(treap));
        
        for(lld x : a)
            root[0]=merge_p(root[0], new node(x));
    }
    
    static node* aval(node* p, const point& P)
    {
        if( p==NULL )
            return NULL;
        else
        {
            p=new node(*p);
            p->val=p->val+P;
            p->avl=p->avl+P;
            return p;
        }
    }
    
    static node* push(node* p)
    {
        if( p==NULL )
            return NULL;
        else if( p->avl.x==0 && p->avl.y==0 )
            return new node(*p);
        else
        {
            p=new node(*p);
            p->l=aval(p->l, p->avl);
            p->r=aval(p->r, p->avl);
            p->avl=0;
            return p;
        }
    }
    /*
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
            return l;
        }
        else
        {
            push(r);
            r->l=merge(l, r->l);
            return r;
        }
    }
    */
    static node* merge_p(node* l, node* r)
    {
        if( l==NULL )
            return r;
        else if( r==NULL )
            return l;
        else if( l->pri>r->pri )
        {
            l=push(l);
            l->r=merge_p(l->r, r);
            return l;
        }
        else
        {
            r=push(r);
            r->l=merge_p(l, r->l);
            return r;
        }
    }
    /*
    static void split(node* p, int k, node*& l, node*& r)
    {
        push(p);
        
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
    */
    static void split_p(node* p, int k, node*& l, node*& r)
    {
        p=push(p);
        
        if( p==NULL )
            l=r=NULL;
        else if( p->key<k )
        {
            l=p;
            split_p(l->r, k, l->r, r);
        }
        else
        {
            r=p;
            split_p(r->l, k, l, r->l);
        }
    }
    
    void modify(int x0, int x1, point v0, point v1, point v2)
    {
        node *l, *m, *r;
        split_p(root[n], x0, l, m);
        split_p(m, x1, m, r);
        l=aval(l, v0);
        m=aval(m, v1);
        r=aval(r, v2);
        m=merge_p(l, m);
        root[++n]=merge_p(m, r);
    }
    
    point query(int v, int x)
    {
        node *l, *r;
        split_p(root[v], x, l, r);
        point ans;
        
        for(node* p=l; p!=NULL; p=p->r)
        {
            push(p);
            ans=p->val;
        }
        
        root[v]=merge_p(l, r);
        return ans;
    }
} T;

struct data
{
    int x1, x2, y1, a, b, y2;
    
    data()
    {
        scanf("%d%d%d%d%d%d", &x1, &x2, &y1, &a, &b, &y2);
        x1++;
        x2++;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    vector<data> a;
    set<int> S;
    S.insert(0);
    S.insert(INF);
    
    for(int i=0; i<n; i++)
    {
        a.push_back(data());
        S.insert(a.back().x1);
        S.insert(a.back().x2);
    }
    
    T.init(S);
    
    for(int i=0; i<n; i++)
    {
        T.query(0, 22);
        T.modify(a[i].x1, a[i].x2, point(0, a[i].y1), point(a[i].a, a[i].b), point(0, a[i].y2));
    }
    
    lld last=0;
    
    for(scanf("%d", &n); n>0; n--)
    {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        x=(x+last)%INF;
        point p=T.query(r, *S.upper_bound(x))-T.query(l-1, *S.upper_bound(x));
        last=p.x*x+p.y;
        printf("%lld\n", last);
    }
}

/*

3
2 5 1 1 1 4
3 6 8 2 5 7
1 3 5 1 4 10
1
1 2 22

*/
