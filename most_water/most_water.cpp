#include <iostream>
#include <vector>

using namespace std;
class Solution {
    public:
        int maxArea(vector<int>& height) {
            int n = height.size();
            int l = 0;
            int r = n-1;
            int Amax = (r-l)*min(height[r], height[l]);
            while(l < r) {
                if(height[l] <= height[r]) {
                    int bottelneck = height[l];
                    while(l < r && height[l] <= bottelneck) {
                        l++;
                    }
                }
                else {
                    int bootleneck = height[r];
                    while(l < r && height[r] <= bootleneck) {
                        r--;
                    }
                }
                Amax = max(Amax, (r-l)*min(height[r], height[l]));
            }
            return Amax;
        }
    };

    int main() {
        vector<int> height = {1,8,6,2,5,4,8,3,7};
        Solution s;
        auto result = s.maxArea(height);
        cout << "Maximum area: " << result << endl;

        return 0;
    }