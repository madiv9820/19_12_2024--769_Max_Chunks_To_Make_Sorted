- ## Approach 1:- PrefixMax and SuffixMin Arrays 
    - ### Intuition
        The problem asks us to find the maximum number of chunks in which we can split the array such that each chunk can be independently sorted and then reassembled to form the original array. 

        To solve this, we need to figure out how to identify the boundaries of each chunk. These boundaries are determined by comparing the maximum value up to each index and the minimum value from each index to the end of the array.

        - #### Key Insight:
            - A chunk can be formed at index `i` if the maximum value of the previous elements (up to `i-1`) is less than the minimum value of the elements from `i` to the end.
            - The challenge is to find where these chunks can be split, and we can do this by tracking the running maximum (`prefixMax`) and the running minimum (`suffixMin`).

    - ### Approach
        1. **Create Two Arrays:**
            - `prefixMax[i]`: Stores the maximum value from the start of the array to index `i`.
            - `suffixMin[i]`: Stores the minimum value from index `i` to the end of the array.

        2. **Populate Arrays:**
            - Traverse the array once from left to right to populate `prefixMax` where each element stores the maximum value seen up to that index.
            - Traverse the array again from right to left to populate `suffixMin` where each element stores the minimum value from that index to the end of the array.

        3. **Count Chunks:**
            - Traverse through the array and check the condition: If `suffixMin[i] > prefixMax[i-1]` (for `i > 0`), then it’s a valid split, and we can count it as a chunk.
            - Start with one chunk for the first element since it doesn’t need to be compared to anything before it.

        4. **Return the Total Chunks.**

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
            class Solution:
                def maxChunksToSorted(self, arr: List[int]) -> int:
                    # Get the length of the input array
                    n = len(arr)

                    # Initialize prefixMax and suffixMin with the original array
                    # These arrays will store the maximum values up to each index
                    # and the minimum values from each index to the end respectively
                    prefixMax = arr[:]
                    suffixMin = arr[:]

                    # Initialize the chunk counter
                    chunks = 0

                    # Step 1: Populate the prefixMax array
                    # For each index from 1 to n-1, store the maximum value up to that index
                    for index in range(1, n):
                        prefixMax[index] = max(prefixMax[index-1], prefixMax[index])

                    # Step 2: Populate the suffixMin array
                    # For each index from n-2 down to 0, store the minimum value from that index to the end of the array
                    for index in range(n-2, -1, -1):
                        suffixMin[index] = min(suffixMin[index+1], suffixMin[index])

                    # Step 3: Count the number of chunks
                    # A chunk is valid if suffixMin[index] > prefixMax[index-1]
                    for index in range(0, n):
                        # For the first element, it's automatically considered a chunk
                        # For other elements, check if the condition holds
                        if index == 0 or suffixMin[index] > prefixMax[index-1]:
                            chunks += 1

                    # Return the total number of chunks
                    return chunks
            ```
        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity
        - **Time Complexity**: **$O(n)$**, where **$n$** is the number of elements in the input array. 
            - We perform three linear passes over the array: 
                - One pass to populate `prefixMax`.
                - One pass to populate `suffixMin`.
                - One pass to count the chunks.
            
        - **Total time complexity** is **$O(n)$** because each pass takes **$O(n)$** time.

    - ### Space Complexity
        - **Space Complexity**: **$O(n)$**, because we use two additional arrays, `prefixMax` and `suffixMin`, each of size **$n$**, to store the intermediate results.

        - **Total space complexity** is **$O(n)$** due to the space required for these two arrays.