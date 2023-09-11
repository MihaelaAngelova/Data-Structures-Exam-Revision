#include<iostream>

const int MAX = 5;
const int matrix[][MAX] = {
        0, 2, 4, 3, 9,
        0, 3, 2, 3, 3,
        0, 6, 5, 5, 3,
        0, 7, 7, 2, 8,
        0, 0, 6, 7, 9
    };

bool isValid(int x, int y){
    return (x >= 0 && x < MAX && y >= 0 && y < MAX);
}

bool downstairs (int sx, int sy, int tx, int ty){
    if(sx == tx && sy == ty){
        return true;
    }

    if(isValid(sx, sy+1) && matrix[sx][sy+1] == 0){
        return downstairs(sx, sy+1, tx, ty);
    }

    if(isValid(sx+1, sy) && matrix[sx+1][sy] == 0){
        return downstairs(sx+1, sy, tx, ty);
    }

    return false;
}

int main(){
    std::cout << std::boolalpha << downstairs(0, 0, 4, 1);
}