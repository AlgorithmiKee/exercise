// LeetCode 137. Single Number II
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int result = nums[0];
        int i = 3;
        while(i < nums.size()) {
            if(nums[i-1] == result) {
                result = nums[i];
                i += 3;
            }
            else {
                return result;
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    vector<int> v = {0,1,0,1,0,1,99};
    s.singleNumber(v);

    return 0;
}