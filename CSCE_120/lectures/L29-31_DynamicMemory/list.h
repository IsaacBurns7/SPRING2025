#ifndef LIST
#define LIST

class list{
    private:
        int* arr;
        int size;
        int capacity;
        void resize();
    public:
        list();
        void push_back(int newVal);
        int& at(int index);
        ~list();
};

#endif LIST