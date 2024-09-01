#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(vector<Node*>& tree, int value) {
    Node* newNode =  newNode(value);
    tree.push_back(newNode);
}

void display(const vector<Node*>& tree) {
    cout << "Binary Tree (Array Representation): ";
    for (int i = 0; i < tree.size(); i++) {
        cout << tree[i]->data << " ";
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

void deleteTree(vector<Node*>& tree) {
    for (int i = 0; i < tree.size(); i++) {
        delete tree[i];
    }
    tree.clear();
}
