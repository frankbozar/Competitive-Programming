#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;

struct node
{
    node *l=NULL, *r=NULL;
    int pri, val;
    node(int _val) : pri(rand()), val(_val){}
};

struct treap
{
    node *root=NULL;
    
    static void split(node* p, int k, node*& l, node*& r)
    {
        if( p==NULL )
            l=r=NULL;
        else if( p->val<k )
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
    
    void append(int x)
    {
        root=merge(root, new node(x));
    }
    
    static void print(const node* p)
    {
        if( p!=NULL )
        {
            print(p->l);
            printf(" %d", p->val);
            print(p->r);
        }
    }
};

vector<int> plist(int n)
{
    vector<int> p;
    vector<bool> isp(n, true);
    isp[0]=isp[1]=false;
    
    for(int i=2; i<n; i++)
        if( isp[i] )
        {
            p.push_back(i);
            
            for(int j=i*i; j<n; j+=i)
                isp[j]=false;
        }
    
    return p;
}

const int N=500;

struct data
{
    vector<int> p;
    vector<treap> t;
    
    data(int n) : p(plist(N)), t(N)
    {
        for(int i=0; i<n; i++)
        {
            int x;
            scanf("%d", &x);
            t[x%N].append(i);
        }
    }
    
    void add(int a, int b, int v)
    {
        vector<node*> l, m, r;
        split(a, b, l, m, r);
        merge(l, m, r, v%N);
    }
    
    int query(int a, int b)
    {
        vector<node*> l, m, r;
        split(a, b, l, m, r);
        int ans=0;
        
        for(int x : p)
            if( m[x]!=NULL )
                ans++;
        
        merge(l, m, r);
        return ans;
    }
    
    void split(int a, int b, vector<node*>& l, vector<node*>& m, vector<node*>& r)
    {
        l.resize(N);
        m.resize(N);
        r.resize(N);
        
        for(int i=0; i<N; i++)
        {
            treap::split(t[i].root, a, l[i], m[i]);
            treap::split(m[i], b+1, m[i], r[i]);
        }
    }
    
    void merge(vector<node*>& l, vector<node*>& m, vector<node*>& r, int v=0)
    {
        for(int i=0; i<N; i++)
        {
            t[i].root=treap::merge(l[i], m[(i+N-v)%N]);
            t[i].root=treap::merge(t[i].root, r[i]);
        }
    }
};

int main()
{
    for(int n; scanf("%d", &n)!=EOF; )
    {
        data D(n);
        int m;
        
        for(scanf("%d", &m); m>0; m--)
        {
            char s[8]={0};
            scanf("%s", s);
            
            if( s[0]=='q' )
            {
                int l, r;
                scanf("%d%d", &l, &r);
                printf("%d\n", D.query(l, r));
            }
            else
            {
                int l, r, v;
                scanf("%d%d%d", &l, &r, &v);
                D.add(l, r, v);
            }
        }
    }
}
