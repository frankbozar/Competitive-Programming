#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

string get(const string& s, const string& t)
{
    return s+" "+t;
}

int main()
{
    int n;
    cin >> n;
    map<string,int> s;
    queue<string> q;
    string w[2], b[2], h, wname, bname;
    vector<string> ans;
    
    for (int i = 0; i < n; i++)
    {
        string name;
        cin >> name;
        
        if (i == 0)
            w[0] = name;
        else if (i == 1)
            b[0] = name;
        else if (i == 2)
        {
            w[1] = name;
            wname=get(w[0], w[1]);
        }
        else if (i == 3)
        {
            b[1] = name;
            bname=get(b[0], b[1]);
        }
        else
            q.push(name);
    }
    
    cin >> h;
    int cur = 0;
    int ansv = 0;
    char last = h[0];
    
    for (int i = 0; i < h.length(); i++)
    {
        if (h[i] == last)
            cur++;
        else
            cur = 1;
        
        if( ansv<cur )
        {
            ansv=cur;
            ans.clear();
        }
        
        if (h[i] == 'W')
        {
            if( cur==ansv )
                ans.push_back(wname);
            
            swap(w[0], w[1]);
            q.push(b[1]);
            b[1] = b[0];
            b[0] = q.front();
            bname=get(b[1], b[0]);
        }
        else
        {
            if( cur==ansv )
                ans.push_back(bname);
            
            swap(b[0], b[1]);
            q.push(w[1]);
            w[1] = w[0];
            w[0] = q.front();
            wname=get(w[1], w[0]);
        }
        
        q.pop();
        last = h[i];
    }
    
    for(const string& s : ans)
        cout << s << endl ;
}

/*

6
Balaji David Alex Scott Andrew Ravi
WWBWBBWBW

6
Amy Jinu Kasey Sarah Sheetal Julia
BBBBB

*/
