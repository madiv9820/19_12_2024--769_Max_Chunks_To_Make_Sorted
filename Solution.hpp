#include <vector>
using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        // Initialize chunks to 0 and maxElement to a value smaller than any possible element in arr.
        int chunks = 0, maxElement = -1;

        // Loop through each element in the array.
        for(int index = 0; index < arr.size(); ++index) {
            // Update the maxElement to be the maximum value encountered so far.
            maxElement = max(maxElement, arr[index]);

            // If the current maxElement is equal to the current index, 
            // it means that the array can be divided into a chunk at this point.
            // Increment the chunk count.
            chunks += (maxElement == index) ? 1 : 0;
        }

        // Return the total number of chunks.
        return chunks;
    }
};