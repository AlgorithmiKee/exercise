#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string result("");

        for(int j = 0; ; j++) {
            if(j >= strs[0].size()) {
                break;
            }
            char c = strs[0][j];
            for(int i = 1; i < strs.size(); i++) {
                if(j >= strs[i].size() || strs[i][j] != c) {
                    c = 'F';
                    break;
                }
            }
            if(c != 'F') {
                result = result + c;
            }
            else{
                // common prefix ended here. No need to check next character
                break;
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> strs = {"dog","racecar","car"};
    cout << "largest common prefix: " << s.longestCommonPrefix(strs);

    return 0;
}