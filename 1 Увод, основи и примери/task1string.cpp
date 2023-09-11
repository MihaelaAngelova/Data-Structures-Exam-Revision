#include <iostream>
#include <cstring>
using namespace std;

char hexRemainders(int r){
    return 'A' + r - 10;
}

string reverse(string input){
    string result;
    for(int i = 0; i < input.length(); i++){
        result.push_back(input[input.length() - i - 1]);
    }
    return result;
}

string convert(int input, int system) {
    string result;
    int i = 0;
    while (input > 0){
        int r = input % system;
        if(r > 9){
            result.push_back(hexRemainders(r));
        } else {
            result.push_back(r + '0');
        }
        input = input / system;
        i++;
    }
    return reverse(result);
}

int main(){
    int birthdayDate = 7122000;
    cout << "Binary: " << convert(birthdayDate, 2) << endl 
              << "Octal: " << convert(birthdayDate, 8) << endl 
              << "Hex: " << convert(birthdayDate, 16);
    return 0;
}