#include<cstdio>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define F first
#define S second
char s[1<<20];

string rev(const string& s)
{
    return string(s.rbegin(), s.rend());
}

bool pal(const string& s)
{
    return s==rev(s);
}

int main()
{
    int n, mid=0, ans=0;
    scanf("%d%*d", &n);
    map<string, pair<vector<int>, vector<int>>> M;
    
    for(int i=0; i<n; i++)
    {
        int v;
        scanf("%s%d", s, &v);
        
        if( M.find(s)!=M.end() )
            M[s].F.push_back(v);
        else if( M.find(rev(s))!=M.end() )
            M[rev(s)].S.push_back(v);
        else
            M[s].F.push_back(v);
    }
    
    for(auto& it : M)
    {
        auto& a=it.S.F;
        auto& b=it.S.S;
        sort(a.rbegin(), a.rend());
        sort(b.rbegin(), b.rend());
        
        if( pal(it.F) )
        {
            int tmp=0;
            
            for(int n=a.size(), i=0; i<n && a[i]>0; i+=2)
            {
                if( i+1>=n || a[i]+a[i+1]<0 )
                    tmp=a[i];
                else
                {
                    tmp=-a[i+1];
                    ans+=a[i]+a[i+1];
                }
            }
            
            mid=max(mid, tmp);
        }
        else
        {
            for(int i=min(a.size(), b.size())-1; i>=0; i--)
                ans+=max(a[i]+b[i], 0);
        }
    }
    
    printf("%d\n", ans+mid);
}
