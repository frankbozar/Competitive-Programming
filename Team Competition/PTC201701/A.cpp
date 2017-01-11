#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1600, N=1600;
typedef bitset<N> set;

struct equation
{
    set S;
    equation() : S(0){}
    
    bool read()
    {
        S.reset();
        char s[1024]={0};
        scanf(" %[^\n]", s);
        const char *p=strtok(s, " ");
        
        if( atoi(p)==-1 )
            return false;
        
        while( (p=strtok(NULL, " ")) )
            S[atoi(p)]=true;
        
        return true;
    }
    
    int left() const
    {
        for(int i=0; i<N; i++)
            if( S[i] )
                return i;
        
        return INF;
    }
    
    void print(int n) const
    {
        for(int i=0; i<n; i++)
            printf(S[i] ? "1" : "0");
        
        printf("\n");
    }
};

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        scanf("%*d");
        vector<equation> E;
        for(equation e; e.read(); E.push_back(e));
        int n=E.size();
        
        for(int i=0; i<n; i++)
        {
            int pos=-1, bit=INF;
            
            for(int j=i; j<n; j++)
            {
                int tmp=E[j].left();
                
                if( bit>tmp )
                {
                    bit=tmp;
                    pos=j;
                }
            }
            
            if( pos<0 )
                break;
            
            swap(E[i], E[pos]);
            
            for(int j=0; j<n; j++)
                if( i!=j && E[j].S[bit] )
                    E[j].S^=E[i].S;
        }
        
        int ans=0;
        
        for(int i=0; i<n; i++)
            if( E[i].S.count()==1 )
                ans++;
        
        printf("%d\n", ans);
    }
}

/*

3

3
120 0 1
121 1 2
122 2 0
-1

3
120 0
121 1
123 0 1 2
-1

6
120 0
121 1
123 0 1 2
3 3 4
73 0 3
1 4 5
-1

*/
