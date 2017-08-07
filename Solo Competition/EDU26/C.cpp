#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

bool o(int a, int b, int c)
{
    return a>=b+c;
}

bool k(int a, int b, int c)
{
    return a>=b && a>=c;
}

bool ok(int a, int b, int w1, int h1, int w2, int h2)
{
    if( o(a, w1, w2) && k(b, h1, h2) )
        return true;
    else if( o(a, w1, h2) && k(b, h1, w2) )
        return true;
    else if( o(a, h1, w2) && k(b, w1, h2) )
        return true;
    else if( o(a, h1, h2) && k(b, w1, w2) )
        return true;
    
    swap(a, b);
    
    if( o(a, w1, w2) && k(b, h1, h2) )
        return true;
    else if( o(a, w1, h2) && k(b, h1, w2) )
        return true;
    else if( o(a, h1, w2) && k(b, w1, h2) )
        return true;
    else if( o(a, h1, h2) && k(b, w1, w2) )
        return true;
    
    return false;
}

int main()
{
    int n, a, b, ans=0;
    scanf("%d%d%d", &n, &a, &b);
    vector<int> w(n), h(n);
    
    for(int i=0; i<n; i++)
    {
        scanf("%d%d", &w[i], &h[i]);
        
        for(int j=0; j<i; j++)
            if( ok(a, b, w[i], h[i], w[j], h[j]) )
                ans=max(ans, w[i]*h[i]+w[j]*h[j]);
    }
    
    printf("%d\n", ans);
}
