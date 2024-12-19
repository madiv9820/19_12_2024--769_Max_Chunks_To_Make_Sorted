from Solution import Solution
import unittest
from timeout_decorator import timeout

class UnitTest(unittest.TestCase):
    def setUp(self):
        self.__testcases = {1: ([4,3,2,1,0], 1), 2: ([1,0,2,3,4], 4)}
        self.__obj = Solution()
        return super().setUp()
    
    @timeout(0.5)
    def test_case_1(self):
        arr, output = self.__testcases[1]
        result = self.__obj.maxChunksToSorted(arr = arr)
        self.assertIsInstance(result, int)
        self.assertEqual(result, output)

    @timeout(0.5)
    def test_case_2(self):
        arr, output = self.__testcases[2]
        result = self.__obj.maxChunksToSorted(arr = arr)
        self.assertIsInstance(result, int)
        self.assertEqual(result, output)

if __name__ == '__main__': unittest.main()