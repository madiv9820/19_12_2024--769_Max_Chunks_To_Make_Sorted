#include <vector>
using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        // Get the size of the input array
        int n = arr.size();

        // Create two vectors:
        // `prefixMax` stores the maximum value encountered up to index i
        // `suffixMin` stores the minimum value encountered from index i to the end
        vector<int> prefixMax = arr;
        vector<int> suffixMin = arr;

        // Populate the `prefixMax` array:
        // For each index, store the maximum value from the start of the array to that index
        for(int index = 1; index < n; ++index) 
            prefixMax[index] = max(prefixMax[index-1], prefixMax[index]);

        // Populate the `suffixMin` array:
        // For each index, store the minimum value from that index to the end of the array
        for(int index = n-2; index >= 0; --index) 
            suffixMin[index] = min(suffixMin[index+1], suffixMin[index]);

        // Initialize a counter for the number of chunks
        int chunks = 0;

        // Check for each index if the array can be split into a chunk:
        // If `suffixMin[index]` (the minimum value to the right of the index) is greater
        // than `prefixMax[index-1]` (the maximum value to the left of the index), 
        // then it's a valid place to split the array into chunks.
        for(int index = 0; index < n; ++index) {
            // For the first element (index 0), it's automatically a chunk
            // For other elements, check if `suffixMin[index]` > `prefixMax[index-1]`
            if(index == 0 || suffixMin[index] > prefixMax[index-1]) 
                ++chunks;  // Increase the chunk count
        }

        // Return the number of chunks
        return chunks;
    }
};