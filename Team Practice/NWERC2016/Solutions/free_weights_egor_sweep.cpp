//this solution considers one element after another on the rack
//     A. consider the first two weights next to each other:
//              1. they are equal -> just delete them, nothing to do
//              2. they are different, so I know I have to lift the lighter one, rember the weight of the lighter one and delete it
//     go to A
//
//  Running time: O(n)


#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

int sweep_rack(const vi &rack){
    int res=0;
    int cand=0;
    for(const int &e:rack){ 
        if(e==cand)//found second!
            cand=0;
        else if(e<cand)//I have to be strong enough to lift e (but who knows, maybe also cand)
            res=max(res, e);
        else{// if(e>cand), There is no way out, I have to lift the candidate, but it is not yet clear with e-> make it candidate
            res=max(res, cand);
            cand=e;
        }
    }
    return max(res, cand);
}

vi read_rack(int n){
  vi res(n);
  for (auto &e:res)
    cin >> e;
  return res;
}

int main(){
    
    int n;
    cin >> n;
    
    cout << std::max(sweep_rack(read_rack(n)), sweep_rack(read_rack(n))) <<"\n";
}

