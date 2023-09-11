// Да се реализира метод int LList<T>::count(int x), който преброява колко пъти елементът x се среща в списъка.
#include "LList.cpp";
template<typename T>
int LList<T>::count(int x){
    int counter = 0;
    box* curr = first;
    while(curr != nullptr){
        if(curr->data == x){
            counter++;
        }
        curr = curr->next;
    }
    return counter;
}

int main(){

    return 0;
}