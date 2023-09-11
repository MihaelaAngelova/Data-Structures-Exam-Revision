#include <iostream>

void getmax (long *pmax, size_t n){
    while(n > 0){
        int number;
        std::cout << "Enter a number" << std::endl;
        std:: cin >> number;
        if(number > *pmax){
            *pmax = number;
        }
        n--;
    }
}

int main ()
{
    long max = -1;
    getmax (&max,5);
    std::cout << max;
    return 0;
}