#include<cstdio>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
const int n=4, N=10000;

struct guess
{
    bool init=true;
    bitset<N> can;
    
    guess()
    {
        can.set();
        
        for(int i=0; i<N; i++)
            if( !valid(i) )
                can[i]=false;
    }
    
    static bool valid(int x)
    {
        bitset<10> u;
        
        for(int i=0; i<n; i++)
        {
            int d=x%10;
            x/=10;
            
            if( u[d] )
                return false;
            else
                u[d]=true;
        }
        
        return true;
    }
    
    int find()
    {
        if( init )
        {
            init=false;
            int x=0;
            
            while( !can[x] )
                x=rand()%N;
            
            return x;
        }
        
        int ans=-1, cnt=N;
        
        for(int i=0; ans<0 || i<10; i++)
        {
            int x=0, tmp=0;
            
            while( !can[x] )
                x=rand()%N;
            
            for(int k=0; k<=n; k++)
                for(int a=0; a<=k; a++)
                    for(int b=0; a+b<=k; b++)
                    {
                        int val=0;
                        
                        for(int j=0; j<N; j++)
                            if( can[j] && check(x, j, a, b) )
                                val++;
                                
                        tmp=max(tmp, val);
                    }
            
            if( cnt>tmp )
            {
                cnt=tmp;
                ans=x;
            }
        }
        
        return ans;
    }
    
    void operator()()
    {
        for(int a=0, b; a!=n; )
        {
            int x=find();
            printf("%.*d\n", n, x);
            fflush(stdout);
            scanf("%d%d", &a, &b);
            
            for(int i=0; i<N; i++)
                if( can[i] && !check(i, x, a, b) )
                    can[i]=false;
        }
    }
    
    static bool check(int x, int y, int a, int b)
    {
        char s[n+1], t[n+1];
        sprintf(s, "%.*d", n, x);
        sprintf(t, "%.*d", n, y);
        int p=0, q=0;
        
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if( s[i]==t[j] )
                    (i==j ? p : q)++;
        
        return a==p && b==q;
    }
};

int main()
{
    guess G;
    G();
}
