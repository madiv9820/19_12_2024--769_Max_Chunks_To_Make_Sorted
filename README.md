- ## Approach 3:- Monotonic Increasing Stack

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