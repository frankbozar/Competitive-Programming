#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

string bwt(const string& s)
{
    int n=s.length();
    vector<pair<char, int>> a(n);
    
    for(int i=0; i<n; i++)
    {
        a[i].first=s[i];
        a[i].second=i;
    }
    
    sort(a.begin(), a.end());
    string t="";
    
    for(int p=0, i=0; i<n; i++)
    {
        t+=s[p];
        p=a[p].second;
    }
    
    return t;
}

int Z(const string& s, string t)
{
    int n=t.length(), m=s.length(), ans=0;
    t+='$'+s+s;
    int N=t.length();
    vector<int> z(N, N);
    
    for(int l=0, r=0, i=1; i<n+1+m; i++)
    {
        if( i>r )
        {
            for(l=r=i; r<N && t[r-l]==t[r]; r++);
            z[i]=(r--)-l;
        }
        else
        {
            int k=i-l;
            
            if( z[k]<r-i+1 )
                z[i]=z[k];
            else
            {
                for(l=i; r<N && t[r-l]==t[r]; r++);
                z[i]=(r--)-l;
            }
        }
        
        if( i>n && z[i]>=n )
            ans++;
    }
    
    return ans;
}

int main()
{
    int N;
    
    for(cin >> N; N>0; N--)
    {
        string s;
        cin >> s;
        s=bwt(s);
        int n;
        
        for(cin >> n; n>0; n--)
        {
            string t;
            cin >> t ;
            cout << Z(s, t) << endl ;
        }
    }
}

/*

2

nnbaaa
1
aba

pssmipissii
2
s
mmi

*/