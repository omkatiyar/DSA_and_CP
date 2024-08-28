import unittest
import os
import subprocess

class TestBitwiseOperation(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Compile the C program
        c_file = "testable_ideal_completion.c"
        executable = "testable_ideal_completion"
        compile_cmd = f"gcc {c_file} -o {executable}"
        compilation_result = os.system(compile_cmd)
        if compilation_result != 0:
            cls.fail("C program compilation failed")

    def run_c_program(self, inputs):
        # Run the compiled C program with inputs
        executable = "./testable_ideal_completion"
        process = subprocess.Popen(executable, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate(input=inputs.encode())
        if process.returncode != 0:
            self.fail(f"C program failed with error: {stderr.decode()}")
        return stdout.decode().strip()

    def test_basic(self):
        output = self.run_c_program("1F3\n4\n")
        self.assertIn("515", output)

    def test_zero_position(self):
        output = self.run_c_program("1F\n0\n")
        self.assertIn("32", output)

    def test_zero_input(self):
        output = self.run_c_program("0x00\n4\n")
        self.assertIn("16", output)

    def test_small_value(self):
        output = self.run_c_program("1\n3\n")
        self.assertIn("9", output)

    def test_non_zero_input(self):
        output = self.run_c_program("A\n1\n")
        self.assertIn("12", output)

if __name__ == '__main__':
    unittest.main(verbosity=2)
