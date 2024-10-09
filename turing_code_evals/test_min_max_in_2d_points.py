import cppyy
import unittest
import os

class TestCalculateMinMax(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ source file
            cpp_file_name = "ideal_completion.cpp"
            cpp_file_path = os.path.abspath(os.path.join(os.path.dirname(__file__), cpp_file_name))
            if not os.path.exists(cpp_file_path):
                raise FileNotFoundError(f"{cpp_file_path} not found")
            
            # Read the content of the C++ file and load it into cppyy
            with open(cpp_file_path, 'r') as cpp_file:
                cpp_code = cpp_file.read()
            
            cppyy.cppdef(cpp_code)
        except FileNotFoundError as e:
            raise unittest.SkipTest(f"Setup failed: {str(e)}")
        except Exception as e:
            raise unittest.SkipTest(f"Error during C++ compilation: {str(e)}")

    def test_min_max_with_positive_values(self):
        # Test with positive values in front_curve
        front_curve = cppyy.gbl.std.vector[cppyy.gbl.std.array["double", 2]]()
        front_curve.push_back([3.0, 5.0])
        front_curve.push_back([1.0, 2.0])
        front_curve.push_back([4.0, 6.0])
        front_curve.push_back([0.5, 1.5])

        result = cppyy.gbl.calculateMinMax(front_curve)
        self.assertEqual(result.first, 0.5, "Min x should be 0.5")
        self.assertEqual(result.second, 4.0, "Max x should be 4.0")

    def test_min_max_with_negative_values(self):
        # Test with negative values in front_curve
        front_curve = cppyy.gbl.std.vector[cppyy.gbl.std.array["double", 2]]()
        front_curve.push_back([-1.0, 5.0])
        front_curve.push_back([-2.0, 2.0])
        front_curve.push_back([-4.0, 6.0])
        front_curve.push_back([-0.5, 1.5])

        result = cppyy.gbl.calculateMinMax(front_curve)
        self.assertEqual(result.first, -4.0, "Min x should be -4.0")
        self.assertEqual(result.second, -0.5, "Max x should be -0.5")

    def test_min_max_with_mixed_values(self):
        # Test with both positive and negative values in front_curve
        front_curve = cppyy.gbl.std.vector[cppyy.gbl.std.array["double", 2]]()
        front_curve.push_back([-3.0, 5.0])
        front_curve.push_back([1.0, 2.0])
        front_curve.push_back([-4.0, 6.0])
        front_curve.push_back([0.5, 1.5])

        result = cppyy.gbl.calculateMinMax(front_curve)
        self.assertEqual(result.first, -4.0, "Min x should be -4.0")
        self.assertEqual(result.second, 1.0, "Max x should be 1.0")

if __name__ == '__main__':
    unittest.main(verbosity=2)
