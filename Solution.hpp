#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        // Initialize a stack to help track the current "monotonic" subsequence.
        stack<int> monotonicStack;

        // Loop through each element in the array.
        for (int index = 0; index < arr.size(); ++index) {
            // If the stack is empty or the current element is greater than the top of the stack,
            // it means we are still forming a valid increasing subsequence, so push the element onto the stack.
            if (monotonicStack.empty() || arr[index] > monotonicStack.top()) {
                monotonicStack.push(arr[index]);
            } else {
                // If the current element is smaller than or equal to the top of the stack,
                // we need to "close" the current chunk. 
                // We pop the elements off the stack until we find a position where the element is 
                // greater than or equal to the current one.
                int maxElement = monotonicStack.top();
                
                // Pop elements from the stack as long as the current element is smaller than the stack's top.
                while (!monotonicStack.empty() && monotonicStack.top() > arr[index]) {
                    monotonicStack.pop();
                }

                // Push the maximum element (which is the largest value encountered in this chunk) back onto the stack.
                monotonicStack.push(maxElement);
            }
        }

        // The size of the stack will give the number of chunks, as the stack keeps track of the "ends" of each chunk.
        return monotonicStack.size();
    }
};