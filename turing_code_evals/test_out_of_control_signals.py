import unittest
import os
import cppyy

class TestOutOfControlDetection(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ code from the file
            cpp_file_path = "model_out_of_control_signals.cpp"
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

    def test_basic_in_control_signal(self):
        data = cppyy.gbl.std.vector["double"]([-1,1,4])  
        result = cppyy.gbl.detect_out_of_control(data)
        self.assertEqual(result,True)

    def test_out_of_control_signal_rule_2(self):
        # Test Rule 2: Two out of three consecutive values more than 2 stddev away
        data = cppyy.gbl.std.vector["double"]([1,1,1,1,1,1,1,1,1,5,5])
        result = cppyy.gbl.detect_out_of_control(data)
        self.assertEqual(result, False)

    def test_out_of_control_signal_rule_3(self):
        # Test Rule 3: Four out of five consecutive values more than 1 stddev away
        data = cppyy.gbl.std.vector["double"]([30,32,35,40,45,47,50,55,60,62,65,70,75,80,85,90,95,100,114.84,119.84])
        result = cppyy.gbl.detect_out_of_control(data)
        self.assertEqual(result, False)

    def test_out_of_control_signal_with_rule_4(self):
        # Test Rule 5: Pattern of 10 out of 11 values on one side of the mean .... Here Rule 3 will be applied first
        data = cppyy.gbl.std.vector["double"]([2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,50,50,50,50])
        result = cppyy.gbl.detect_out_of_control(data)
        self.assertEqual(result, False)

    def test_out_of_control_signal_with_rule_5(self):
        # Test Rule 5: Pattern of 10 out of 11 values on one side of the mean
        data = cppyy.gbl.std.vector["double"]([10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29])
        result = cppyy.gbl.detect_out_of_control(data)
        self.assertEqual(result, False)

    def test_in_control_signal(self):
        # Test with data that should be in control
        data = cppyy.gbl.std.vector["double"]([50, 52, 51, 49, 50, 53, 51, 50, 52, 51, 50])
        result = cppyy.gbl.detect_out_of_control(data)
        self.assertEqual(result, True)

if __name__ == '__main__':
    unittest.main(verbosity=2)
