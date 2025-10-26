// LeetCode 46. Permutation
// LeetCode 77. Combination

#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> perms;
        int n = nums.size();
        if (n == 1) {
            perms.push_back(vector<int>{nums[0]});
            return perms;
        }

        for (int i = 0; i < n; i++) {
            // store nums without nums[i]
            vector<int> remain;
            for (int j = 0; j < n; j++) {
                if(j != i)
                    remain.push_back(nums[j]);
            }
            // recursion
            auto remain_perms = permute(remain);
            for (auto& remain_perm : remain_perms) {
                remain_perm.push_back(nums[i]);
                perms.push_back(remain_perm);
            }
        }

        return perms;
    }

    // Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        if(k == 1) {
            for(int i = 1; i <= n; i++)
                res.push_back(vector<int>{i});
            return res;
        }

        if(k == n) {
            vector<int> comb;
            for(int i = 1; i <= n; i++) {
                comb.push_back(i);
            }
            res.push_back(comb);
            return res;
        }

        // k-combination with n
        auto remain_combs = combine(n-1, k-1);
        for(auto& remain_comb : remain_combs) {
            remain_comb.push_back(n);
            res.push_back(remain_comb);
        }

        // k-combination without n
        remain_combs = combine(n-1, k);
        for(auto& remain_comb : remain_combs) {
            res.push_back(remain_comb);
        }

        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums{1,2,3};
    auto perms = s.permute(nums);
    for(auto& perm : perms) {
        for(auto& num : perm) {
            cout << num << ", ";
        }
        cout << '\b' << endl;
    }
    return 0;
}