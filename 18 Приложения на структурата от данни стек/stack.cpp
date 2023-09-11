#include <iostream>
#include <cassert>

template <typename T>
class Stack{
    public:
    Stack(): count(0), head(nullptr){};

    Stack(const Stack& other){
        head = copy(other.head);
    }

    Stack& operator=(const Stack& other){
        if( this != &other){
            clear();
            head = copy(other.head);
        }
        return *this;
    }

    ~Stack(){
        clear();
    }

    T top(){
        assert(head != nullptr);
        return head->data;
    }

    void pop(){
        assert(head != nullptr);
        box *temp = head;
        head = head->next;
        delete temp;
        --count;
    }

    void push(const T& element){
        head = new Stack<T>::box(element, head);
        ++count;
    }

    bool empty(){
        return head == nullptr;
    }

    size_t size()const{
        return count;
    }

    void print(){
        box *temp = head;
        while(temp != nullptr){
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std:: cout << "nulllptr" << std::endl;
    }

    

   
    private:
    struct box{
        T data;
        box *next;
        box(const T& data, box* next): data(data), next(next) {}
    };
    size_t count;
    box *head;

    box *copy(box *other){
        if (other == nullptr){
            return nullptr;
        }
        return new box(other->data, copy(head->next));
        
    }

     void clear(){
        box* temp = head;
        while(head != nullptr){
            head = head -> next;
            delete temp;
            temp = head;
        }
    }

    
};

int main(){
    Stack<int> stack;
    stack.push(4);
    stack.push(3);
    stack.push(2);
    stack.push(1);
    stack.print();
    stack.pop();
    stack.print();
    std::cout << "Stack size: " << stack.size() << std::endl;
}