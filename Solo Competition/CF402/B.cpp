#include<cstdio>
#include<cstring>
#include<bitset>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1024;
typedef bitset<N> bs;

struct var
{
    string name;
    bs u, v;
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<var> a(n);
    
    for(int i=0; i<n; i++)
    {
        char s[N<<1];
        scanf(" %[^\n]", s);
        
        if( strstr(s, "OR") || strstr(s, "XOR") || strstr(s, "AND") )
        {
            char x[16], y[16], o[16], z[16];
            sscanf(s, "%s%*s%s%s%s", x, y, o, z);
            a[i].name=x;
            int p=-1, q=-1;
            
            for(int j=0; j<i; j++)
            {
                if( a[j].name==y )
                    p=j;
                
                if( a[j].name==z )
                    q=j;
            }
            
            if( q<0 )
                swap(p, q);
            
            if( q<0 )
            {
                if( strcmp(o, "XOR")==0 )
                {
                    a[i].u.reset();
                    a[i].v.reset();
                }
                else
                {
                    a[i].u.reset();
                    a[i].v.set();
                }
            }
            else if( p<0 )
            {
                if( strcmp(o, "XOR")==0 )
                {
                    a[i].u=a[q].u;
                    a[i].v=~a[q].v;
                }
                else if( strcmp(o, "OR")==0 )
                {
                    a[i].u=a[q].u;
                    a[i].v.set();
                }
                else// if( strcmp(o, "AND")==0 )
                {
                    a[i].u.reset();
                    a[i].v=a[q].v;
                }
            }
            else
            {
                if( strcmp(o, "XOR")==0 )
                {
                    a[i].u=a[p].u^a[q].u;
                    a[i].v=a[p].v^a[q].v;
                }
                else if( strcmp(o, "OR")==0 )
                {
                    a[i].u=a[p].u|a[q].u;
                    a[i].v=a[p].v|a[q].v;
                }
                else// if( strcmp(o, "AND")==0 )
                {
                    a[i].u=a[p].u&a[q].u;
                    a[i].v=a[p].v&a[q].v;
                }
            }
        }
        else
        {
            a[i].name=strtok(s, " ");
            strtok(NULL, " ");
            const char *t=strtok(NULL, " ");
            a[i].u.reset();
            
            for(int j=0; j<m; j++)
                a[i].u[j]=a[i].v[j]=(t[j]=='1');
        }
    }
    
    for(int j=0; j<m; j++)
    {
        int p=0, q=0;
        
        for(int i=0; i<n; i++)
        {
            if( a[i].u[j] )
                p++;
            
            if( a[i].v[j] )
                q++;
        }
        
        printf(p<=q ? "0" : "1");
    }
    
    printf("\n");
    
    for(int j=0; j<m; j++)
    {
        int p=0, q=0;
        
        for(int i=0; i<n; i++)
        {
            if( a[i].u[j] )
                p++;
            
            if( a[i].v[j] )
                q++;
        }
        
        printf(p>=q ? "0" : "1");
    }

    printf("\n");
}
