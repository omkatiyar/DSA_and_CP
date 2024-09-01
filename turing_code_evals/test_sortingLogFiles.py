import cppyy
import unittest
import os

# Load the C++ source file
cppyy.include("ideal_completion.cpp")

# Import the C++ function
from cppyy.gbl import reorderLogFiles  # type: ignore

class SortLogFiles(unittest.TestCase):

    def test_letter_logs_only(self):
        log = ["let3-art-zero", "let2-own-kit-dig", "let1-art-can"]
        log_vector = cppyy.gbl.std.vector[str](log)
        result_vector = reorderLogFiles(log_vector)
        result = [str(log) if isinstance(log, str) else log.decode('utf-8') for log in result_vector]
        expected_value = ["let1-art-can", "let3-art-zero", "let2-own-kit-dig"]
        self.assertEqual(result, expected_value)

    def test_digit_logs_only(self):
        log = ["dig1-81-1-5-1", "dig2-3-6", "dig1-31-22-53-11"]
        log_vector = cppyy.gbl.std.vector[str](log)
        result_vector = reorderLogFiles(log_vector)
        result = [str(log) if isinstance(log, str) else log.decode('utf-8') for log in result_vector]
        expected_value = ["dig1-81-1-5-1", "dig2-3-6", "dig1-31-22-53-11"]
        self.assertEqual(result, expected_value)

    def test_digit_and_letter_logs_simple_case(self):
        log = ["dig1-8-1-5-1", "let1-art-can", "dig2-3-6", "let2-own-kit-dig", "let3-art-zero"]
        log_vector = cppyy.gbl.std.vector[str](log)
        result_vector = reorderLogFiles(log_vector)
        result = [str(log) if isinstance(log, str) else log.decode('utf-8') for log in result_vector]
        expected_value = ["let1-art-can", "let3-art-zero", "let2-own-kit-dig", "dig1-8-1-5-1", "dig2-3-6"]
        self.assertEqual(result, expected_value)

    def test_letter_logs_with_same_content_case(self):
        log = ["a1-9-2-3-1", "g1-act-car", "zo4-4-7", "ab1-off-key-dog", "a8-act-zoo", "b1-act-car"]
        log_vector = cppyy.gbl.std.vector[str](log)
        result_vector = reorderLogFiles(log_vector)
        result = [str(log) if isinstance(log, str) else log.decode('utf-8') for log in result_vector]
        expected_value = ["b1-act-car", "g1-act-car", "a8-act-zoo", "ab1-off-key-dog", "a1-9-2-3-1", "zo4-4-7"]
        self.assertEqual(result, expected_value)


if __name__ == '__main__':
    unittest.main(verbosity=2)
