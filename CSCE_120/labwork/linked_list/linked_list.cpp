# include "linked_list.h"
# include <iostream>
# include <string>

using std::cout, std::endl, std::string, std::ostream;

void MyList::add(const std::string& name, int score) {
    MyNode* newTail = new MyNode(name, score);
    newTail->next = nullptr;
    newTail->prev = nullptr;

    if(_head == nullptr){
        _head = _tail = newTail;
    }else{
        _tail->next = newTail;
        newTail->prev = _tail;
        _tail = newTail;
    }
    _size++;
}

void MyList::clear() {
    if(_head == nullptr){
        _size = 0;
        return;
    }
    MyNode* temp = _head;
    MyNode* dummy = _head;
    while(dummy){
        temp = dummy; 
        dummy = dummy->next;
        delete temp;
        _size--;
    }
    //head->next = nullptr
    //head is not necessarily nullptr
    _head = nullptr;
    _tail = nullptr;
    //_size = 0;
}

bool MyList::remove(const std::string& name) {
    // MyNode* dummy = _head;
    // while(dummy){
    //     if(dummy->name == name){
    //         MyNode* prev = dummy->prev;
    //         MyNode* next = dummy->next;
    //         if(prev != nullptr){
    //             prev->next = next; 
    //         }
    //         if(next != nullptr){
    //             next->prev = prev;
    //         }
    //         delete dummy;
    //         _size--;
    //         return true;
    //     }
    //     dummy = dummy->next;
    // }
    return false;
}

bool MyList::insert(const std::string& name, int score, size_t index) {
    // TODO

    return false;
}

MyList::MyList() : _size(0), _head(nullptr), _tail(nullptr) {}

MyList::~MyList() {
    clear();
}

size_t MyList::size() const {
    return _size;
}

bool MyList::empty() const {
    return _head == nullptr;
}

MyNode* MyList::head() const {
    return _head;
}

ostream& operator<<(ostream& os, const MyList& myList) {
    MyNode* _current = myList.head();
    if (_current == nullptr) {
        os << "<empty>" << endl;
        return os;
    }

    os << "[ " << _current->name << ", " << _current->score << " ]";
    _current = _current->next;
    while (_current != nullptr) {
        os << " --> [ " << _current->name << ", " << _current->score << " ]";
        _current = _current->next;
    }
    
    return os;
}

MyNode::MyNode(const std::string& name, int score) : name{name}, score{score}, next{nullptr}, prev{nullptr} {}
