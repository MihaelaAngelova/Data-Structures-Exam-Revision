// Да се реализира конструктор с два аргумента x и y от тип int. Конструкторът 
// създава списък с елементи x, x + 1, ..., y, при положение, че x ≤ y.

#include "LList.cpp"

template <typename T>
LList<T>::LList (int x, int y){
    first = x;
    box* curr = x;
    while(curr-> data != y){
        x-> next = new box{x->data + 1, nullptr};
        curr = curr->next;
    }
}

int main(){

    return 0;
}