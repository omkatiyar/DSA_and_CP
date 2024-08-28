import markdown
from bs4 import BeautifulSoup
import json

def markdown_to_json(markdown_text):
    # Convert Markdown to HTML
    html = markdown.markdown(markdown_text, extensions=['fenced_code'])

    # Parse the HTML using BeautifulSoup
    soup = BeautifulSoup(html, 'html.parser')

    def process_element(element):
        if element.name in ['h1', 'h2', 'h3', 'h4', 'h5', 'h6']:
            return {
                'type': 'header',
                'level': int(element.name[1]),
                'content': process_children(element)
            }
        elif element.name == 'p':
            return {
                'type': 'paragraph',
                'content': process_children(element)
            }
        elif element.name == 'ul':
            return {
                'type': 'list',
                'style': 'unordered',
                'items': [process_children(li) for li in element.find_all('li', recursive=False)]
            }
        elif element.name == 'ol':
            return {
                'type': 'list',
                'style': 'ordered',
                'items': [process_children(li) for li in element.find_all('li', recursive=False)]
            }
        elif element.name == 'li':
            return process_children(element)
        elif element.name == 'blockquote':
            content = process_children(element)
            # Simplify if blockquote contains only one paragraph
            if isinstance(content, dict) and content.get('type') == 'paragraph':
                content = content['content']
            return {
                'type': 'blockquote',
                'content': content
            }
        elif element.name == 'pre':
            # Check for code blocks
            code = element.find('code')
            if code:
                return {
                    'type': 'code_block',
                    'content': code.get_text().rstrip('\n')
                }
            else:
                return {
                    'type': 'pre',
                    'content': element.get_text()
                }
        elif element.name == 'code':
            return {
                'type': 'code_inline',
                'content': element.get_text()
            }
        elif element.name == 'strong':
            return {
                'type': 'strong',
                'content': process_children(element)
            }
        elif element.name == 'em':
            return {
                'type': 'emphasis',
                'content': process_children(element)
            }
        elif element.name == 'a':
            return {
                'type': 'link',
                'href': element.get('href'),
                'content': process_children(element)
            }
        elif element.name == 'img':
            return {
                'type': 'image',
                'src': element.get('src'),
                'alt': element.get('alt', '')
            }
        else:
            # For any other tags, process its children
            if element.name is not None:
                return process_children(element)
            else:
                # NavigableString
                text = element.string
                if text and text.strip():
                    return text
                else:
                    return None

    def process_children(element):
        children = []
        for child in element.contents:
            processed_child = process_element(child)
            if processed_child is None:
                continue
            if isinstance(processed_child, list):
                children.extend(processed_child)
            else:
                children.append(processed_child)
        if len(children) == 1:
            return children[0]
        return children

    # Start processing from the body of the document
    results = []
    for child in soup.contents:
        processed = process_element(child)
        if processed is None:
            continue
        if isinstance(processed, list):
            results.extend(processed)
        else:
            results.append(processed)

    return json.dumps(results, indent=4)