from typing import List

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