// Да се напише фунцкия bool issorted (...), която проверява 
// дали елементите на даден контейнер са подредени в нарастващ 
// или в намаляващ ред.

#include <limits.h>

template<template <typename> class Container, typename T>
bool isSorted(const Container<T>& container){
    T temp = INT_MIN;
    for(T& element: container){
        if (temp > element){
            return false;
        }
        temp = element;
    }
    return true;
}