// Даден е израз, който може да съдържа отварящи и затварящи скоби.
// Да се напише функция, която проверява дали скобите на израза са
// правилно балансирани. Например, изразът (x+(y+(1+2))) считаме за
// правилно балансиран, но не и израза (x+y)*3)+(x+(1+2).

#include <iostream>
#include <cstring>

bool balanced(std::string expression){
    int counter = 0;
    for(int i = 0; i < expression.length(); i++){
        if(counter == -1){
            return false;
        }

        if(expression[i] == '('){
            counter++;
        }

        if(expression[i] == ')'){
            counter--;
        }
    }
    return counter == 0;
}

int main(){
    std::cout << std::boolalpha << balanced("(x+(y+(1+2)))") << " " << std::boolalpha << balanced("x+y)*3)+(x+(1+2)");
}