#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> read(int n)
{
    vector<int> a(10, 0);
    
    for(int i=0; i<n; i++)
    {
        int x;
        scanf("%1d", &x);
        a[x]++;
    }
    
    return a;
}

int one(vector<int> a, vector<int> b)
{
    int ans=0;
    
    for(int i=9; i>=0; i--)
    {
        for(; a[i]>0; a[i]--)
        {
            bool ok=false;
            
            for(int j=9; j>=i; j--)
                if( b[j]>0 )
                {
                    b[j]--;
                    ok=true;
                    break;
                }
            
            if( !ok )
            {
                ans++;
                
                for(int j=0; j<i; j++)
                    if( b[j]>0 )
                    {
                        b[j]--;
                        break;
                    }
            }
        }
    }
    
    return ans;
}

int two(vector<int> a, vector<int> b)
{
    int ans=0;
    
    for(int i=0; i<=9; i++)
    {
        for(; a[i]>0; a[i]--)
        {
            bool ok=false;
            
            for(int j=i+1; j<=9; j++)
                if( b[j]>0 )
                {
                    b[j]--;
                    ok=true;
                    ans++;
                    break;
                }
            
            if( !ok )
                for(int j=0; j<=i; j++)
                    if( b[j]>0 )
                    {
                        b[j]--;
                        break;
                    }
        }
    }
    
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a=read(n);
    vector<int> b=read(n);
    printf("%d\n%d\n", one(a, b), two(a, b));
}
