#include<cstdio>
//#include<set>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
typedef bitset<1<<20> set;

int maxi(vector<int> a[2], int m)
{
    int ans=0;
    
    for(int x : a[0])
    {
        int t=min(x>>1, m);
        ans+=t<<1;
        m-=t;
    }
    
    for(int x : a[1])
    {
        int t=min(x>>1, m);
        ans+=t<<1;
        m-=t;
    }
    
    ans+=min(m, (int)a[1].size());
    return ans;
}

int mini(vector<int> a[2], int m)
{
    set S;
    S[0]=true;
    
    for(int x : a[0])
        S|=S<<x;
    
    for(int x : a[1])
        S|=S<<x;
    
    return S[m] ? m : m+1 ;
    
    /*
    multiset<int> S;
    
    for(int x : a[0])
        S.insert(x);
    
    for(int x : a[1])
        S.insert(x);
    
    int t=m;
    
    for(; ; )
    {
        auto it=S.upper_bound(m);
        
        if( it==S.begin() )
            break;
        
        --it;
        m-=*it;
        S.erase(it);
    }
    
    return m==0 ? t : t+1 ;
     */
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> p(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &p[i]);
    
    vector<int> a[2];
    
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
            a[cnt&1].push_back(cnt);
    }
    
    printf("%d %d\n", mini(a, m), maxi(a, m));
}
