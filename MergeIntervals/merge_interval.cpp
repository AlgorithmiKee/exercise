#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Define a vector of vector<int>
    vector<vector<int>> vec = {
        {3, 7, 2},
        {1, 4, 9},
        {1, 2},
        {5, 2, 8},
        {3, 1, 4}
    };

    // Sort the vector of vectors using std::sort
    // This will sort primarily by the first element, then by second element, and so on.
    sort(vec.begin(), vec.end());

    // Print the sorted vector of vectors
    for (const auto& innerVec : vec) {
        for (const auto& elem : innerVec) {
            cout << elem << " ";
        }
        cout << endl;
    }

    // test vector erase
    vector<int> v = {0,1,2,3,4,5};
    auto it = v.begin()+2;
    cout << "before removing v.begin()+2: " << *it << endl;
    v.erase(it);
    cout << "after removing v.begin()+2: " << *it << endl;


    return 0;
}