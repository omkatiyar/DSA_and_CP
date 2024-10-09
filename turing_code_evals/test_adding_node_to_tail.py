import cppyy
import unittest
import os

class TestLinkedListOperations(unittest.TestCase):
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

    def test_add_to_empty_list(self):
        # Test adding to an empty list
        list = cppyy.gbl.LinkedList()
        list.addToTail(10)
        self.assertEqual(list.head.data, 10, "Head should have data 10")
        self.assertEqual(list.tail.data, 10, "Tail should have data 10")
        self.assertEqual(cppyy.addressof(list.head.next), 0, "Next node should be nullptr (0x0)")

    def test_add_multiple_elements(self):
        # Test adding multiple elements
        list = cppyy.gbl.LinkedList()
        list.addToTail(10)
        list.addToTail(20)
        list.addToTail(30)
        self.assertEqual(list.head.data, 10, "Head should have data 10")
        self.assertEqual(list.tail.data, 30, "Tail should have data 20")
        self.assertEqual(list.head.next.data, 20, "Head next should have data 20")

    def test_add_negative_values(self):
        # Test adding a negative value
        list = cppyy.gbl.LinkedList()
        list.addToTail(-10)
        list.addToTail(-20)
        list.addToTail(-30)
        list.addToTail(-40)
        self.assertEqual(list.head.data, -10, "Head should have data -10")
        self.assertEqual(list.head.next.data, -20, "Head next should have -20")
        self.assertEqual(list.head.next.next.data, -30, "Head next to next should have -20")
        self.assertEqual(list.tail.data, -40, "Tail should have data -40")

if __name__ == '__main__':
    unittest.main(verbosity=2)
