#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long lld;

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), key;
        lld val, svl;
        node(int _key, int _val) : key(_key), val(_val), svl(_val){}
    } *root;
    
    treap(int key, int val)
    {
        root=new node(key, val);
    }
    
    static void pull(node* p)
    {
        if( p!=NULL )
            p->svl=eval(p->l)+p->val+eval(p->r);
    }
    
    static lld eval(const node* p)
    {
        return p==NULL ? 0 : p->svl ;
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
    
    lld merge(treap T)
    {
        return merge(T.root);
    }
    
    lld merge(node* p)
    {
        if( p==NULL )
            return 0;
        
        merge(p->l);
        merge(p->r);
        p->l=p->r=NULL;
        pull(p);
        node *l, *r;
        split(root, p->key, l, r);
        lld ans=eval(l);
        root=merge(l, p);
        root=merge(root, r);
        return ans;
    }
};

int size(const vector<vector<int>>& e, int u)
{
    static vector<int> s(1<<20, 1);
    int& ans=s[u];
    
    if( ans<=(int)e[u].size() )
        for(int v : e[u])
            ans+=size(e, v);
    
    return ans;
}

treap dfs(vector<lld>& ans, const vector<int>& key, const vector<int>& val, const vector<vector<int>>& e, int u)
{
    treap S(key[u], val[u]);
    
    if( e[u].empty() )
        return S;
    
    int t=e[u].front();
    
    for(int v : e[u])
        if( size(e, t)<size(e, v) )
            t=v;
    
    treap T=dfs(ans, key, val, e, t);
    
    for(int v : e[u])
        if( v!=t )
            T.merge(dfs(ans, key, val, e, v));
    
    ans[u]=T.merge(S);
    return T;
}

int main()
{
    int n, r=0;
    scanf("%d", &n);
    vector<vector<int>> e(n+1);
    vector<int> key(n+1, 0), val(n+1, 0);
    
    for(int i=1; i<=n; i++)
    {
        int p;
        scanf("%d%d%d", &p, &key[i], &val[i]);
        
        if( p<0 )
            r=i;
        else
            e[p].push_back(i);
    }
    
    vector<lld> ans(n+1, 0);
    dfs(ans, key, val, e, r);
    
    for(int i=1; i<=n; i++)
        printf("%lld\n", ans[i]);
}

/*

5
4 4 80
1 1 40
-1 10 50
3 5 50
4 8 70

*/
