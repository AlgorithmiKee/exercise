// LeetCode 162. Find Peak Element

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) {
            return 0;
        }

        if(nums[0] > nums[1]) {
            return 0;
        }

        if(nums[n-1] > nums[n-2]) {
            return n-1;
        }

        int l = 0;
        int r = n-1;

        while(l < r) {
            int mid = (l+r)/2;
            int boundary_h = (nums[l] > nums[r]) ? l : r;

            if(nums[mid] < nums[boundary_h]) {
                l = min(mid, boundary_h);
                r = max(mid, boundary_h);
            }
            else {
                if(peak_at(mid, nums)) {
                    return mid;
                }
                else if(nums[mid+1] > nums[mid]) {
                    l = mid;
                }
                else {
                    r = mid;
                }
            }
        }
        // should not reach here
        return -1;
    }
    
    bool peak_at(int i, vector<int> a) {
        if(i == 0) {
            return (a[0] > a[1]) ? true : false;
        }

        int n = a.size();
        if(i == n-1) {
            return (a[n-1] > a[n-2]) ? true : false;
        }

        if(a[i] > a[i-1] && a[i] > a[i+1]) {
            return true;
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> v = {1,2,1,3,5,6,4};
    cout << s.findPeakElement(v);

    return 0;
}