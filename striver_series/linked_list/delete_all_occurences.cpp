#include <bits/stdc++.h>
using namespace std;

Node* removeElement(Node* head, int val){
    if(head==NULL) return head;
   
    while(head && head->data == val){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    Node* curr = head;
    Node* prev = NULL;
    
    while(curr){
        if(curr->data == val){
            prev->next = prev->next->next;
            curr= prev->next;
            // delete curr;
        }
        else{
        prev=curr;
        curr=curr->next;
        }
    }
    return head;
}
int main(){
    
}