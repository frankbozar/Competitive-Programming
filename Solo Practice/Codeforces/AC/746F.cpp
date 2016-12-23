#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

struct DS
{
    int m, k, s=0;
    priority_queue<int, vector<int>, greater<int>> il, dl;
    priority_queue<int> ir, dr;
    DS(int _m, int _k) : m(_m), k(_k){}
    
    void clean()
    {
        while( !il.empty() && !dl.empty() && il.top()==dl.top() )
            il.pop(), dl.pop();
        
        while( !ir.empty() && !dr.empty() && ir.top()==dr.top() )
            ir.pop(), dr.pop();
    }
    
    bool insert(int x)
    {
        clean();
        
        if( s+((x+1)>>1)>k )
            return false;
        
        s+=(x+1)>>1;
        il.push(x);
        
        if( il.size()-dl.size()>m )
        {
            if( s+(il.top()>>1)>k )
            {
                s-=(x+1)>>1;
                dl.push(x);
                return false;
            }
            
            s+=il.top()>>1;
            ir.push(il.top());
            dl.push(il.top());
        }
        
        return true;
    }
    
    void erase(int x)
    {
        clean();
        
        if( x<il.top() )
        {
            s-=x;
            dr.push(x);
        }
        else
        {
            s-=(x+1)>>1;
            dl.push(x);
            
            if( !ir.empty() )
            {
                s-=ir.top()>>1;
                il.push(ir.top());
                dr.push(ir.top());
            }
        }
    }
};

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<int> a(n), t(n);
    
    for(int& x : a)
        scanf("%d", &x);
    
    for(int& x : t)
        scanf("%d", &x);
    
    DS ds(m, k);
    int ans=0, val=0;
    
    for(int l=0, r=0; l<n; l++)
    {
        for(r=max(l, r); r<n && ds.insert(t[r]); r++)
            val+=a[r];
        
        if( l<r )
        {
            ans=max(ans, val);
            ds.erase(t[l]);
            val-=a[l];
        }
    }
    
    printf("%d\n", ans);
}