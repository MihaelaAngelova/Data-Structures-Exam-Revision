#include <iostream>

char* strduplicate(char* array, int size){
    char* copyArr = new char[size];
    for(int i = 0; i < size; i++){
        copyArr[i] = array[i];
    }
    return copyArr;
}

int main(){
    char test [] = {'a', 'b', '1', '2'};
    char *result = new char[5];
    result = strduplicate(test, 5);
    std::cout << result[0] << result[1] << result[2] << result[3];
}