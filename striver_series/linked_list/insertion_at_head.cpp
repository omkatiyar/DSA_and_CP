#include <bits/stdc++.h>
using namespace std;
class Node{
public:
    int data;
    Node* next;
    Node(int data, Node* next = nullptr){
        this->data = data;
        this->next = next;
    }
};
Node* convertArraytoLL(vector<int>a){
    Node* head = nullptr;
    if(a.size()==0)
    return head;
    head = new Node(a[0]);
    Node* current = head;
    int i=1; int n=a.size();
    while(i < n){
        Node* temp = new Node(a[i]);
        current->next = temp;
        current = temp;
        i++;
    }
    return head;
}
Node* insertAtHead(Node* head, int data) {
    Node* temp = new Node(data);
    temp->next = head;
    head = temp;
    return head;
}
void printLL(Node* head){
    Node* temp = head;
    while (temp)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}
int main(){
    vector<int>v = {20, 2, 15, 34, 5};
    Node* head = convertArraytoLL(v);
    head = insertAtHead(head, 10);
    printLL(head);
}