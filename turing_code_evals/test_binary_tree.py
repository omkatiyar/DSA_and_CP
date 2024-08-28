import unittest
import os
import cppyy

class TestBinaryTreeFunctions(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ code from the file
            cpp_file_path = "binary_tree_array.cpp"
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

    def test_newNode(self):
        node = cppyy.gbl.newNode(10)
        self.assertEqual(node.data, 10)
        self.assertFalse(bool(node.left))  # Check if left pointer is NULL
        self.assertFalse(bool(node.right))  # Check if right pointer is NULL

    def test_insert_and_structure(self):
        tree = cppyy.gbl.std.vector['Node*']()
        cppyy.gbl.insert(tree, 1)
        cppyy.gbl.insert(tree, 2)
        cppyy.gbl.insert(tree, 3)

        self.assertEqual(len(tree), 3)
        self.assertEqual(tree[0].data, 1)
        self.assertEqual(tree[cppyy.gbl.leftChild(0)].data, 2)
        self.assertEqual(tree[cppyy.gbl.rightChild(0)].data, 3)

        cppyy.gbl.deleteTree(tree)

    def test_parent_child_relationships(self):
        tree = cppyy.gbl.std.vector['Node*']()
        cppyy.gbl.insert(tree, 10)
        cppyy.gbl.insert(tree, 20)
        cppyy.gbl.insert(tree, 30)
        cppyy.gbl.insert(tree, 40)
        cppyy.gbl.insert(tree, 50)
        
        # Test relationships
        self.assertEqual(tree[cppyy.gbl.leftChild(0)].data, 20)
        self.assertEqual(tree[cppyy.gbl.rightChild(0)].data, 30)
        self.assertEqual(tree[cppyy.gbl.leftChild(1)].data, 40)
        self.assertEqual(tree[cppyy.gbl.rightChild(1)].data, 50)
        self.assertEqual(tree[cppyy.gbl.parent(1)].data, 10)

        cppyy.gbl.deleteTree(tree)

if __name__ == '__main__':
    unittest.main(verbosity=2)
