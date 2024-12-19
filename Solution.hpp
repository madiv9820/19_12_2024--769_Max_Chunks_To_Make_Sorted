#include <vector>
using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        // Initialize variables for the running sum of the array elements
        // and the expected sum of indices (sorted version of the array).
        int prefixSum = 0, sortedPrefixSum = 0; 
        // Variable to count the number of chunks.
        int chunks = 0;
        // Variable to iterate over the array.
        int index = 0;

        // Iterate through the array
        for(; index < arr.size(); ++index) {
            // Add the current element of arr to the running prefix sum
            prefixSum += arr[index];

            // Add the current index to the running sortedPrefixSum
            // sortedPrefixSum is the sum of indices, which is the sum of 0 + 1 + 2 + ... up to current index
            sortedPrefixSum += index;

            // If the prefix sum matches the sorted prefix sum, it means we can form a chunk
            // This implies that the part of the array from the start up to this index is correctly ordered.
            if(prefixSum == sortedPrefixSum) {
                // Increment the chunk count
                ++chunks;
            }
        }

        // Return the total number of chunks found
        return chunks;
    }
};