#include <iostream>

void getmax (long *pmax, size_t n){
    if(n == 0){
        return;
    }
    int number;
    std::cout << "Enter a number" << std::endl;
    std:: cin >> number;
    if(number > *pmax){
        *pmax = number;
    }
    getmax(pmax, n - 1);
}

int main ()
{
    long max = -1;
    getmax (&max,5);
    std::cout << max;
    return 0;
}