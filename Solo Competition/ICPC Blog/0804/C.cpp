#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define data pair<char,int>
#define c first
#define p second

void sol(int n, char s[64], vector<data>& a)
{
    sort(a.begin(), a.end());
    
    for(int i=1; i<n-1; i++)
    {
        sort(a.begin()+i+1, a.end());
        int p=-1;
        
        if( a[i-1].p<a[i].p )
        {
            for(int j=n-1; j>i; j--)
                if( a[i].p>a[j].p )
                    p=j;
        }
        else//if( a[i-1].p>a[i].p )
        {
            for(int j=n-1; j>i; j--)
                if( a[i].p<a[j].p )
                    p=j;
        }
        
        if( p<0 )
            swap(a[i], a[i+1]);
        else
            swap(a[i+1], a[p]);
    }
    
    for(int i=0; i<n; i++)
        s[i]=a[i].c;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        char s[64];
        scanf("%d%s", &n, s);
        vector<data> a;
        
        for(int i=0; i<n; i++)
            a.push_back(data(s[i], i));
        
        sol(n, s, a);
        printf("%s\n", s);
    }
}
