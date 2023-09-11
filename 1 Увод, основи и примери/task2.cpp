#include <iostream>
#include <cstring>
using namespace std;

int main(){
    string mihaela = "mihaela";
    for(int i = 0; i < mihaela.length(); i++){
        cout << mihaela[i] << ": " << (int)mihaela[i] << endl;
    }
    return 0;
}