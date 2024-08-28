#include<iostream>
#include<vector>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* node = new Node();  // Using new instead of malloc
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void insert(vector<Node*>& tree, int value) {
    Node* newNd = newNode(value);
    tree.push_back(newNd);
}

void display(const vector<Node*>& tree) {
    for (const auto& node : tree) {
        cout << node->data << " ";
    }
    cout << endl;
}

int leftChild(int index) {
    return 2 * index + 1;
}

int rightChild(int index) {
    return 2 * index + 2;
}

int parent(int index) {
    return (index - 1) / 2;
}

// Function to clean up memory for the entire tree
void deleteTree(vector<Node*>& tree) {
    for (auto& node : tree) {
        delete node;
    }
    tree.clear();
}

int main() {
    vector<Node*> tree;  // Using vector to store the tree nodes

    // Insert values into the tree
    insert(tree, 1);
    insert(tree, 2);
    insert(tree, 3);
    insert(tree, 4);
    insert(tree, 5);
    insert(tree, 6);

    // Display the tree
    display(tree);

    // Free memory
    deleteTree(tree);

    return 0;
}
