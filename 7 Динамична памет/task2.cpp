//Да се дефинира функция, която преобразува положително цяло число в
//съответния му символен низ и връща така построения символен низ.
#include <iostream>

char* convertString(unsigned int n){
    int counter = 0;
    int nCopy = n;
    while(nCopy > 0){
        nCopy/=10;
        counter++;
    }

    char* result = new char[counter+1];
    for(int i = 0; i < counter; i++){
        result[counter - i - 1] = (char)(n % 10 + '0');
        n/=10;
    }
    result[counter] = '\0';
    return result;
}

int main(){
    unsigned int n = 1234567;
    //std::cin >> n;
    std::cout<< convertString(n);
    return 0;
}