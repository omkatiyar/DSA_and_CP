import unittest
import json
from markdown_to_json import markdown_to_json  # Import the function to be tested

class TestMarkdownToJson(unittest.TestCase):

    def test_header_conversion(self):
        markdown_text = "# Header Level 1\n## Header Level 2\n### Header Level 3"
        expected_output = [
            {'type': 'header', 'level': 1, 'content': 'Header Level 1'},
            {'type': 'header', 'level': 2, 'content': 'Header Level 2'},
            {'type': 'header', 'level': 3, 'content': 'Header Level 3'}
        ]
        result = markdown_to_json(markdown_text)
        self.assertEqual(json.loads(result), expected_output)

    def test_paragraph_conversion(self):
        markdown_text = "This is a paragraph."
        expected_output = [{'type': 'paragraph', 'content': ['This is a paragraph.']}]
        result = markdown_to_json(markdown_text)
        self.assertEqual(json.loads(result), expected_output)

    def test_ordered_list_conversion(self):
        markdown_text = "1. First item\n2. Second item"
        expected_output = [{'type': 'list', 'style': 'ordered', 'items': ['First item', 'Second item']}]
        result = markdown_to_json(markdown_text)
        self.assertEqual(json.loads(result), expected_output)

    def test_unordered_list_conversion(self):
        markdown_text = "- First item\n- Second item"
        expected_output = [{'type': 'list', 'style': 'unordered', 'items': ['First item', 'Second item']}]
        result = markdown_to_json(markdown_text)
        self.assertEqual(json.loads(result), expected_output)

    def test_blockquote_conversion(self):
        markdown_text = "> This is a blockquote."
        expected_output = [{'type': 'blockquote', 'content': ['This is a blockquote.']}]
        result = markdown_to_json(markdown_text)
        self.assertEqual(json.loads(result), expected_output)

    def test_inline_code_conversion(self):
        markdown_text = "This is `inline code`."
        expected_output = [{'type': 'paragraph', 'content': ['This is ', {'type': 'code_inline', 'content': 'inline code'}, '.']}]
        result = markdown_to_json(markdown_text)
        self.assertEqual(json.loads(result), expected_output)

    def test_code_block_conversion(self):
        markdown_text = "```\nThis is a code block.\n```"
        expected_output = [{'type': 'code_block', 'content': 'This is a code block.'}]
        result = markdown_to_json(markdown_text)
        self.assertEqual(json.loads(result), expected_output)

if __name__ == '__main__':
    unittest.TextTestRunner(verbosity=2).run(unittest.makeSuite(TestMarkdownToJson))
