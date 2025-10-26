#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        // need at least two columns to trap any water
        int n = height.size();
        if(n < 3) {
            return 0;
        }

        int max_h = *max_element(height.begin(), height.end());
        // can't trap any water if no columns is taller than 0
        if(max_h == 0) {
            return 0;
        }

        int trap = 0;
        vector<int> left_max(n, -1);
        vector<int> right_max(n, -1);

        compute_left_max(height, left_max, n-1);
        compute_right_max(height, right_max, 0);

        for(int i = 1; i < n-1; i++) {
            int water_left = (left_max[i] - height[i] > 0) ? left_max[i] - height[i] : 0;
            int water_right = (right_max[i] - height[i] > 0) ? right_max[i] - height[i] : 0;

            trap += min(water_left, water_right);
        }

        return trap;
    }

    void compute_left_max(vector<int>& height, vector<int>& left_max, int i) {
        if(left_max[i] != -1) {
            return;
        }

        if(i == 0) {
            left_max[i] = height[i];
            return;
        }
        else {
            compute_left_max(height, left_max, i-1);
            left_max[i] = max(left_max[i-1], height[i-1]);
        }
    }

    void compute_right_max(vector<int>& height, vector<int>& right_max, int i) {
        if(right_max[i] != -1) {
            return;
        }

        if(i == height.size()-1) {
            right_max[i] = height[i];
            return;
        }
        else {
            compute_right_max(height, right_max, i+1);
            right_max[i] = max(right_max[i+1], height[i+1]);
        }
    }

};

class SolutionBad {
public:
    int trap(vector<int>& height) {
        // need at least two columns to trap any water
        int n = height.size();
        if(n < 3) {
            return 0;
        }

        int max_h = *max_element(height.begin(), height.end());
        // can't trap any water if no columns is taller than 0
        if(max_h == 0) {
            return 0;
        }

        int trapped = 0;
        for(int h = 1; h <= max_h; h++) {
            int left = 0;
            int right = 0;
            int count = 0;
            while(left < n && right < n) {
                // move the left pointer to the first wall
                while(left < n && height[left] < h) {
                    left++;
                }

                // move the left pointer to the potential water trap
                while(left < n && height[left] >= h) {
                    left++;
                }

                // move the right pointer to the next column
                right = left;
                while(right < n && height[right] < h) {
                    right++;
                }
                if(right < n && height[right] >= h) {
                    trapped = trapped + right - left;
                }
                // advance the left pointer
                left = right;
            }

        }

        return trapped;
    }
};

int main() {
    Solution s;
    vector<int> h = {0,1,0,2,1,0,1,3,2,1,2,1};
    
    cout << "trapped water: " << s.trap(h);

    return 0;
}