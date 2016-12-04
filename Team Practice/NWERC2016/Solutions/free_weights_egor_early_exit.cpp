//Looks for weights on the rack starting with the heavest:
//  1. there is a single weight -> we are done, this one is the heavest we have to lift.
//  2. there is a pair of equal weights -> find the maximum weight in between this pair - this is a lower bound for the result.
//repeat with the next weight(-pair).
//
// we are done, if the current lower bound is not smaller as the currently considered weight. 
// With this strategy, every element of the array is touched at most once.
//
// Running time could be O(n) [counting sort], but we use quicksort, which results in O(n*logn)


#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

int brute_force_rack(const vi &rack){
    typedef pair<int, size_t> Weight;
    std::vector<Weight> sorted;
    for(int e:rack)
        sorted.push_back(make_pair(e,sorted.size()));
        
    sort(sorted.begin(), sorted.end(), greater<Weight>());
    
    size_t current=0;
    int max_w=0;
    while(current<sorted.size()){
        if(sorted[current].first<=max_w)  //Important, so we don't touch an element more than ones.
            return max_w;
        if(current==sorted.size()-1 || sorted[current].first!=sorted[current+1].first)
            return std::max(max_w, sorted[current].first);
        for(size_t i=sorted[current+1].second+1;i<=sorted[current].second-1;i++)
          max_w=std::max(max_w, std::min(rack[i], sorted[current].first));
        current+=2;
    }
    
    return max_w;
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
    
    cout << std::max(brute_force_rack(read_rack(n)), brute_force_rack(read_rack(n))) <<"\n";
}

