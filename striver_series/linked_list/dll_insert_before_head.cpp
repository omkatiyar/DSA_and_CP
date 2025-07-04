#include <bits/stdc++.h>
using namespace std;
class Node{
public:
    int data;
    Node* next;
    Node* prev;
    Node(int data, Node* next = nullptr, Node* prev = nullptr){
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

void printLL(Node* head){
    Node* temp = head;
    while (temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

Node* convertArraytoLL(vector<int>a){
    if(a.size()==0)
    return nullptr;
    Node* head = new Node(a[0]);
    head->prev = nullptr;
    Node* current = head;
    int i=1; int n=a.size();
    while(i < n){
        Node* temp = new Node(a[i]);
        current->next = temp;
        temp->prev = current;
        current = temp;
        i++;
    }
    return head;
}

Node* insertBeforeHead(Node* head, int val){
    if(head == NULL)
    return new Node(val);
    Node* newHead = new Node(val,head,nullptr);
    head->prev = newHead;
    
    return newHead;
}

int main(){
    vector<int>v = {20, 2, 15, 34, 5};
    Node* head = convertArraytoLL(v);
    head = insertBeforeHead(head, 10);
    printLL(head);
}

