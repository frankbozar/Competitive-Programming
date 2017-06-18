#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

struct ch
{
    lld l;
    char c;
    ch(lld _l=0, char _c='\0') : l(_l), c(_c){}
    
    void read()
    {
        scanf("%lld-%c", &l, &c);
    }
    
    bool operator>=(const ch& C) const
    {
        return c==C.c && l>=C.l ;
    }
    
    bool operator==(const ch& C) const
    {
        return c==C.c && l==C.l ;
    }
};

struct str
{
    vector<ch> s;
    
    str(int n=0)
    {
        for(int i=0; i<n; i++)
        {
            ch c;
            c.read();
            
            if( !s.empty() && s.back().c==c.c )
                s.back().l+=c.l;
            else
                s.push_back(c);
        }
    }
    
    str operator+(const str& T) const
    {
        str S;
        S.s.assign(s.begin()+1, s.end()-1);
        S.s.push_back(ch(1, '$'));
        S.s.insert(S.s.end(), T.s.begin(), T.s.end());
        return S;
    }
    
    int length() const
    {
        return s.size();
    }
    
    void print() const
    {
        for(int i=0; i<length(); i++)
            for(int j=0; j<s[i].l; j++)
                putchar(s[i].c);
        
        putchar('\n');
    }
    
    const ch& operator[](int i) const
    {
        return s[i];
    }
    
    lld operator()(const str& T) const
    {
        return T.length()==1 ? m1(T) : m3(T);
    }
    
    lld m1(const str& T) const
    {
        const str& S=*this;
        lld ans=0;
        
        for(int i=0; i<S.length(); i++)
            if( S[i]>=T[0] )
                ans+=S[i].l-T[0].l+1;
        
        return ans;
    }
    
    lld m3(const str& T) const
    {
        const str S=T+*this;
        vector<int> z=Z(S);
        int n=S.length(), m=T.length();
        lld ans=0;
        
        for(int i=1; i+m-2<n; i++)
            if( z[i]>=m-2 && S[i-1]>=T[0] && S[i+m-2]>=T[m-1] )
                ans++;
        
        return ans;
    }
    
    static vector<int> Z(const str& S)
    {
        int n=S.length();
        vector<int> z(n, n);
        
        for(int l=0, r=0, i=1; i<n; i++)
            if( r<i || r-i<z[i-l] ){
                if( r<i ) r=i;
                for(l=i; r<n && S[r]==S[r-l]; r++);
                z[i]=r---l;
            }else z[i]=z[i-l];
        
        return z;
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    str s(n), t(m);
    printf("%lld\n", s(t));
}
