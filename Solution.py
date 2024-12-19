from typing import List

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