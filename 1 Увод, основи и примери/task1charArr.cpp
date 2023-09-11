// Превърнете рождената си дата в шестнадесетична, в осмична и в двоична бройни системи.

#include <iostream>

int size(int n){
    int counter = 0;
    while (n > 0){
        n = n / 10;
        counter++;
    }
    return counter;
}

char hexRemainders(int r){
    return 'A' + r - 10;
}


char* reverse(char* input){
    char* result = new char[strlen(input) + 1];
    for(int i = 0; i < strlen(input); i++){
        result[strlen(input) - i - 1] = input[i];
    }
    result[strlen(input)] = '\0'; 
    return result;
}

char* convert(int input, int system) {
    char* result = new char[size(input)*10];
    int i = 0;
    while (input > 0){
        int r = input % system;
        if(r > 9){
            result[i] = hexRemainders(r);
        } else {
            result[i] = r + '0';
        }
        input = input / system;
        i++;
    }
    result[i] = '\0';
    return reverse(result);
}


int main() {
    int birthdayDate = 7122000;
    std::cout << "Binary: " << convert(birthdayDate, 2) << std::endl 
              << "Octal: " << convert(birthdayDate, 8) << std::endl 
              << "Hex: " << convert(birthdayDate, 16);
    return 0;
}

 