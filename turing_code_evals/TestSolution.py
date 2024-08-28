import ctypes
import unittest
import os
import platform

class TestSolution(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Determine the correct library file name based on the platform
        if platform.system() == "Linux":
            lib_name = "libsolution.so"
        elif platform.system() == "Windows":
            lib_name = "solution.dll"
        elif platform.system() == "Darwin":
            lib_name = "libsolution.dylib"
        else:
            raise Exception(f"Unsupported platform: {platform.system()}")

        # Load the shared library
        cls.lib = ctypes.CDLL(os.path.abspath(lib_name))

        # Define the function prototypes
        cls.lib.Solution_new.restype = ctypes.POINTER(ctypes.c_void_p)
        cls.lib.Solution_delete.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
        cls.lib.Solution_maximumTotalDamage.argtypes = [ctypes.POINTER(ctypes.c_void_p), ctypes.POINTER(ctypes.c_int), ctypes.c_int]
        cls.lib.Solution_maximumTotalDamage.restype = ctypes.c_int

        # Create an instance of the Solution class
        cls.solution = cls.lib.Solution_new()

    @classmethod
    def tearDownClass(cls):
        # Clean up and delete the Solution instance
        cls.lib.Solution_delete(cls.solution)

    def test_case_with_different_complete_days(self):
        # Create a C array from a Python list
        damage_list = [12,12,30,24,24]
        damage_array = (ctypes.c_int * len(damage_list))(*damage_list)
        # Call the maximumTotalDamage method
        expected_output = 2
        result = self.lib.Solution_maximumTotalDamage(self.solution, damage_array, len(damage_list))
        self._expected_output = expected_output
        self._user_output = result
        self.assertEqual(result, expected_output)
    
    def test_case_with_greater_complete_days(self):
        # Create a C array from a Python list
        damage_list = [72,48,24,3]
        damage_array = (ctypes.c_int * len(damage_list))(*damage_list)
        # Call the maximumTotalDamage method
        expected_output = 3
        result = self.lib.Solution_maximumTotalDamage(self.solution, damage_array, len(damage_list))
        self._expected_output = expected_output
        self._user_output = result
        self.assertEqual(result, expected_output)

class CustomTestResult(unittest.TextTestResult):
    def addSuccess(self, test):
        super().addSuccess(test)
        print(f"{test._testMethodName} : PASS Expected_Output: {test._expected_output}  User_Output: {test._user_output}")

    def addFailure(self, test, err):
        super().addFailure(test, err)
        print(f"{test._testMethodName} : FAIL Expected_Output: {test._expected_output}  User_Output: {test._user_output}")

    def addError(self, test, err):
        super().addError(test, err)
        print(f"{test._testMethodName} : ERROR Expected_Output: {test._expected_output}  User_Output: {test._user_output}")

class CustomTestRunner(unittest.TextTestRunner):
    def run(self, test):
        result = CustomTestResult(self.stream, self.descriptions, self.verbosity)
        test(result)
        return result

if __name__ == "__main__":
    unittest.main(testRunner=CustomTestRunner(verbosity=2))
