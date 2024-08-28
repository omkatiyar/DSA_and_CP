#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

struct Node {
    string name;
    long long int phone_number;
    Node *next;
    Node *prev;
};

class ContactBook {
    Node *head;

public:
    ContactBook() {
        head = NULL;
    }

    void CreateNode(string name, long long int phoneNumber) {
        Node *newer = new Node;
        newer->name = name;
        newer->phone_number = phoneNumber;
        newer->next = NULL;
        newer->prev = NULL;

        if (head == NULL) {
            head = newer;
        } else {
            Node *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newer;
            newer->prev = temp;
        }
    }

    void Display() {
        Node *temp = head;
        if (temp == NULL) {
            cout << "No Contacts... Please Add Some Contacts" << endl;
            return;
        }

        BubbleSort();
        cout << "Name:      Number:" << endl;
        while (temp != NULL) {
            cout << temp->name << "    " << temp->phone_number << endl;
            temp = temp->next;
        }
    }

    int SearchByName(string name) {
        Node *temp = head;
        while (temp != NULL) {
            if (temp->name == name) {
                cout << "Name: " << temp->name << endl;
                cout << "Phone Number: " << temp->phone_number << endl;
                return 1;
            }
            temp = temp->next;
        }
        cout << "Name Not Found" << endl;
        return 0;
    }

    int SearchByNumber(long long int phoneNumber) {
        Node *temp = head;
        while (temp != NULL) {
            if (temp->phone_number == phoneNumber) {
                cout << "Name: " << temp->name << endl;
                cout << "Phone Number: " << temp->phone_number << endl;
                return 1;
            }
            temp = temp->next;
        }
        cout << "Number Not Found" << endl;
        return 0;
    }

    void DeleteAllContacts() {
        Node *temp = head;
        while (temp != NULL) {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
        head = NULL;
        cout << "Successfully Deleted All Contacts" << endl;
    }

    int DeleteContactByName(string name) {
        Node *temp = head;
        while (temp != NULL) {
            if (temp->name == name) {
                if (temp == head) {
                    head = temp->next;
                    if (head != NULL) head->prev = NULL;
                } else {
                    if (temp->prev != NULL) temp->prev->next = temp->next;
                    if (temp->next != NULL) temp->next->prev = temp->prev;
                }
                delete temp;
                cout << "Contact Deleted Successfully" << endl;
                return 1;
            }
            temp = temp->next;
        }
        cout << "Name Not Found" << endl;
        return 0;
    }

    int DeleteContactByNumber(long long int phoneNumber) {
        Node *temp = head;
        while (temp != NULL) {
            if (temp->phone_number == phoneNumber) {
                if (temp == head) {
                    head = temp->next;
                    if (head != NULL) head->prev = NULL;
                } else {
                    if (temp->prev != NULL) temp->prev->next = temp->next;
                    if (temp->next != NULL) temp->next->prev = temp->prev;
                }
                delete temp;
                cout << "Contact Deleted Successfully" << endl;
                return 1;
            }
            temp = temp->next;
        }
        cout << "Number Not Found" << endl;
        return 0;
    }

    void BubbleSort() {
        if (head == NULL) return;
        Node *i, *j;
        for (i = head; i->next != NULL; i = i->next) {
            for (j = i->next; j != NULL; j = j->next) {
                if (i->name > j->name) {
                    swap(i->name, j->name);
                    swap(i->phone_number, j->phone_number);
                }
            }
        }
    }

    int EditContactByName(string name, string newName, long long int newPhone) {
        Node *temp = head;
        while (temp != NULL) {
            if (temp->name == name) {
                temp->name = newName;
                temp->phone_number = newPhone;
                cout << "Contact Edited Successfully" << endl;
                return 1;
            }
            temp = temp->next;
        }
        cout << "Name Not Found" << endl;
        return 0;
    }

    int EditContactByNumber(long long int phoneNumber, string newName, long long int newPhone) {
        Node *temp = head;
        while (temp != NULL) {
            if (temp->phone_number == phoneNumber) {
                temp->name = newName;
                temp->phone_number = newPhone;
                cout << "Contact Edited Successfully" << endl;
                return 1;
            }
            temp = temp->next;
        }
        cout << "Number Not Found" << endl;
        return 0;
    }

    void SaveToFile() {
        ofstream myfile("contactbook.txt");
        if (myfile.is_open()) {
            Node *temp = head;
            while (temp != NULL) {
                myfile << temp->name << endl;
                myfile << temp->phone_number << endl;
                temp = temp->next;
            }
            myfile.close();
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    void LoadFromFile() {
        ifstream myfile("contactbook.txt");
        if (myfile.is_open() && myfile.peek() != EOF) {
            string name;
            long long int phone_number;
            while (getline(myfile, name)) {
                myfile >> phone_number;
                myfile.ignore(); // Ignore newline after number
                CreateNode(name, phone_number);
            }
            myfile.close();
        } else {
            cout << "File is empty or could not be opened." << endl;
        }
    }
};
