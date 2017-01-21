#include<cstdio>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
typedef bitset<1<<20> set;

int maxi(const vector<int>& a, int m)
{
    int ans=0, odd=0;
    
    for(int x : a)
    {
        int tmp=min(x>>1, m);
        odd+=x&1;
        ans+=tmp<<1;
        m-=tmp;
    }
    
    return ans+min(odd, m);
}

int mini(const vector<int>& a, int m)
{
    const int N=100;
    vector<int> c(N, 0);
    set ans;
    ans[0]=true;
    
    for(int x : a)
    {
        if( x<N )
            c[x]++;
        else
            ans|=ans<<x;
    }
    
    for(int i=1; i<N; i++)
    {
        if( c[i]==0 )
            continue;
        
        set tmp=ans;
        
        for(int j=m; j>m-i; j--)
        {
            int cnt=0;
            
            for(int k=1; k<=c[i]; k++)
                if( j-i*k>=0 && tmp[j-i*k] )
                    cnt++;
            
            for(int k=j; k>=0; k-=i)
            {
                if( cnt>0 )
                    ans[k]=true;
                
                if( k-i>=0 && tmp[k-i] )
                    cnt--;
                
                if( k-i*(c[i]+1)>=0 && tmp[k-i*(c[i]+1)] )
                    cnt++;
            }
        }
    }
    
    return ans[m] ? m : m+1 ;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> p(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &p[i]);
    
    vector<int> a;
    
    for(int i=1; i<=n; i++)
    {
        int cnt=0;
        
        for(int x=i; p[x]>0; cnt++)
        {
            int tmp=p[x];
            p[x]=0;
            x=tmp;
        }
        
        if( cnt>0 )
            a.push_back(cnt);
    }
    
    printf("%d %d\n", mini(a, m), maxi(a, m));
}
