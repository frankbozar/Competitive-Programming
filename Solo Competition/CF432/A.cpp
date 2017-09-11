#include<cstdio>
#include<vector>
using namespace std;

struct point
{
    int a[5]={0}, id=0;
    
    void read(int _id)
    {
        id=_id;
        
        for(int i=0; i<5; i++)
            scanf("%d", &a[i]);
    }
    
    point operator-(const point& P) const
    {
        point ans;
        
        for(int i=0; i<5; i++)
            ans.a[i]=a[i]-P.a[i];
        
        return ans;
    }
    
    int operator()() const
    {
        int ans=0;
        
        for(int i=0; i<5; i++)
            ans+=a[i]*a[i];
        
        return ans;
    }
};

bool ok(const point& A, const point& B, const point& C)
{
    int a=(B-C)();
    int b=(C-A)();
    int c=(A-B)();
    return a>=b+c;
}

void sol(vector<point>& a)
{
    vector<point> b=a;
    
    while( b.size()>=3 )
    {
        vector<point> c;
        
        while( b.size()>=3 )
        {
            const point& A=b[b.size()-1];
            const point& B=b[b.size()-2];
            const point& C=b[b.size()-3];
            
            if( ok(A, B, C) )
                c.push_back(A);
            else if( ok(B, C, A) )
                c.push_back(B);
            else if( ok(C, A, B) )
                c.push_back(C);
            
            b.pop_back();
            b.pop_back();
            b.pop_back();
        }
        
        for(; !b.empty(); b.pop_back())
            c.push_back(b.back());
        
        b=c;
    }
    
    int n=a.size();
    vector<point> c;
    
    for(const point& P : b)
    {
        bool flag=true;
        
        for(int i=0; i<n; i++)
            if( a[i].id!=P.id )
                for(int j=i+1; j<n; j++)
                    if( a[j].id!=P.id && !ok(P, a[i], a[j]) )
                        flag=false;
        
        if( flag )
            c.push_back(P);
    }
    
    a=c;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<point> a(n);
    
    for(int i=0; i<n; i++)
        a[i].read(i+1);
    
    sol(a);
    n=a.size();
    printf("%d\n", n);
    
    for(int i=0; i<n; i++)
        printf(i==n-1 ? "%d\n" : "%d ", a[i].id);
}
