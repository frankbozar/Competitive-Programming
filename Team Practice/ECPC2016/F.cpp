#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
#define chess pair<int,lld>
#define x first
#define p second

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        lld key;
        int pri=rand(), val, mvl;
        node(lld _key, int _val) : key(_key), val(_val), mvl(_val){}
        
        ~node()
        {
            delete l;
            delete r;
        }
    } *root=NULL;
    
    ~treap()
    {
        delete root;
    }
    
    static int get(const node* p)
    {
        return p==NULL ? 0 : p->mvl ;
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
    
    static void split(node* p, lld k, node*& l, node*& r)
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
    
    void insert(lld key, int val)
    {
        node *l, *r;
        split(root, key, l, r);
        root=merge(l, new node(key, val));
        root=merge(root, r);
    }
    
    int query(lld key)
    {
        node *l, *r;
        split(root, key, l, r);
        int ans=get(r);
        root=merge(l, r);
        return ans;
    }
    
    int get() const
    {
        return get(root);
    }
};

int cal(vector<chess> a, int c)
{
    sort(a.rbegin(), a.rend());
    treap T;
    
    for(const chess& b : a)
    {
        int val=T.query(b.x+b.p+c-1)+1;
        T.insert(b.x-b.p, val);
    }
    
    return T.get();
}

int main()
{
    freopen("bishops.in", "rb", stdin);
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m, k, ans=0;
        scanf("%d%d%d", &n, &m, &k);
        vector<vector<chess>> d(n*2+1), D(n*2+1);
        
        for(; m>0; m--)
        {
            int x, y, p;
            scanf("%d%d%d", &x, &y, &p);
            const chess c(x, p*(lld)p);
            d[x+y].push_back(c);
            D[x-y+n].push_back(c);
        }
        
        for(const auto& it : d)
            ans=max(ans, cal(it, k));
        
        for(const auto& it : D)
            ans=max(ans, cal(it, k));
        
        printf("%d\n", ans);
    }
}
