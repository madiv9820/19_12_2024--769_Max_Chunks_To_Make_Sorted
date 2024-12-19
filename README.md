- ## Approach 4:- Maximum Element
    - ### Intuition
        The problem is asking for the maximum number of chunks that we can divide the array into, such that each chunk can be independently sorted and when combined will result in the original array. The idea is to look for points in the array where we can split the array, ensuring that elements on the left of this point are smaller than or equal to elements on the right after sorting.

        To solve this efficiently:
        - We can track the largest element encountered so far while iterating through the array.
        - If at any point the largest element matches the current index, it indicates that we can safely split the array at this index, since all elements up to this point can be rearranged independently.

    - ### Approach
        1. **Initialize**:
            - `chunks = 0`: To count how many valid chunks we can form.
            - `maxElement = -1`: To track the largest element encountered so far in the array.

        2. **Iterate** through the array:
            - For each element, update `maxElement` to the maximum of the current `maxElement` and the current element (`arr[index]`).
        
        3. **Identify a valid chunk**:
            - If `maxElement == index`, it means all elements from the start up to this index can be rearranged independently into a sorted chunk.
            - Increment the chunk count when this condition is met.

        4. **Return the result**:
            - After iterating through the array, the value of `chunks` will be the number of chunks we can split the array into.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
            class Solution:
                def maxChunksToSorted(self, arr: List[int]) -> int:
                    # Initialize chunks to 0 and maxElement to a value smaller than any possible element in arr.
                    chunks, maxElement = 0, -1

                    # Loop through each index in the array.
                    for index in range(len(arr)):
                        # Update maxElement to the maximum of the current maxElement and the current element arr[index].
                        maxElement = max(maxElement, arr[index])
                        
                        # If the maxElement is equal to the current index, it means that the array can be divided into
                        # a valid chunk at this index, and we increment the chunk count.
                        # This happens when all elements up to this index are smaller than or equal to the max element.
                        chunks += 1 if maxElement == index else 0

                    # Return the total number of chunks formed.
                    return chunks
            ```
        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity:
        - **$O(n)$**, where **$n$** is the length of the array. We only need to iterate through the array once, and each operation inside the loop (finding the maximum and comparing it to the index) is constant time. Thus, the overall time complexity is linear.

    - ### Space Complexity:
        - **$O(1)$**, as we are only using a few variables (`chunks`, `maxElement`), regardless of the size of the input array. The space complexity is constant.