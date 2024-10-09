import unittest
from unittest.mock import patch

from sliding_window_median import medianSlidingWindow

class TestMedianSlidingWindow(unittest.TestCase):

    def assert_median_output(self, expected_output, nums, k):
        result = medianSlidingWindow(nums, k)
        self.assertEqual(result, expected_output)

    def test_negative_array_case(self):
        nums1 = [1, 3, -1, -3, 5, 3, 6, 7]
        k1 = 3
        expected_output = [1.00000, -1.00000, -1.00000, 3.00000, 5.00000, 6.00000]
        self.assert_median_output(expected_output, nums1, k1)

    def test_positive_zig_zag_array_case(self):
        nums2 = [1, 2, 3, 4, 2, 3, 1, 4, 2]
        k2 = 4
        expected_output = [2.50000, 2.50000, 3.00000, 2.50000, 2.50000, 2.50000]
        self.assert_median_output(expected_output, nums2, k2)

    def test_basic_case(self):
        nums3 = [1, 3, 2, 5, 4]
        k3 = 3
        expected_output = [2.00000, 3.00000, 4.00000]
        self.assert_median_output(expected_output, nums3, k3)

    def test_large_case(self):
        nums4 = list(range(1, 10001))  # A large list from 1 to 10000
        k4 = 500
        # Expected output is the median of each sliding window; here we focus on just testing performance and no precise values are needed.
        expected_output = [i + 250.5 for i in range(0, 9501)]  # Medians will be i + 250.5 for this range
        self.assert_median_output(expected_output, nums4, k4)

if __name__ == '__main__':
    unittest.main(verbosity=2)
