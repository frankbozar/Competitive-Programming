#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, string> data;
const string QQ="IMPOSSIBLE";

string solve(int r, int y, int b)
{
    int n=r+y+b;
    
    if( r<<1>n || y<<1>n || b<<1>n )
        return QQ;
    
    vector<data> a(3);
    a[0]=data(r, "R");
    a[1]=data(y, "Y");
    a[2]=data(b, "B");
    sort(a.rbegin(), a.rend());
    r=a[0].first;
    y=a[1].first;
    b=a[2].first;
    string R=a[0].second;
    string Y=a[1].second;
    string B=a[2].second;
    string ans;
    
    for(int i=0; i<b-r+y; i++)
        ans+=R+Y+B;
    
    for(int i=0; i<r-b; i++)
        ans+=R+Y;
    
    for(int i=0; i<r-y; i++)
        ans+=R+B;
    
    return ans;
}

string solve(int n, int r, int o, int y, int g, int b, int v)
{
    string ans="";
    
    if( n==o+b && o==b )
    {
        for(int i=0; i<b; i++)
            ans+="BO";
    }
    else if( n==g+r && g==r )
    {
        for(int i=0; i<r; i++)
            ans+="RG";
    }
    else if( n==v+y && v==y )
    {
        for(int i=0; i<y; i++)
            ans+="YV";
    }
    
    if( ans!="" )
        return ans;
    
    for(int i=0; i<=o; i++)
    {
        if( i==0 && o!=0 )
            continue;
        else if( b<i+o )
            break;
        
        for(int j=0; j<=g; j++)
        {
            if( j==0 && g!=0 )
                continue;
            else if( r<j+g )
                break;
            
            for(int k=0; k<=v; k++)
            {
                if( k==0 && v!=0 )
                    continue;
                else if( y<k+v )
                    break;
                
                string tmp=solve(r-g, y-v, b-o);
                
                if( tmp==QQ )
                    continue;
                
                int I=i, J=j, K=k;
                
                for(char C : tmp)
                {
                    if( C=='B' )
                    {
                        int l=I>1 ? 1 : I<1 ? 0 : o-i+1 ;
                        
                        for(I--; l>0; l--)
                            ans+="BO";
                        
                        ans+="B";
                    }
                    else if( C=='R' )
                    {
                        int l=J>1 ? 1 : J<1 ? 0 : g-j+1 ;
                        
                        for(J--; l>0; l--)
                            ans+="RG";
                        
                        ans+="R";
                    }
                    else//if( C=='Y' )
                    {
                        int l=K>1 ? 1 : K<1 ? 0 : v-k+1 ;
                        
                        for(K--; l>0; l--)
                            ans+="YV";
                        
                        ans+="Y";
                    }
                }
                
                return ans;
            }
        }
    }
    
    return QQ;
}

int map(char c)
{
    switch( c )
    {
        case 'R': return 1;
        case 'O': return 3;
        case 'Y': return 2;
        case 'G': return 6;
        case 'B': return 4;
        case 'V': return 5;
        default : return 7;
    }
}

int main(int argc, const char* argv[])
{
    FILE* inp=fopen(argv[1], "r");
    FILE* oup=fopen(argv[2], "r");
    
    int ncase;
    fscanf(inp, "%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int a[6], s;
        fscanf(inp, "%d", &s);
        
        for(int i=0; i<6; i++)
            fscanf(inp, "%d", &a[i]);
        
        string ans=solve(s, a[0], a[1], a[2], a[3], a[4], a[5]);
        
        if( ans==QQ )
            continue;
        
        printf("%d\n", cases);
        string ANS="ROYGBV";
        
        for(int i=0; i<6; i++)
            if( count(ans.begin(), ans.end(), ANS[i])!=a[i] )
            {
                printf("!!!!!\n");
                getchar();
            }
        
        for(int i=0; i<s; i++)
            if( (map(ans[i])&map(ans[(i+1)%s]))!=0 )
            {
                printf("%c %c", ans[i], ans[(i+1)%s]);
                printf("~~~~~\n");
                getchar();
            }
    }
}
