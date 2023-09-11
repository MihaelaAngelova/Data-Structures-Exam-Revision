#include <iostream>
#include <map>
#include <iterator>

template <typename T>
class ListIterator;

template<typename T>
struct box{
    box(const T& data): data(data), next(nullptr) {};
    box(const T& data, box<T>* next): data(data), next(next) {};
    T data;
    box<T>* next;
};

template<typename T>
class LList{
    private:
        box<T>* first;
    public:
        LList(): first(nullptr) {}

        LList(const LList<T>&other){
            first = copy(other.first);
        }

        LList(box<T>* head): first(head){};

        box<T>* copy(box<T>* other){
            if(other == nullptr){
                return nullptr;
            }
            return new box<T>(other->data, copy(other->next));
        }

        void clear(){
            box<T>* temp = first;
            while(first != nullptr){
                temp = first->next;
                delete first;
                first = temp;
            }
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
                return;
            }

            box<T>* curr = first;
            while(curr->next != nullptr){
                curr = curr->next;
            }
            curr->next = copy(other.first);
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
            first = new box<T>(x, first);
        }

        void push_back(const T& element){ // task 3
            if (!first) {
                first = new box<T>(element, nullptr);
                return;
            }

            box<T>* curr = first;
            while(curr->next != nullptr){
                curr = curr->next;
            }
            curr->next = new box<T>(element, nullptr);
        }

        void pop();
        void instertAt(unsigned index, const T& element){
            assert(index >= 0);
            if(index == 0){
                push_front(element);
                return;
            }

            box<T>* curr = first;
            for(int i = 0; i < index - 1; i++){
                curr = curr->next;
                if(curr == nullptr){
                    throw std::out_of_range("Index out of range!");
                }
            }
            curr->next = new box<T>(element, curr->next);
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

        T most_common(){
            std::map<T, int>m;
            box<T>* curr = first;
            while(curr){
                if(m.find(curr->data) != m.end()){
                    m[curr->data]++;
                } else {
                    m.insert(std::make_pair(curr->data, 1));
                }
                curr = curr->next;
            }

            size_t maxV = 0;
            for(auto it = m.begin(); it != m.end(); it++){
                if(it->second > maxV){
                    maxV = it->second;
                }
            }
            return maxV;
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
            current=current->next;
            return *this;
        }

        bool operator!=(const ListIterator<T>&other) const{
            return current!=other.current;
        }

    private:
        box<T>* current;
        box<T>* first;
};

template<typename T>
box<T>* reverseList(box<T>* head){
    if(!head || !(head->next)){
        return head;
    }
    box<T>* res = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return res;
}

int main(){
    box<int>* head = new box<int>(1);
    head->next = new box<int>(2);
    head->next->next = new box<int>(3);
    head->next->next->next = new box<int>(4);
    head->next->next->next->next = new box<int>(5);
    head->next->next->next->next->next = new box<int>(2);
    //head = reverseList(head);
    LList<int> *l = new LList<int>(head);
    std:: cout << l->most_common() << std::endl;
    box<int>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
    
    return 0;
}