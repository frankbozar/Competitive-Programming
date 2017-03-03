#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const int INF=1<<30;

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), key;
        lld val, ans;
        node(int _key=0, lld _val=0) : key(_key), val(_val), ans(_val){}
    } *root=NULL;
    
    static lld get(const node* p)
    {
        return p==NULL ? 0 : p->ans ;
    }
    
    static void pull(node* p)
    {
        if( p!=NULL )
        {
            p->ans=p->val;
            p->ans=max(p->ans, get(p->l));
            p->ans=max(p->ans, get(p->r));
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
    
    lld query(int key)
    {
        node *l, *r;
        split(root, key, l, r);
        lld ans=get(l);
        root=merge(l, r);
        return ans;
    }
    
    void insert(int key, lld val)
    {
        node *l, *r;
        split(root, key, l, r);
        root=merge(l, new node(key, val));
        root=merge(root, r);
    }
};

struct ring
{
    int a, b, h;
    
    bool operator<(const ring& R) const
    {
        return b==R.b ? a>R.a : b>R.b ;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    vector<ring> a(n);
    
    for(int i=0; i<n; i++)
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].h);
    
    sort(a.begin(), a.end());
    lld ans=0;
    treap T;
    
    for(int i=0; i<n; i++)
    {
        lld tmp=T.query(a[i].b)+a[i].h;
        T.insert(a[i].a, tmp);
        ans=max(ans, tmp);
    }
    
    printf("%lld\n", ans);
}
