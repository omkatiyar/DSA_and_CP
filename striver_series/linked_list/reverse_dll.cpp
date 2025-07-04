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

Node* insertAfterK(Node* head, int k, int val){
    if(head == NULL)
    return head;
    Node* current = head;
    int i=0;
    while(current){
        if(i==k){
            Node* newNode = new Node(val);
            Node* temp    = current->next;
            newNode->next = temp;
            current->next = newNode;
            newNode->prev = current;
            if (temp) /// check if temp is not null
                temp->prev = newNode;
        }
        current = current->next;
        i++;
    }
    return head;
}



int main(){
    vector<int>v = {20, 2 , 15 , 34, 5}; //
    Node* head = convertArraytoLL(v);
    // head = insertAfterK(head, 0, 10);
    printLL(head);
    // LL :  nullptr <- 20 -> 2 -> 15 
    //                     <-   <-
    Node* tempTail = head;
    int cnt=0;
    while (tempTail->next!= NULL){
        tempTail = tempTail->next;
        cnt++;
    }
    Node* tempHead = head;
    while(tempTail->prev != tempHead->next){
        swap(tempHead->data, tempTail->data);
        tempTail = tempTail->prev;
        tempHead = tempHead->next;
    }
    printLL(head);
    // Node* revHead = temp;
    // Node* s = temp; 
    // cout<<" size of LL is "<<cnt<<endl;
    // cout<<"last node value is "<<revHead->data<<" "<<endl;
    // cout<<" prev pointer of last node is "<<temp->prev<<" and it's data value is "<<temp->prev->data<<" "<<endl;
    // cout<< " before setting temp next "<<temp->next<<endl;
    // temp->next = temp->prev;
    // temp->prev = s->next;
    // cout<<" value of swap next_ptr is "<<s->next<<endl;
    // cout<<" PART 2222 "<<endl;
    //  cout<<"last node value is "<<temp->data<<" "<<endl;
    //  cout<<" next ptr of temp is "<<temp->next<<" and its data value is "<<temp->next->data<<endl;
    // cout<<" prev pointer of last node is "<<temp->prev<<" and it's data value is "<<temp->prev->data<<" "<<endl;
// expected
}

