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
Node* insertAtPosK(Node* head,int k,int val){
    if(head == NULL || k<=1){
        Node* newHead = new Node(val);
        newHead->next = head;
        return newHead;
    }
    Node* curr = head;
    Node* prev = nullptr;
    int i=0;
    /*
curr LL :      20 -> 2 -> 15 -> 34 -> 5
exprected LL : 20 -> 2 -> 15 -> 10 -> 34 -> 5
*/
    while(curr!=NULL && i<k){
        i++;
        if(i==k){
            Node* temp = new Node(val);
            temp->next = prev->next->next;
            curr->next = temp;
            cout<<" curr/prev data is "<<prev->data<<" "<<endl;
            break;
        } 
        else{ 
            prev = curr;
        curr = curr->next;
        }
    }
    return head;
}
void printLL(Node* head){
    Node* temp = head;
    cout<<" printing the linked list "<<endl;
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
    head = insertAtPosK(head, 6, 10);
    printLL(head);
}
/*
curr LL : 20 -> 2 -> 15 -> 34 -> 5
exprected LL : 20 -> 2 -> 15 -> 10 -> 34 -> 5
*/