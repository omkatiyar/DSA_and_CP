import unittest
import os
import cppyy

class TestMaxXorSum(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ code from the file
            cpp_file_path = "model_max_xor_sum.cpp"
            if not os.path.exists(cpp_file_path):
                raise FileNotFoundError(f"{cpp_file_path} not found")

            with open(cpp_file_path, 'r') as cpp_file:
                cpp_code = cpp_file.read()

            # Compile the C++ code using cppyy
            cppyy.cppdef(cpp_code)
        except FileNotFoundError as e:
            cls.fail(f"Setup failed: {str(e)}")
        except Exception as e:
            cls.fail(f"Error during C++ compilation: {str(e)}")

    def test_basic(self):
        S = cppyy.gbl.std.vector[int]([1, 2, 3, 4, 5])
        result = cppyy.gbl.maximize_xor_sum(5,S)
        expected_value = 10737418221
        self.assertEqual(result, expected_value)

    def test_normal_case(self):
        S = cppyy.gbl.std.vector[int]([100, 92, 87, 50])
        result = cppyy.gbl.maximize_xor_sum(4,S)
        expected_value = 8589934427
        self.assertEqual(result, expected_value)
    
    def test_large_case(self):
        S = cppyy.gbl.std.vector[int]([10, 74, 11, 37, 48, 70, 56, 49, 48, 20, 78, 61, 52, 46,  8, 69, 47, 50, 18, 63, 58, 37, 38,  7, 46, 30, 73, 61, 32, 15, 29, 80, 68, 73, 76, 71, 35, 69,  3, 37, 59, 47, 37, 72, 80, 75, 24, 77, 15, 23, 39, 63,  3, 78, 59, 19, 78, 33, 37,  9, 46, 26, 28, 23, 43, 55,  9, 48, 53, 26, 12, 68, 37, 34, 68, 52, 32,  4, 56, 70, 64, 59, 22, 49, 78, 79,  2, 69, 20,  3, 16, 34, 15, 27, 32,  1, 14, 46,  1, 29])
        result = cppyy.gbl.maximize_xor_sum(100,S)
        expected_value = 214748360502
        self.assertEqual(result,expected_value)

if __name__ == '__main__':
    unittest.main(verbosity=2)
