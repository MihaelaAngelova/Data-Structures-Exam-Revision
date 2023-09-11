#include <iostream>

void reverse(int n){
    if(n == 0){
        return;
    }
    std::cout << "Enter the element." << std::endl;
    int number;
    std::cin >> number;
    reverse(n-1);
    std::cout << number << " ";
}

int main(){
    reverse (4);
}