import unittest, subprocess, os

class TestMaximumPages(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compile_command = ["g++", "-o", "testable_ideal_completion", "testable_ideal_completion.cpp"]

        # Compile the C++ code into an executable
        subprocess.run(compile_command, check=True)
        cls.exe_path = os.path.abspath("testable_ideal_completion")

    @classmethod
    def tearDownClass(cls):
        # Remove the compiled executable
        os.remove("testable_ideal_completion")

    def test_single_case(self):
        # Prepare the command-line arguments and expected output
        args = ["1", "4", "10", "20", "30", "40"]
        expected_output = "70"

        # Run the C++ executable and capture the output
        result = subprocess.run([self.exe_path] + args, text=True, capture_output=True)

        # Assert that the output matches the expected output
        self.assertEqual(result.stdout.strip(), expected_output.strip())

    def test_multiple_cases(self):
        # Prepare the command-line arguments and expected output
        args = ["2", "4", "10", "45", "50", "40", "3", "15", "25", "35"]
        expected_output = "90\n60"

        # Run the C++ executable and capture the output
        result = subprocess.run([self.exe_path] + args, text=True, capture_output=True)

        # Assert that the output matches the expected output
        self.assertEqual(result.stdout.strip(), expected_output.strip())

    def test_invalid_argument(self):
        # Prepare the command-line arguments with invalid type
        args = ["1", "4", "a", "20", "30", "40"]

        # Run the C++ executable with the arguments and capture the output
        result = subprocess.run([self.exe_path] + args, text=True, capture_output=True)

        # Check the return code and stderr message
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("Invalid argument", result.stderr)

    def test_argument_out_of_range(self):
        # Prepare the command-line arguments with values out of range for int
        args = ["1", "4", "999999999999999999999999999999", "20", "30", "40"]

        # Run the C++ executable with the arguments and capture the output
        result = subprocess.run([self.exe_path] + args, text=True, capture_output=True)

        # Check the return code and stderr message
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("Argument out of range", result.stderr)

    def test_not_enough_books(self):
        # Prepare the command-line arguments where fewer than 2 books are provided
        args = ["1", "1", "10"]

        # Run the C++ executable with the arguments and capture the output
        result = subprocess.run([self.exe_path] + args, text=True, capture_output=True)

        # Check the return code and stderr message
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("At least two books are required", result.stderr)

if __name__ == '__main__':
    unittest.main(verbosity=2)
