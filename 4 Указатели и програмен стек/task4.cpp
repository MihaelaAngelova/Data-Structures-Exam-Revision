#include <iostream>

bool duplicates (long *pointers[], int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = i + 1; j < size; j++){
            if(*pointers[i] == *pointers[j]){
                return true;
            }
        }
    }
    return false;
}

int main(){
    long p[] ={100,2,4,6,5,5};
    long *pointers[] = {&p[0], &p[1], &p[2], &p[3], &p[4], &p[5]};
    std::cout << duplicates(pointers, 6);
}