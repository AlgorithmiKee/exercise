#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> mat(n, vector<int>(n ,0));
		fill(mat, n, 1);
		return mat;
	}
	
	void fill(vector<vector<int>>& mat, int width, int startVal) {
		int n = mat.size();
		if(width == 0) {
			return;
		}
		if(width == 1) {
			mat[(n-1)/2][(n-1)/2] = startVal;
			return;
		}
		
		// math:  2 always divides n - width
		int i = (n - width)/2;
		int j = i;
		mat[i][j] = startVal;
		for(int k = 1; k < width; k++) {
			j++;
			mat[i][j] = mat[i][j-1] + 1;
		}
		for(int k = 1; k < width; k++) {
			i++;
			mat[i][j] = mat[i-1][j] + 1;
		}
		for(int k = 1; k < width; k++) {
			j--;
			mat[i][j] = mat[i][j+1] + 1;
		}
		for(int k = 1; k < width-1; k++) {
			i--;
			mat[i][j] = mat[i+1][j] + 1;
		}
		
		int nextStartVal = mat[i][j] + 1;
		fill(mat, width-2, nextStartVal);
	}
};


int main(int argc, char *argv[]) {
	Solution s;
	vector<vector<int>> mtx = s.generateMatrix(3);
	for(auto& r : mtx) {
		for(auto& elem : r) {
			cout << elem << " ";
		}
		cout << endl;
	}
	return 0;
}