#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;

struct treap
{
    struct node
    {
        node *l=NULL, *r=NULL;
        int pri=rand(), key, val=0, mvl=0, svl=0, avl=0;
        node(int _key) : key(_key){}
    } *root=NULL;
    
    treap(int n)
    {
        for(int i=0; i<n; i++)
            root=merge(root, new node(i));
    }
    
    static void add(node* p, int val)
    {
        if( p!=NULL )
        {
            p->val+=val;
            p->avl+=val;
            p->svl+=val;
            p->mvl+=val;
        }
    }
    
    static void set(node* p, int val)
    {
        if( p!=NULL )
        {
            add(p->l, p->avl);
            add(p->r, p->avl);
            p->avl=0;
            p->val=max(p->val, val);
            p->svl=max(p->svl, val);
            p->mvl=max(p->mvl, val);
        }
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
    
    static void push(node* p)
    {
        if( p!=NULL )
        {
            add(p->l, p->avl);
            add(p->r, p->avl);
            p->avl=0;
            set(p->l, p->svl);
            set(p->r, p->svl);
            p->svl=0;
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
    
    void query(int a, int b)
    {
        node *l, *m, *r;
        split(root, a, l, root);
        split(root, b+1, m, r);
        add(m, 1);
        set(r, get(m));
        root=merge(l, m);
        root=merge(root, r);
    }
    
    int get()
    {
        return get(root);
    }
};

int main()
{
    for(int n; scanf("%d", &n) && n>0; )
    {
        treap T(n);
        
        for(; n>0; n--)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            T.query(l, r);
        }
        
        printf("%d\n", T.get());
    }
}

/*

5
1 3
0 1
3 4
0 0
2 3
0

*/
