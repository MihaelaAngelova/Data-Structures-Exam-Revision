//Задача 1.4.30. Обединение на два символни низа s1 и s2 наричаме всеки символен низ,
//който съдържа без повторение всички символи на s1 и s2. Да се дефинира функция, която
//намира и връща обединението на два символни низа.
#include <iostream>

char* concat(char* s1, int size1, char* s2, int size2){
    char* result = new char[size1 + size2 - 1];
    for(int i = 0; i < size1; i ++){
        result[i] = s1[i];
    }
    for(int i = 0; i < size2; i++){
        result[i + size1 - 1] = s2[i];
    }
    result[size1+size2] = '\0';
    return result;
}

int main(){
    char s1 [] = "Az sum ";
    char s2 [] = "Mishi.";
    std::cout << concat(s1, 8, s2, 7);
    return 0;
}
