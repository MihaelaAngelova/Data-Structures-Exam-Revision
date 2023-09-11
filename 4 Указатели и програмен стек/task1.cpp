#include <iostream>

template<typename T>
void swapElements(T* arr1, T* arr2, int size){
    for(int i = 0; i < size; i++){
        T temp = arr1[i];
        arr1[i] = arr2[i];
        arr2[i] = temp;
    }
}

int main(){
    char arr1[5] = "byee";
    char arr2[5] = "heyy";
    swapElements(arr1,arr2,5);
    std::cout << arr1 << std::endl;
    std::cout << arr2 << std::endl;
    return 0;
}