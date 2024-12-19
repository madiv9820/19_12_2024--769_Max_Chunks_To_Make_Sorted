from typing import List

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