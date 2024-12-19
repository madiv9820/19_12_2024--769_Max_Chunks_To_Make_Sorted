## Approach 2:- Prefix Sum
- ### Intuition
    The goal is to find the maximum number of chunks into which the array can be split, such that each chunk can be independently sorted and then reassembled to form the original array. The key observation is that a valid chunk can be formed if the sum of elements in the chunk is equal to the sum of indices for that chunk, under the assumption that the chunk is in its correct order. 

    We can exploit this property by comparing the prefix sum of elements in the array with the sum of the indices. If at any index `i`, the sum of elements from index `0` to `i` is equal to the sum of indices from `0` to `i`, then it suggests that the subarray up to this index can be considered as one valid chunk.

- ### Approach
    1. **Initialize variables**:
            - `prefixSum`: Tracks the running sum of elements in the array.
            - `sortedPrefixSum`: Tracks the running sum of indices from `0` to `i` (theoretical sorted order).

    2. **Iterate through the array**:
            - For each index `i`, add `arr[i]` to `prefixSum` and `i` to `sortedPrefixSum`.
            - If `prefixSum` equals `sortedPrefixSum`, this indicates that the chunk from index `0` to `i` can be a valid chunk.
            - Increment the chunk count each time the condition holds.

    3. **Return the total number of chunks**:
            - Once the loop is complete, the variable `chunks` holds the number of valid chunks that can be formed.

- ### Code Implementation
    - **Python Solution**
        ```python3 []
        class Solution:
            def maxChunksToSorted(self, arr: List[int]) -> int:
                # Initialize the running prefix sum of array elements, 
                # and the running sum of indices (which is the sorted version).
                prefixSum = sortedPrefixSum = chunks = 0

                # Loop through each index of the array
                for index in range(len(arr)):
                    # Add the current element of the array to the prefix sum
                    prefixSum += arr[index]

                    # Add the current index to the sortedPrefixSum
                    # sortedPrefixSum is essentially the sum of indices 0, 1, 2, ..., up to the current index
                    sortedPrefixSum += index

                    # If the prefix sum matches the sorted prefix sum,
                    # it means we can form a chunk where the elements are sorted up to this point.
                    if prefixSum == sortedPrefixSum:
                        # Increment the chunk count
                        chunks += 1

                # Return the total number of chunks
                return chunks
        ```
    - **C++ Solution**
        ```cpp []
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
        ```

- ### Time Complexity
    - **Time Complexity**: **$O(n)$**, where **$n$** is the number of elements in the array.
        - We iterate through the array exactly once, performing constant time operations for each element.
    
    - **Total time complexity** is **$O(n)$**, which is optimal for this problem, as we need to inspect each element at least once.

- ### Space Complexity
    - **Space Complexity**: **$O(1)$**, because we only use a constant amount of extra space (the variables `prefixSum`, `sortedPrefixSum`, and `chunks`), regardless of the size of the input array.
    
    - **Total space complexity** is **$O(1)$**, which is optimal as we don't use any extra data structures that grow with the input size.