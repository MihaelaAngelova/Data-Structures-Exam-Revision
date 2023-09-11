#include <iostream>

void swap(int &el1, int &el2){
    int temp = el1;
    el1 = el2;
    el2 = temp;
}

int main(){
    int a = 4;
    int b = 5;
    swap(a,b);
    std::cout << a << " " << b;
    return 0;
}