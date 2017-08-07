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
    const char* p="IVXLCDM";
    const char* q="1222234";
    
    for(int x; scanf("%d", &x)!=EOF; )
    {
        int ans=0;
        
        for(char c : rome(x))
            for(int i=0; i<7; i++)
                if( c==p[i] )
                    ans+=q[i]-'0';
        
        printf("%d\n", ans);
    }
}
