#include<cstdio>
#include<string>
using namespace std;
const int num[13]={1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
const string str[13]={"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
string rome(int x){
    for(int i=0; i<13; i++) if( x>=num[i] ) return str[i]+rome(x-num[i]);
    return "";
}
int rome(const string& s){
    for(int i=0; i<13; i++)
        if( s.length()>=str[i].length() && s.substr(0, str[i].length())==str[i] )
            return num[i]+rome(s.substr(str[i].length()));
    return 0;
}


int main()
{
    const char* p="IVXLC";
    const int N=128;
    int a[N][5]={{0}};
    
    for(int i=1; i<N; i++)
    {
        for(int j=0; j<5; j++)
            a[i][j]=a[i-1][j];
        
        for(char c : rome(i))
            for(int j=0; j<5; j++)
                if( c==p[j] )
                    a[i][j]++;
    }
    
    for(int x; scanf("%d", &x) && x>0; )
        printf("%d: %d i, %d v, %d x, %d l, %d c\n", x, a[x][0], a[x][1], a[x][2], a[x][3], a[x][4]);;
}
