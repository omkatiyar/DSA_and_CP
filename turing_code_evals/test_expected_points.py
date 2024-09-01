import unittest
import os
import cppyy

class TestExpectedPoints(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ code from the file
            cpp_file_path = "expected_points.cpp"
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
        S = cppyy.gbl.std.vector[int]([1, 2])
        P = cppyy.gbl.std.vector[int]([0, 100])
        result = cppyy.gbl.calculateExpectedValue(2,S,P)
        expected_value = "0/1"
        self.assertEqual(result, expected_value)

    def test_complex_zig_zag_array(self):
        S = cppyy.gbl.std.vector[int]([80, 30, 20, 100, 25, 35, 65, 78, 18, 22])
        P = cppyy.gbl.std.vector[int]([90, 80, 30, 40, 20, 24, 100, 45, 76, 84])
        result = cppyy.gbl.calculateExpectedValue(10,S,P)
        expected_value = "38011/2500"
        self.assertEqual(result, expected_value)

if __name__ == '__main__':
    unittest.main(verbosity=2)
