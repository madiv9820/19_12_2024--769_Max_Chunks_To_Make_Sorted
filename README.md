# [769. Max Chunks To Make Sorted](https://leetcode.com/problems/max-chunks-to-make-sorted) (All Approaches)

- ## [Approach 1:- PrefixMax and SuffixMin Arrays](https://github.com/madiv9820/19_12_2024--769_Max_Chunks_To_Make_Sorted/tree/Approach_01-Prefix_And_Suffix_Arrays)
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

- ## [Approach 2:- Prefix Sum](https://github.com/madiv9820/19_12_2024--769_Max_Chunks_To_Make_Sorted/tree/Approach_02-Prefix_Sum)
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

- ## [Approach 3:- Monotonic Increasing Stack](https://github.com/madiv9820/19_12_2024--769_Max_Chunks_To_Make_Sorted/tree/Approach_03-Monotic_Increasing_Stack)
    - ### Intuition
        The goal is to find the maximum number of chunks into which the array can be split such that each chunk can be independently sorted and reassembled to form the original array. 

        To solve this, we can use a **monotonic stack** to track the boundaries of these chunks. As we process the elements of the array:
        1. We maintain a stack that stores elements in increasing order.
        2. When we encounter an element that is smaller than the top of the stack, it indicates the end of a chunk. We then attempt to find a valid chunk by popping elements from the stack.
        3. The size of the stack at the end will give the number of chunks because the stack represents the "ends" of each chunk.

        - #### Key Insight:
            - **Chunks** are valid if elements within the chunk can be sorted independently without affecting other chunks.
            - By maintaining a stack of elements, we can efficiently identify where chunks end and count how many chunks we can form.

    - ### Approach
        1. **Initialize** an empty stack (`monotonicStack`).
        2. **Iterate** through the array:
            - If the current element is larger than the top of the stack or if the stack is empty, push the current element onto the stack.
            - If the current element is smaller than the top of the stack, it indicates the end of the current chunk:
                - Pop elements from the stack until we find an element smaller than the current element.
                - Push the maximum element encountered during the popping back onto the stack.
        3. **Return** the size of the stack at the end, which corresponds to the number of chunks.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
            class Solution:
                def maxChunksToSorted(self, arr: List[int]) -> int:
                    # Initialize an empty stack to keep track of the current "monotonic" subsequence.
                    monotonicStack = []

                    # Iterate through each element in the input array.
                    for element in arr:
                        # If the stack is empty or the current element is greater than the top element of the stack,
                        # it means the current element can be part of the increasing subsequence, so we push it onto the stack.
                        if not monotonicStack or element > monotonicStack[-1]:
                            monotonicStack.append(element)
                        else:
                            # If the current element is smaller than or equal to the top element of the stack,
                            # we need to "close" the current chunk, which means we need to pop the elements
                            # that are larger than the current element until we find a valid chunk boundary.
                            maxElement = monotonicStack[-1]

                            # Pop elements from the stack as long as they are greater than the current element.
                            # These elements will be part of the previous chunk.
                            while monotonicStack and monotonicStack[-1] > element:
                                monotonicStack.pop()

                            # Push the largest element (maxElement) from the popped elements back onto the stack,
                            # since it represents the maximum value of the current chunk.
                            monotonicStack.append(maxElement)

                    # The number of chunks is represented by the size of the stack, since each element in the stack
                    # corresponds to a valid chunk boundary.
                    return len(monotonicStack)
            ```
        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity:
        - **$O(n)$**, where **$n$** is the length of the array. Each element is pushed and popped from the stack at most once.
            - For each element, either it is pushed onto the stack or popped from the stack. Since each operation is constant time, the overall time complexity is linear.

    - ### Space Complexity:
        - **$O(n)$**, as the stack stores at most **$n$** elements (in the worst case when no elements are merged into chunks).
            - The space complexity is linear because the stack may need to store up to **$n$** elements in the worst case.

- ## [Approach 4:- Maximum Element](https://github.com/madiv9820/19_12_2024--769_Max_Chunks_To_Make_Sorted/tree/Approach_04-Maximum_Element)
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