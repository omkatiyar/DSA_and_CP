import cppyy
import unittest

# Load the C++ source file
cppyy.include("ideal_completion.cpp")

# Import the C++ class
ContactBook = cppyy.gbl.ContactBook

class TestContactBook(unittest.TestCase):

    def setUp(self):
        # Set up a fresh instance of ContactBook before each test
        self.cb = ContactBook()

    def test_create_node(self):
        self.cb.CreateNode("Alice", 1234567890)
        self.cb.CreateNode("Bob", 9876543210)
        result = self.cb.SearchByName("Alice")
        self.assertEqual(result, 1)
        result = self.cb.SearchByNumber(9876543210)
        self.assertEqual(result, 1)

    def test_search_by_name(self):
        self.cb.CreateNode("Charlie", 1112223333)
        result = self.cb.SearchByName("Charlie")
        self.assertEqual(result, 1)
        result = self.cb.SearchByName("NonExistent")
        self.assertEqual(result, 0)

    def test_search_by_number(self):
        self.cb.CreateNode("David", 4445556666)
        result = self.cb.SearchByNumber(4445556666)
        self.assertEqual(result, 1)
        result = self.cb.SearchByNumber(9998887777)
        self.assertEqual(result, 0)

    def test_edit_contact_by_name(self):
        self.cb.CreateNode("Eve", 7778889990)
        result = self.cb.EditContactByName("Eve", "Eve Adams", 1122334455)
        self.assertEqual(result, 1)
        result = self.cb.SearchByName("Eve Adams")
        self.assertEqual(result, 1)
        result = self.cb.SearchByNumber(1122334455)
        self.assertEqual(result, 1)

    def test_delete_contact_by_name(self):
        self.cb.CreateNode("Frank", 5556667777)
        result = self.cb.DeleteContactByName("Frank")
        self.assertEqual(result, 1)
        result = self.cb.SearchByName("Frank")
        self.assertEqual(result, 0)

    def test_delete_contact_by_number(self):
        self.cb.CreateNode("Grace", 8889990000)
        result = self.cb.DeleteContactByNumber(8889990000)
        self.assertEqual(result, 1)
        result = self.cb.SearchByNumber(8889990000)
        self.assertEqual(result, 0)

    def test_display(self):
        self.cb.CreateNode("Heidi", 3334445555)
        self.cb.CreateNode("Ivan", 6667778888)
        self.cb.Display()
        # You can check stdout here if necessary, but typically it's better to check return values or state changes

    def test_delete_all_contacts(self):
        self.cb.CreateNode("Judy", 1231231234)
        self.cb.CreateNode("Karl", 9879879876)
        self.cb.DeleteAllContacts()
        result = self.cb.SearchByName("Judy")
        self.assertEqual(result, 0)
        result = self.cb.SearchByNumber(9879879876)
        self.assertEqual(result, 0)

    def test_save_and_load(self):
        # Test saving and loading contacts from a file
        self.cb.CreateNode("Liam", 2223334444)
        self.cb.SaveToFile()
        new_cb = ContactBook()  # New instance to load from file
        new_cb.LoadFromFile()
        result = new_cb.SearchByName("Liam")
        self.assertEqual(result, 1)

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
