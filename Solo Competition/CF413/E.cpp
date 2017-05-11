#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), siz=1;
        lld val, sum;
        node(lld _val) : val(_val), sum(_val){}
    } *root=NULL;
    
    static lld get(const node* p)
    {
        return p==NULL ? 0 : p->sum ;
    }
    
    static int size(const node* p)
    {
        return p==NULL ? 0 : p->siz ;
    }
    
    static void pull(node* p)
    {
        if( p!=NULL )
        {
            p->sum=get(p->l)+p->val+get(p->r);
            p->siz=size(p->l)+1+size(p->r);
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
    
    static void split_val(node* p, lld val, node*& l, node*& r)
    {
        if( p==NULL )
            l=r=NULL;
        else if( p->val<val )
        {
            l=p;
            split_val(l->r, val, l->r, r);
            pull(l);
        }
        else
        {
            r=p;
            split_val(r->l, val, l, r->l);
            pull(r);
        }
    }
    
    static void split_siz(node* p, int siz, node*& l, node*& r)
    {
        if( p==NULL )
            l=r=NULL;
        else if( size(p->l)<siz )
        {
            l=p;
            split_siz(l->r, siz-size(p->l)-1, l->r, r);
            pull(l);
        }
        else
        {
            r=p;
            split_siz(r->l, siz, l, r->l);
            pull(r);
        }
    }
    
    void insert(lld v)
    {
        node *l, *r;
        split_val(root, v, l, r);
        root=merge(l, new node(v));
        root=merge(root, r);
    }
    
    void erase(lld v)
    {
        node *l, *r;
        split_val(root, v, l, r);
        split_siz(r, 1, root, r);
        root=merge(l, r);
    }
    
    lld query(int k)
    {
        node *l, *r;
        split_siz(root, k, l, r);
        lld ans=get(l);
        root=merge(l, r);
        return ans;
    }
    
    int size() const
    {
        return size(root);
    }
};

lld f(vector<vector<lld>>& a, int n, int m)
{
    for(int i=0; i<4; i++)
    {
        sort(a[i].begin(), a[i].end());
        int l=a[i].size();
        
        for(int j=1; j<l; j++)
            a[i][j]+=a[i][j-1];
    }
    
    treap T;
    lld ans=INF;
    int p=a[1].size()-1;
    int q=a[2].size()-1;
    int l=a[3].size()-1;
    
    for(int k=0; k<4; k+=3)
        for(int i=a[k].size()-1; i>0; i--)
            T.insert(a[k][i]-a[k][i-1]);
    
    for(int j=0, i=max(0, m-min(p, q)); i<=min(l, m); i++)
    {
        for(; j<i; j++)
            T.erase(a[3][j+1]-a[3][j]);
        
        for(; p>m-i; p--)
            T.insert(a[1][p]-a[1][p-1]);
        
        for(; q>m-i; q--)
            T.insert(a[2][q]-a[2][q-1]);
        
        if( n+i-m-m>=0 && T.size()>=n+i-m-m )
            ans=min(ans, a[3][i]+a[1][m-i]+a[2][m-i]+T.query(n+i-m-m));
    }
    
    return ans;
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<int> a(n), b(n, 0);
    vector<vector<lld>> p(4, vector<lld>(1, 0));
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    for(int l=1; l<=2; l++)
    {
        int t;
        
        for(scanf("%d", &t); t>0; t--)
        {
            int x;
            scanf("%d", &x);
            b[x-1]|=l;
        }
    }
    
    for(int i=0; i<n; i++)
        p[ b[i] ].push_back(a[i]);
    
    lld ans=f(p, m, k);
    printf("%lld\n", ans>=INF ? -1 : ans);
}

/*

4 3 2
3 2 2 1
2
1 2
2
1 3

4 3 2
3 2 2 1
2
1 2
3
4 1 3

4 2 2
3 2 2 1
2
1 2
3
4 1 3

6 6 5
5 6 9 4 9 6
6
5 3 2 1 4 6
6
2 4 1 5 3 6

*/
