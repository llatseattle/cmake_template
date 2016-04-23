#include "combination_sum.h"

vector<vector<int> > CombinationSum::combinationSum(vector<int>& candidates, int target) {
        vector<vector<int> > result;
        if (candidates.empty() || target < 1) {
            return result;
        }
        std::sort(candidates.begin(), candidates.end());
        std::vector<int> one_result;
        helper1(candidates, 0, target, one_result, result);

        return result;
}

vector<vector<int>> CombinationSum::combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int> > result;
        if (candidates.empty() || target < 1) {
            return result;
        }
        std::sort(candidates.begin(), candidates.end());
        vector<int> one;
        helper2(candidates, 0, target, one, result);

        return result;
}

vector<vector<int>> CombinationSum::combinationSum3(int k, int n) {
        vector<vector<int> > result;
        if (k < 1 || k > 9 || n < 1) {
            return result;
        }
        int upper = 10 - k;
        vector<int> one;
        sum3Helper(k, 1, 0, n, one, result);

        return result;
}
