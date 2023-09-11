#include <iostream>

template <typename T>
class ListIterator;

template<typename T>
struct box{
    box(const T& data, box<T>* next = nullptr, box<T>* prev = nullptr): data(data), next(next), prev(prev) {};
    T data;
    box<T>* next;
    box<T>* prev;
};

template<typename T>
class LList{
    private:
        box<T>* first;
        box<T>* last;
    public:
        LList(): first(nullptr), last(nullptr) {}

        LList(const LList<T>&other){
            first = copy(other.first);
        }

        box<T>* copy(box<T>* other){
            if(other == nullptr){
                return nullptr;
            }
            box<T>* new_box = new box<T> (other->data, copy(other->next));
            if(new_box->next){
                new_box->next->prev = new_box;
            }
            return new_box;
        }

        void clear(){
            box<T>* temp = first;
            while(first != nullptr){
                temp = first->next;
                delete first;
                first = temp;
            }
            last = nullptr;
        }

        LList<T>& operator= (const LList<T>&other){
            if(this != &other){
                clear();
                first = copy(other.first);
            }
            return *this;
        }

        ListIterator<T> begin() const{
            return ListIterator<T>(first);
        }
        
        ListIterator<T> end()const {
            return ListIterator<T>(nullptr);
        }

        void append(LList<T>& other){ // task 7
            if (!first) {
                first = copy(other.first);
                if(other.last){
                    last = first;
                    while(last->next){
                        last = last->next;
                    }
                }
                return;
            }

            if(other.first){
                box<T>* curr = last;
                curr->next = copy(other.first);

                while(curr->next){
                    curr->next->prev = curr;
                    curr = curr->next;
                }
                last = curr;
            }
        }

        LList<T>& operator += (const T& element){ // task 4
            push_back(element);
            return *this;
        }

        LList<T>& operator[] (size_t index){
            box<T>* curr = first;
            for(int i = 0; i < index; i++){
                if(curr == nullptr){
                    throw std::out_of_range("Index out of bounds!");
                }
                curr = curr->next;
            }
            return curr->data;
        }
        
        int count(int x); // task 1, chapter 12
        LList (int x, int y); // task 2, chapter 12

        void push_front(const T& x){
            box<T>* new_box = new box<T>(x);
            if(first){
                new_box->next = first;
                first->prev = new_box;
            }
            first = new_box;
        }

        void push_back(const T& element){ // task 3
            if (!first) {
                first = new box<T>(element);
                last = first;
                return;
            }

            last->next = new box<T>(element, nullptr, last);
        }

        void instertAt(unsigned index, const T& element){
            assert(index >= 0);
            if(index == 0){
                push_front(element);
                return;
            }

            box<T>* curr = first;
            for(int i = 0; i < index - 1; i++){
                if(curr == nullptr){
                    throw std::out_of_range("Index out of range!");
                }
                curr = curr->next;
            }
            box<T>* new_box = new box<T>(element, curr->next, curr);
            new_box->next = curr->next;
            curr->next-> = new_box;
            new_box->prev = curr;

            if(new_box->next){
                new_box->next->prev = new_box;
            }
        }
        void deleteAt(unsigned);

        void print()const{
            box<T>* curr = first;
            while(curr!= nullptr){
                std::cout << curr->data << " ";
                curr = curr-> next;
            }
            std::cout << "nullptr" << std::endl;
        }

        unsigned size()const{
            box<T>* curr = first;
            unsigned counter = 0;
            while(curr != nullptr){
                counter++;
                curr=curr->next;
            }
            return counter;
        }

        ~LList(){
            clear();
        };

        void reverse(box<T>*& first){
            box<T>* temp = nullptr;
            box<T>* curr = first;
            
            while(curr){
                temp = curr->prev;
                curr->prev = curr->next;
                curr->next = temp;
                curr = curr->next;
            }
            
            if(temp){
                first = temp->prev;
            }
        }

};

template<typename T>
class ListIterator{
    
    public:
        ListIterator(box<T>* first): first(first), current(first) {}
        friend class LList<T>;

        T operator*(){
            if(current == nullptr){
                throw std::out_of_range("Iterator out of range.");
            }
            return current->data;
        }

        ListIterator<T>& operator++(){
            if(current == nullptr){
                throw std::out_of_range("Iterator out of range.");
            }
            current=current->next;
            return *this;
        }

        ListIterator<T>& operator--(){
            if(current == first){
                throw std::out_of_range("Iterator out of range.");
            }
            current=current->prev;
            return *this;
        }

        bool operator!=(const ListIterator<T>&other) const{
            return current!=other.current;
        }

    private:
        box<T>* current;
        box<T>* first;
};

int main(){
    LList<int> lischi;
    lischi.push_back(1);
    lischi.push_back(2);
    lischi.push_back(3);
    lischi.push_back(4);
    lischi.push_back(5);
    lischi.print();

    LList<int> copy_lischi(lischi);
    copy_lischi.print();

    lischi.clear();
    lischi.print();
    copy_lischi.print();

    lischi = copy_lischi;
    lischi.push_back(6);
    lischi.print();
    copy_lischi.print();

    lischi.append(copy_lischi);
    lischi.print();
    copy_lischi.print();

    copy_lischi.push_back(420);
    lischi.print();
    copy_lischi.print();
    
    return 0;
}