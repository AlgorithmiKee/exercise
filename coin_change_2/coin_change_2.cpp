#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	using MapPairToInt = vector<vector<int>>;
	
	int change(int amount, vector<int>& coins) {
		// construct mapping f(k,x):
		// the number of combinations that make up x dollars with nomination >= coins[k]
		MapPairToInt fcx(coins.size(), vector<int>(1+amount, -1));
		
		compute_fcx(0, amount, coins, fcx);
		return fcx[0][amount];
	}
	
	// assumes that coins is sorted
	void compute_fcx(int k, int x, const vector<int>& coins, MapPairToInt& fcx) {
		if(fcx[k][x] != -1) {
			return;
		}
		
		if(x == 0) {
			fcx[k][x] = 1;
			return;
		}
		
		if(x < 0) {
			fcx[k][x] = 0;
			return;
		}
				
		fcx[k][x] = 0;
		
		for(int i = k; i < coins.size(); i++) {
			if(x - coins[i] < 0) {
				continue;
			}
			compute_fcx(i, x - coins[i], coins, fcx);
			fcx[k][x] += fcx[i][x - coins[i]];
		}
	}
};

int main(int argc, char *argv[]) {
	Solution s;
	vector<int> coins = {2, 1};
	cout << s.change(3, coins) << endl;
	
	return 0;
}