#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;


class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        if(!checkRows(board)) {
            return false;
        }

        if(!checkCols(board)) {
            return false;
        }

        if(!check3x3s(board)) {
            return false;
        }

        return true;
    }

    bool checkRows(vector<vector<char>>& board) {
        for(int i = 0; i < board.size(); i++) {
            unordered_set<char> uniqueNums;
            for(int j = 0; j < board[i].size(); j++) {
                if(board[i][j] == '.') {
                    continue;
                }
                if(uniqueNums.find(board[i][j]) != uniqueNums.end()) {
                    return false;
                }
                else {
                    uniqueNums.insert(board[i][j]);
                }
            }
        }
        return true;
    }

    bool checkCols(vector<vector<char>>& board) {
        for(int j = 0; j < board[0].size(); j++) {
            unordered_set<char> uniqueNums;
            for(int i = 0; i < board.size(); i++) {
                if(board[i][j] == '.') {
                    continue;
                }
                if(uniqueNums.find(board[i][j]) != uniqueNums.end()) {
                    return false;
                }
                else {
                    uniqueNums.insert(board[i][j]);
                }
            }
        }
        return true;
    }

    bool check3x3s(vector<vector<char>>& board) {
        vector<int> idx_i = {0, 3, 6};
        vector<int> idx_j = {0, 3, 6};
        for(auto i : idx_i) {
            for(auto j : idx_j) {
                bool valid3x3 = check3x3(board, i, j);
                if(!valid3x3) {
                    return false;
                }
            }
        }
        return true;
    }

    bool check3x3(vector<vector<char>>& board, int x, int y) {
        unordered_set<char> uniqueNums;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[x+i][y+j] == '.')
                    continue;
                if(uniqueNums.find(board[x+i][y+j]) != uniqueNums.end()) {
                        return false;
                }
                else {
                    uniqueNums.insert(board[i][j]);
                }
            }
        }
        return true;
    }
};

int main() {
    // Define the Sudoku board as a vector of vectors of characters
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    // Create an instance of Solution class
    Solution solution;

    // Check if the given board is a valid Sudoku
    bool isValid = solution.isValidSudoku(board);

    // Print the result
    cout << (isValid ? "true" : "false") << endl;

    return 0;
}