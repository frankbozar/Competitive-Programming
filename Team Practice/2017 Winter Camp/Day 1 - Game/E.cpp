#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=6000;
char s[N]={0};

int g(int n)
{
    if( n<=2 )
        return n<=0 ? 0 : 1 ;
    
    if( n<=0 )
        return 0;
    
    static vector<int> G(N, -1);
    int& ans=G[n];
    
    if( ans<0 )
    {
        vector<bool> u(N);
        
        for(int i=0; i<n; i++)
            u[ g(i-1)^g(n-i-2) ]=true;
        
        for(int i=n-1; i>=0; i--)
            if( !u[i] )
                ans=i;
    }
    
    return ans;
}

int main()
{
    scanf("%s", s);
    vector<pair<int, int>> a;
    int n=strlen(s), ans=0;
    s[n++]='$';
    
    for(int p=0, i=1; i<n-1; i++)
    {
        if( s[i-1]==s[i+1] )
            continue;
        else if( p<i-1 )
            a.push_back({p+1, i});
        
        ans^=g(i-p-1);
        p=i;
    }
    
    if( ans==0 )
        printf("Second\n");
    
    for(const pair<int, int>& p : a)
        for(int k=p.first; k<p.second; k++)
            if( !(ans^g(p.second-p.first)^g(k-p.first-1)^g(p.second-k-2)) )
            {
                printf("First\n%d\n", k+1);
                return 0;
            }
}
