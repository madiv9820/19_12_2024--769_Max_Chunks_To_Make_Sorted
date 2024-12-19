from typing import List

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