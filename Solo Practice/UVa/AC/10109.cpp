#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

struct frac
{
    lld p, q;
    
    frac(lld _p=0, lld _q=1) : p(_p), q(_q)
    {
        formalize();
    }
    
    void formalize()
    {
        if( q<0 )
            p=-p, q=-q;
        
        lld g=gcd(abs(p), q);
        p/=g, q/=g;
    }
    
    static lld gcd(lld a, lld b)
    {
        return b==0 ? a : gcd(b, a%b);
    }
    
    frac operator*(const frac& F) const
    {
        return frac(p*F.p, q*F.q);
    }
    
    frac operator/(const frac& F) const
    {
        return frac(p*F.q, q*F.p);
    }
    
    frac operator+(const frac& F) const
    {
        return frac(p*F.q+q*F.p, q*F.q);
    }
    
    frac operator-(const frac& F) const
    {
        return frac(p*F.q-q*F.p, q*F.q);
    }
    
    bool operator==(const frac& F) const
    {
        return p==F.p && q==F.q ;
    }
    
    bool operator!=(const frac& F) const
    {
        return p!=F.p || q!=F.q ;
    }
    
    void read()
    {
        char s[128]={0};
        scanf("%s", s);
        q=1;
        
        if( strchr(s, '/') )
            sscanf(s, "%lld/%lld", &p, &q);
        else
            sscanf(s, "%lld", &p);
        
        formalize();
    }
    
    void show() const
    {
        if( q==1 )
            printf("%lld", p);
        else
            printf("%lld/%lld", p, q);
    }
};

int sol(vector<vector<frac>>& a, int n, int m)
{
    int ans=0;
    
    for(int i=0; ans<min(n, m) && i<m; i++)
    {
        for(int j=ans; j<n; j++)
            if( a[j][i]!=0 )
                swap(a[ans], a[j]);
        
        if( a[ans][i]==0 )
            continue;
        
        for(int j=m; j>=i; j--)
        {
            a[ans][j]=a[ans][j]/a[ans][i];
            
            for(int k=0; k<n; k++)
                if( k!=ans )
                    a[k][j]=a[k][j]-a[ans][j]*a[k][i];
        }
        
        ans++;
    }
    
    for(int i=0; i<n; i++)
    {
        int cnt=0;
        
        for(int j=0; j<m; j++)
            cnt+=a[i][j]!=0;
        
        if( cnt==0 && a[i][m]!=0 )
            return -1;
    }
    
    return ans;
}

int main()
{
    for(int init=1, id; scanf("%d", &id) && id>0; init=0)
    {
        int n, m;
        scanf("%d%d", &m, &n);
        vector<vector<frac>> a(n, vector<frac>(m+1));
        
        for(int i=0; i<n; i++)
            for(int j=0; j<=m; j++)
                a[i][j].read();
        
        int ans=sol(a, n, m);
        printf("%sSolution for Matrix System # %d\n", init ? "" : "\n", id);
        
        if( ans<0 )
            printf("No Solution.\n");
        else if( ans<m )
            printf("Infinitely many solutions containing %d arbitrary constants.\n", m-ans);
        else
        {
            for(int i=0; i<m; i++)
            {
                printf("x[%d] = ", i+1);
                a[i][m].show();
                printf("\n");
            }
        }
    }
}

/*
 
 1
 3 3
 9 4 1 -17
 1 -2 -6 14
 1 6 0 4
 
 2
 3 3
 2 2 2 2
 4 4 4 4
 16/1 16/1 16/1 16/1
 
 3
 2 3
 1 1 10
 1 1 20
 2 2 50
 
 4
 1 1
 3 10
 
 0
 
 */
