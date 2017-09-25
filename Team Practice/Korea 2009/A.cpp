#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;

bool sol(vector<int> a, int n)
{
    for(int k=0; k<1<<10; k++)
    {
        a.push_back(a.front());
        vector<int> b(n);
        bool zer=true;
        
        for(int i=0; i<n; i++)
        {
            b[i]=abs(a[i+1]-a[i]);
            
            if( b[i] )
                zer=false;
        }
        
        if( zer )
            return true;
        else
            a=b;
    }
    
    return false;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        printf(sol(a, n) ? "ZERO\n" : "LOOP\n");
    }
}

/*

4

4
8 11 2 7

5
4 2 0 2 0

7
0 0 0 0 0 0 0

6
1 2 3 1 2 3

*/
