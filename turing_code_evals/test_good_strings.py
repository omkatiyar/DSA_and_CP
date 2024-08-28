import unittest
import os
import cppyy

class TestGoodString(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ code from the file
            cpp_file_path = "testable_ideal_completion.cpp"
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
        result = cppyy.gbl.countGoodNumbers(1)
        expected_value = 5
        self.assertEqual(result, expected_value)

    def test_normal_value(self):
        result = cppyy.gbl.countGoodNumbers(50)
        expected_value = 564908303
        self.assertEqual(result, expected_value)

    def test_large_numbers(self):
        result = cppyy.gbl.countGoodNumbers(10000)
        expected_value = 325891746 
        self.assertEqual(result, expected_value)

if __name__ == '__main__':
    unittest.main(verbosity=2)
