#include <iostream>
#include<cassert>
#include<sstream>
using std::cout, std::endl, std::ostream;

struct Node {
    int data;
    Node* next;
    Node(int data, Node* next) : data(data), next(next) {}
};

class LinkedList {
    private:
        Node* head;
    public:
        LinkedList() : head(nullptr) {}

        void insertAtBeginning(int value) {
            Node* newNode = new Node{value, nullptr};
            newNode->next = head;
            head = newNode;
        }

        void insertAtEnd(int value) {
            Node* newNode = new Node{value, nullptr};
            if (head == nullptr) {
                head = newNode;
            } else {
                Node* current = head;
                while (current->next != nullptr) { 
                    current = current->next;
                }
                current->next = newNode;
            }
        }
        
        // remove every other node starting from the node after the head
        void removeEveryOther() {
            bool remove = true; //remove the next node
            Node* dummy = head;
            while(dummy->next != nullptr){
                if(remove){
                    Node* newNext = dummy->next->next;
                    Node* skipped = dummy->next;
                    dummy->next = newNext;
                    delete skipped;
                }else{
                    dummy = dummy->next;
                }
                remove = !remove;
            }  
        }

        friend ostream& operator<<(ostream& os, const LinkedList& ll);
};

ostream& operator<<(ostream& os, const LinkedList& ll){
    Node dummy = *ll.head;
    os << dummy.data;
    while(dummy.next){
        dummy = *dummy.next;
        os << dummy.data;
    }
    return os;
}

int main() {
    LinkedList list1;
    list1.insertAtBeginning(3);
    list1.insertAtBeginning(2);
    list1.insertAtBeginning(1);
    list1.insertAtEnd(4);
    list1.insertAtBeginning(5);
    list1.insertAtEnd(6);
    cout << list1 << endl;
    list1.removeEveryOther();
    cout << list1 << endl;
}
