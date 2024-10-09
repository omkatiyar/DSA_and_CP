import unittest
import signal
from collections import defaultdict, deque
from typing import List
from shortest_distance_queries import shortestDistanceAfterQueries


# Timeout handler and exception
class TimeoutException(Exception):
    pass

def timeout_handler(signum, frame):
    raise TimeoutException("Test timed out!")

# Unit test code
class TestShortestDistanceAfterQueries(unittest.TestCase):

    def setUp(self):
        self.timeout = 1  # Timeout of 1 second

    # Timeout wrapper using signal to stop long-running tests
    def run_with_timeout(self, func, *args, **kwargs):
        signal.signal(signal.SIGALRM, timeout_handler)
        signal.setitimer(0, self.timeout, 0)

        try:
            result = func(*args, **kwargs)
            signal.setitimer(0, 0, 0)
            # signal.alarm(0)  # Reset the alarm
            return result
        except TimeoutException as e:
            raise TimeoutError(f"Test exceeded time limit of {self.timeout} seconds.")

    def test_normal_case(self):
        n = 5
        queries = [[2, 4], [0, 2], [0, 4]]
        expected_output = [3, 2, 1]

        result_yours = shortestDistanceAfterQueries( n, queries)
        self.assertEqual(result_yours, expected_output)

    def test_case_no_removal(self):
        n = 4
        queries = [[0, 1], [2, 3]]
        expected_output = [3, 3] 

        result_yours = shortestDistanceAfterQueries(n, queries)
        self.assertEqual(result_yours, expected_output)

    def test_basic_edge_case(self):
        n = 2
        queries = [[0, 1]]
        expected_output = [1]

        result_yours = shortestDistanceAfterQueries(n, queries)
        self.assertEqual(result_yours, expected_output)

    def test_basic_edge_case1(self):
        n = 10
        queries = [[0, 5], [1, 3], [7, 9], [3, 7], [2, 9]]
        expected_output = [5, 5, 4, 4, 3]

        result_yours = shortestDistanceAfterQueries(n, queries)
        self.assertEqual(result_yours, expected_output)

    def test_large_case(self):
        n = 100000 
        queries = [[i, i + 1] for i in range(n-1)] 
        expected_output = [n-1] * (n-1) 

        result_yours = self.run_with_timeout(shortestDistanceAfterQueries, n, queries)
        self.assertEqual(result_yours, expected_output)


if __name__ == '__main__':
    unittest.main(verbosity=2)