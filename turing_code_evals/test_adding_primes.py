import cppyy
import unittest
import os

class TestMathOperations(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ source file
            cpp_file_path = "adding_primes.cpp"
            if not os.path.exists(cpp_file_path):
                raise FileNotFoundError(f"{cpp_file_path} not found")
            
            cppyy.include(cpp_file_path)
        except FileNotFoundError as e:
            cls.fail(f"Setup failed: {str(e)}")
        except Exception as e:
            cls.fail(f"Error during C++ compilation: {str(e)}")
    
    def test_edge_case(self):
        self.assertEqual(cppyy.gbl.sumOfPrimes(0), 0)  

    def test_normal_cases(self):
        self.assertEqual(cppyy.gbl.sumOfPrimes(1), 0)  
        self.assertEqual(cppyy.gbl.sumOfPrimes(3), 2)  
        self.assertEqual(cppyy.gbl.sumOfPrimes(5), 5)  
        self.assertEqual(cppyy.gbl.sumOfPrimes(30), 129)  

    def test_large_inputs(self):
        self.assertEqual(cppyy.gbl.sumOfPrimes(100000), 454396537) 

if __name__ == '__main__':
    unittest.main(verbosity=2)
