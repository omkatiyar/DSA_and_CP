import cppyy
import unittest

# Load the C++ source file
cppyy.include("binary_tree.cpp")  # Replace with your actual filename

# Import the C++ functions and structs
Node = cppyy.gbl.Node
newNode = cppyy.gbl.newNode
insert = cppyy.gbl.insert
display = cppyy.gbl.display
leftChild = cppyy.gbl.leftChild
rightChild = cppyy.gbl.rightChild
parent = cppyy.gbl.parent

class TestBinaryTree(unittest.TestCase):

    def setUp(self):
        self.tree = cppyy.gbl.std.vector(Node)()  # Initialize a vector of Node*
        self.size = cppyy.gbl.int(0)  # Initialize size as a cppyy integer

    def test_new_node(self):
        node = newNode(10)
        self.assertEqual(node.data, 10)
        self.assertEqual(int(cppyy.addressof(node.left)), 0)  # Check for nullptr by address
        self.assertEqual(int(cppyy.addressof(node.right)), 0)  # Check for nullptr by address

    def test_insert_and_display(self):
        # Insert nodes directly into the C++ vector
        insert(self.tree, cppyy.addressof(self.size), 1)
        insert(self.tree, cppyy.addressof(self.size), 2)
        insert(self.tree, cppyy.addressof(self.size), 3)

        self.assertEqual(self.tree[0].data, 1)
        self.assertEqual(self.tree[1].data, 2)
        self.assertEqual(self.tree[2].data, 3)

        display(self.tree.data(), self.size)  # Pass the raw pointer and size to display

    def test_left_child(self):
        index = 1
        self.assertEqual(leftChild(index), 3)

    def test_right_child(self):
        index = 1
        self.assertEqual(rightChild(index), 4)

    def test_parent(self):
        index = 4
        self.assertEqual(parent(index), 1)

    def tearDown(self):
        # No need to manually delete elements, let C++ handle it if necessary
        self.tree.clear()

class CustomTestResult(unittest.TextTestResult):
    def addSuccess(self, test):
        super().addSuccess(test)
        print(f"{test._testMethodName}: PASS")

    def addFailure(self, test, err):
        super().addFailure(test, err)
        print(f"{test._testMethodName}: FAIL")

    def addError(self, test, err):
        super().addError(test, err)
        print(f"{test._testMethodName}: ERROR")

class CustomTestRunner(unittest.TextTestRunner):
    resultclass = CustomTestResult

if __name__ == '__main__':
    unittest.main(testRunner=CustomTestRunner())
