#include<cstdio>
#include<stack>
using namespace std;
const int INF=1<<20;

int read()
{
    int x;
    scanf("%d", &x);
    return x;
}

int main()
{
    stack<int> S, T;
    S.push(INF);
    T.push(1);
    int ans=0;
    
    for(int v=0, n=read(); n>0; n--)
    {
        switch( read() )
        {
            case 1:
                v=read();
                break;
                
            case 2:
                for(; T.top()==0; T.pop())
                    ans++;
                break;
                
            case 3:
                S.push(read());
                break;
                
            case 4:
                T.push(1);
                break;
                
            case 5:
                S.push(INF);
                break;
                
            case 6:
                T.push(0);
                break;
                
            default:
                ;
        }
        
        for(; v>S.top(); S.pop())
            ans++;
    }
    
    printf("%d\n",
           ans);
}
