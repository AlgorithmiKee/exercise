// LeetCode 135

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    // return true if candies[i] got updated, false otherwise
    bool updateAt(int i, const vector<int>& ratings, vector<int>& candies) {
        int n = ratings.size();
        int l = (i > 0) ? i-1 : i;
        int r = (i < n-1) ? i+1 : i;

        if(ratings[i] > max(ratings[l], ratings[r])) {
            if(candies[i] > max(candies[l], candies[r])) {
                return false;
            }
            else {
                candies[i] = max(candies[l], candies[r]) + 1;
                return true;
            }
        }

        if(ratings[i] > ratings[l]) {
            if(candies[i] > candies[l]) {
                return false;
            }
            else {
                candies[i] = candies[l] + 1;
                return true;
            }
        }

        if(ratings[i] > ratings[r]) {
            if(candies[i] > candies[r]) {
                return false;
            }
            else {
                candies[i] = candies[r] + 1;
                return true;
            }
        }
        return false;
    } 

    // suboptimal BFS based
    int candyBFS(vector<int>& ratings) {
        int n = ratings.size();
        if(n == 1) {
            return 1;
        }

        vector<int> candies(n, 1);
        queue<int> q;

        for(int i = 0; i < n; i++) {
            q.push(i);
        }

        while(!q.empty()) {
            int i = q.front();
            q.pop();
            auto updated = updateAt(i, ratings, candies);
            if(updated) {
                if(i-1 >=0 ) {
                    q.push(i-1);
                }
                if(i+1 < n) {
                    q.push(i+1);
                }
            }
        }

        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};

int main() {
    Solution s;
    vector<int> ratings = {1,0,2};
    auto minCandy = s.candyBFS(ratings);
    cout << "min candies: " << minCandy << endl;
    return 0;
}