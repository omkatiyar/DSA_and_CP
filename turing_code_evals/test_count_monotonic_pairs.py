import unittest
import os
import cppyy

class TestCountMonotonicPairs(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ code from the file
            cpp_file_path = "ideal_completion.cpp"
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
        nums = [2,3,2]
        nums_vector = cppyy.gbl.std.vector[int](nums)
        result = cppyy.gbl.countMonotonicPairs(nums_vector)
        expected_value = 4
        self.assertEqual(result, expected_value)

    def test_large_value(self):
        nums = [20,25,28,35,40,50,45]
        nums_vector = cppyy.gbl.std.vector[int](nums)
        result = cppyy.gbl.countMonotonicPairs(nums_vector)
        expected_value = 170544 
        self.assertEqual(result, expected_value)

if __name__ == '__main__':
    unittest.main(verbosity=2)
