#ifndef _COMBINATION_SUM_H_
#define _COMBINATION_SUM_H_

#include "static_include.h"

using namespace std;

class CombinationSum {
public:
	CombinationSum() {}
	~CombinationSum() {}
    vector<vector<int> > combinationSum(vector<int>& candidates, int target);
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target);

    
    vector<vector<int>> combinationSum3(int k, int n);
    
private:
    void helper1(vector<int>& cand, size_t index, int target,
                vector<int> one, vector<vector<int> >& result) {
        if (target < 0 || index >= cand.size()) {
            return;
        } else if (0 == target) {
            result.push_back(one);
            return;
        } else
        for (size_t i = index; i < cand.size(); ++i) {
            one.push_back(cand[i]);
            helper1(cand, i, target - cand[i], one, result);
            one.pop_back();
        }
        
        return;
    }
    
    void helper2(vector<int>& cands, size_t index, int target,
                vector<int> one, vector<vector<int> >& result) {
        if (0 == target) {
            result.push_back(one);
            return;
        } else if (target < 0 || index >= cands.size()) {
            return;
        } else
            for (size_t i = index; i < cands.size(); ++i) {
                if (i > index && cands[i] == cands[i-1]) {
                    continue;
                }
                one.push_back(cands[i]);
                helper2(cands, i + 1, target - cands[i], one, result);
                one.pop_back();
            }
        
        return;
    }
    
    void sum3Helper(int k, int start, int count, int n,
                    vector<int> one, vector<vector<int> > &result) {
        if (0 == n && count == k) {
            result.push_back(one);
            return;
        } else if (n < 0 || count >= k) {
            return;
        }
        for (int i = start; i <= 9; ++i) {
            one.push_back(i);
            sum3Helper(k, i + 1, count + 1, n - i, one, result);
            one.pop_back();
        }
        return;
    }
};

// LeetCode 77
class Comb {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if (k > n || n < 1 || k < 1) {
            return result;
        } else if (k == n) {
            result.resize(1);
            result[0].resize(n);
            for (int i = 0; i < n; ++i) {
                result[0][i] = i + 1;
            }
            return result;
        } else if (1 == k) {
            result.resize(n);
            for (int i = 0; i < n; ++i) {
                result[i].push_back(i+1);
            }
            return result;
        }
        
        result = combine(n - 1, k);
        auto r2 = combine(n - 1, k - 1);
        for (auto& one : r2) {
            one.push_back(n);
        }
        result.insert(result.end(), r2.begin(), r2.end());
        
        return result;
    }
};

#endif
