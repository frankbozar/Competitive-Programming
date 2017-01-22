#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const double INF=1e10;
const double EPS=1e-8;
#define pole pair<int,int>
#define x first
#define y second

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        double pri=rand(), key, lvl, rvl, lfl=INF, rfl=-INF;
        node(double _key) : key(_key), lvl(_key), rvl(_key){}
    } *root=NULL;
    
    static void set(node* p, double lfl, double rfl)
    {
        if( p!=NULL )
        {
            p->lfl=min(p->lfl, lfl);
            p->lvl=min(p->lvl, lfl);
            p->rfl=max(p->rfl, rfl);
            p->rvl=max(p->rvl, rfl);
        }
    }
    
    static void push(node* p)
    {
        if( p!=NULL )
        {
            set(p->l, p->lfl, p->rfl);
            set(p->r, p->lfl, p->rfl);
            p->lfl=INF, p->rfl=-INF;
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
            return l;
        }
        else
        {
            push(r);
            r->l=merge(l, r->l);
            return r;
        }
    }
    
    static void split(node* p, double k, node*& l, node*& r)
    {
        if( p==NULL )
            l=r=NULL;
        else if( p->key<k )
        {
            l=p;
            push(l);
            split(l->r, k, l->r, r);
        }
        else
        {
            r=p;
            push(r);
            split(r->l, k, l, r->l);
        }
    }
    
    void insert(double key)
    {
        node *l, *r;
        split(root, key-EPS, l, r);
        root=merge(l, new node(key));
        root=merge(root, r);
    }
    
    void query(int beg, int end)
    {
        int mid=(beg+end)>>1;
        node *l, *r;
        
        split(root, beg-EPS, l, root);
        split(root, mid+EPS, root, r);
        set(root, beg, -INF);
        root=merge(l, root);
        root=merge(root, r);
        
        split(root, mid-EPS, l, root);
        split(root, end+EPS, root, r);
        set(root, INF, end);
        root=merge(l, root);
        root=merge(root, r);
    }
    
    static void get(node* p, vector<double>& a)
    {
        if( p!=NULL )
        {
            push(p);
            get(p->l, a);
            a.push_back(max(p->key-p->lvl, p->rvl-p->key));
            get(p->r, a);
        }
    }
    
    vector<double> get()
    {
        vector<double> ans;
        get(root, ans);
        return ans;
    }
};

double area(double h, double l, double r=0)
{
    assert( h>=0 && l>=0 && r>=0 );
    
        
    return (l+r)*h*.5;
}

double area(double a, double b, double c, double d, double l, double r)
{
    if( a<b )
    {
        if( c<d )
            return area(r-l, a, d);
        
        double p=((d-a)+(r-l))*.5;
        double q=((d-a)-(r-l))*.5;
        return area(p, a, a+p)+area(q, d, d+q);
    }
    else
    {
        if( c>d )
            return area(r-l, a, d);
        
        double p=((r-l)+(a-d))*.5;
        double q=((r-l)-(a-d))*.5;
        return area(p, a, a-p)+area(q, d, d-q);
    }
}

double solve(vector<pole>& p, int n)
{
    sort(p.begin(), p.end());
    treap T;
    
    for(int i=0; i<n; i++)
    {
        T.insert(p[i].x-.5);
        T.insert(p[i].x);
        T.insert(p[i].x+.5);
    }
    
    for(int i=0; i<n; i++)
        T.query(p[i].x-p[i].y, p[i].x+p[i].y);
    
    vector<double> h=T.get();
    double ans=0;
    
    for(int i=0; i<n; i++)
    {
        if( i==0 )
            ans+=area(h[1], h[1]);
        
        if( i==n-1 )
            ans+=area(h[n*3-2], h[n*3-2]);
        else
            ans+=area(h[i*3+1], h[i*3+2], h[i*3+3], h[i*3+4], p[i].x, p[i+1].x);
    }
    
    return ans;
}

struct data
{
    lld x, a, b, c;
    
    void read()
    {
        scanf("%lld%lld%lld%lld", &x, &a, &b, &c);
    }
    
    int gen()
    {
        int ans=x;
        x=(x*a+b)%c+1;
        return ans;
    }
};

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n;
        scanf("%d", &n);
        vector<pole> p;
        data X, Y;
        X.read();
        Y.read();
        
        for(int i=0; i<n; i++)
            p.push_back(pole(X.gen(), Y.gen()));
        
        /*
        
        for(int i=0; i<n; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            p.push_back(pole(x, y));
        }
        */
        printf("Case #%d: %f\n", cases, solve(p, n));
    }
}

/*

3

1
4 2

2
4 2
6 3

3
4 2
6 3
5 1

*/
/*

1
5
1 1 0 100
1 0 0 100

*/
