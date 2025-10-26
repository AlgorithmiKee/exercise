#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    using ReachabilityMap = vector<vector<bool>>;

    bool canJump(vector<int>& nums) {
        int n = nums.size();
        ReachabilityMap reachable(n, vector<bool>(n, false));
        for(int s = n-1; s >=0; s--) {
            if(nums[s] == 0) {
                continue;
            }

            if(s + nums[s] >= n-1) {
                reachable[s][n-1] = true;
                continue;
            }
            
            for(int i = s+1; i < n && i <= s + nums[s]; i++) {
                reachable[s][n-1] = reachable[s][n-1] || reachable[i][n-1];
            }
        }
        return reachable[0][n-1];
    }

    bool canJumpRecur(vector<int>& nums) {
        int n = nums.size();
        ReachabilityMap reachable(n, vector<bool>(n, false));
        update_reachable(0, nums, reachable);
        return reachable[0][n-1];
        
    }

    // update reachability from idx s to i, for all s < i < end of nums
    void update_reachable(int s, vector<int>& nums, ReachabilityMap& reachable) {
        int end = nums.size()-1;

        if (reachable[s][s] == true) {
            return;
        }

        reachable[s][s] = true;

        if(s == end) {
            return;
        }

        // nums[s] == 0, no need to update s-th row
        if(nums[s] == 0) {
            return;
        }

        // nums[s] != 0, update T/F of immediately reachable cells
        for(int i = 1; i <= nums[s]; i++) {
            if(i < nums.size() ) {
                reachable[s][s+i] = true;
            }
            else {
                return;
            }
        }

        // update T/F of indirectly reachable cells
        for(int i = 1; i <= nums[s] && s+i < nums.size(); i++) {
            update_reachable(s+i, nums, reachable);
            reachable[s][end] = reachable[s][end] || reachable[s+i][end];
        }
    }
};

int main() {
    Solution s;
    // vector<int> a = {3,0,8,2,0,0,1};
    vector<int> a = {0};
    auto reachable = s.canJump(a);
    cout << "reachability from a[0] to a[end]: " << reachable << endl;
}