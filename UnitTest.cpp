#include "Solution.hpp"
#include <iostream>

struct testcase {
    vector<int> arr;
    int output;
};

class UnitTest {
private:
    vector<testcase> testcases;
    Solution obj;
    
public:
    UnitTest() {
        testcases.push_back({{4,3,2,1,0}, 1});
        testcases.push_back({{1,0,2,3,4}, 4});
    }

    void test() {
        for(int i = 0; i < testcases.size(); ++i) {
            vector<int> arr = testcases[i].arr;
            int output = testcases[i].output;

            int result = obj.maxChunksToSorted(arr);
            cout << "Testcase " << i+1 << ": " << ((result == output) ? "passed":"failed") << endl;
        }
    }
};

int main() {
    UnitTest test;
    test.test();
}