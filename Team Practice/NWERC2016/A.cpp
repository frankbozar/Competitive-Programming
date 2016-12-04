#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n, m=0;

struct data
{
    vector<int> a;
    data() : a(m, 0){}
    
    void read()
    {
        for(int i=0; i<m; i++)
            scanf("%1d", &a[i]);
    }
    
    void show() const
    {
        for(int i=0; i<m; i++)
            printf("%d", a[i]);
        
        printf("\n");
    }
    
    bool operator<(const data& D) const
    {
        for(int i=0; i<m; i++)
            if( a[i]!=D[i] )
                return a[i]<D[i];
        
        return false;
    }
    
    bool inf() const
    {
        return a[0]>9;
    }
    
    int& operator[](int i)
    {
        return a[i];
    }
    
    int operator[](int i) const
    {
        return a[i];
    }
    
} INF;

data solve(const data& A, const data& B, int k)
{
    data ans=A;
    int p=-1;
    
    for(int i=0; i<m && k>0; p=i++)
    {
        if( ans[i]!=B[i] )
        {
            ans[i]=B[i];
            k--;
        }
    }
    
    if( !(ans<B) )
        return ans;
    
    for(int i=p; i>=0; i--)
    {
        if( ans[i]==9 && ans[i]!=A[i] )
        {
            ans[i]=A[i];
            k++;
        }
        else if( ans[i]!=9 )
        {
            if( ans[i]==A[i] )
                k--;
            
            ans[i]++;
            
            if( ans[i]==A[i] )
                k++;
            
            for(int j=i+1; j<m && k>0; j++)
            {
                if( ans[j]!=0 )
                {
                    ans[j]=0;
                    k--;
                }
            }
            
            return ans;
        }
    }
    
    return INF;
}

int main()
{
    scanf("%d%d", &n, &m);
    INF.a.assign(m, 10);
    int k=(n<<1)|1;
    vector<data> a(n+1);
    vector<vector<data>> dp(n+1, vector<data>(k));
    vector<vector<int>> pre(n+1, vector<int>(k, -1));

    for(int i=1; i<=n; i++)
    {
        a[i].read();
        
        for(int j=0; j<k; j++)
        {
            dp[i][j]=INF;
            
            for(int l=0; l<=j; l++)
            {
                data tmp=solve(a[i], dp[i-1][l], j-l);
                
                if( tmp<dp[i][j] )
                {
                    dp[i][j]=tmp;
                    pre[i][j]=l;
                }
            }
        }
    }
    
    vector<int> S;
    
    for(int i=0; i<k; i++)
    {
        if( !dp[n][i].inf() )
        {
            for(int j=i; n>0; j=pre[n--][j])
                S.push_back(j);
            
            break;
        }
    }
    
    for(int i=1; !S.empty(); S.pop_back())
        dp[i++][S.back()].show();
}

/*

5 3
111
001
000
111
000

*/