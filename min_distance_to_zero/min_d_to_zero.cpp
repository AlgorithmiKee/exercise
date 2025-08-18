#include <vector>
#include<iostream>

using namespace std;

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}

////////////////////////////////////////////////////////////

class Solution {
    const int INF = 1e9;
    
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int nrow = mat.size();
        int ncol = mat[0].size();
        vector<vector<int>> d(nrow, vector(ncol, -1));
        
        for (int i = 0; i < nrow; i++) {
            for(int j = 0; j < ncol; j++) {
                compute_d(i, j, mat, d);
            }
        }
        return d;
    }
    
    void compute_d(int i, int j, vector<vector<int>>& mat, vector<vector<int>>& d) {
        int nrow = mat.size();
        int ncol = mat[0].size();
        if(d[i][j] != -1) {
            return;
        }
        
        if(mat[i][j] == 0) {
            d[i][j] = 0;
            return;
        }
        else {
            // min d s.t. d in neighbour(d[i][j])
            int delta_d = INF;
            if(i-1 >= 0) {
                compute_d(i-1, j, mat, d);
                delta_d = min(delta_d, d[i-1][j]);
            }
            if(i+1 < nrow) {
                compute_d(i+1, j, mat, d);
                delta_d = min(delta_d, d[i+1][j]);
            }
            if(j-1 >= 0) {
                compute_d(i, j-1, mat, d);
                delta_d = min(delta_d, d[i][j-1]);
            }
            if(j+1 < ncol) {
                compute_d(i, j+1, mat, d);
                delta_d = min(delta_d, d[i][j+1]);
            }
            d[i][j] = 1 + delta_d;
        }
    }
    
    int min(int a, int b) {
        if(b == -1) {
            return a;
        }
        
        if(a == -1) {
            return b;
        }
        return (a < b)? a:b;
    }
    
    
};

////////////////////////////////////////////////////////////

int main() {
    Solution s;
    vector<vector<int>> mat = {
        {0, 0 ,0},
        {0, 1, 0},
        {1, 1, 1}
    };
    
    auto d = s.updateMatrix(mat);
    
    cout << "mat:" << endl;
    printMatrix(mat);
    cout << "d:" << endl;
    printMatrix(d);
    
}