import unittest
import os
import cppyy

class TestMaxXorSum(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ code from the file
            cpp_file_path = "maximum_xor_sum.cpp"
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
        result = cppyy.gbl.maximize_xor_sum(10,S)
        expected_value = 8589934427
        self.assertEqual(result, expected_value)

if __name__ == '__main__':
    unittest.main(verbosity=2)
